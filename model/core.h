#pragma once
#include "systemc.h"
#include "input.h"

#define epochs 7

SC_MODULE(core) {

	sc_in<bool>  clk_i;
	sc_in<bool>   train_data_i[train_dim];	// reading dataset	
	sc_in<bool>   ideal_data_i[ideal_dim];	// reading ideals	
	sc_in<bool>   test_i[train_dim];		// reading test
	sc_in<bool>	 wr_i;						// reading input flag
	sc_out<bool> wr_o;						// writing output flag
	sc_out<int>  addr_bo;					// writing address				
	sc_out<int>  data_bo;					// writing data	

	static int count;
	int core_num;
		
	// print float prediction
	void get_prediction() {
		cout << "Prediction for core " << core_num << ": ";
		for_ideal()
			cout << prediction[i] << " ";
		cout << endl;
	}

	// sending results to the bus 
	void bus_write(int addr, int data) {

		addr_bo.write(addr);
		data_bo.write(data);
		wr_o.write(1);

		wait();
	
		cout << endl << "CORE " << get_core_num() << ":" << endl;
		cout << "	addr: " <<  addr << endl;
		cout << "	data: " <<  data << endl << endl;
	}

	// core main thread
	void input_read() {
		
		vector<float> actual;
		Layer layer1(49), layer2(49), layer3(3);
		vector<Layer> net = { layer1, layer2, layer3 };

		wait();
		wait();
		for (int j(0); j < set_size; j++) {
			if (wr_i.read()) {
				for_ideal() 
					ideals[j][i] = (int)ideal_data_i[i].read();
				
				for_train()
					dataset[j][i] = (int)train_data_i[i].read();

				for_train()
					test[i] = (int)test_i[i].read();
			}

			wait();
		}
		
		// neural net counting
		for (int i(0); i < epochs; i++) {
			
			float counter = 0;

			for (int j(0); j < dataset.size(); j++) {

				net[0].set_first_layer_outputs(dataset[j]);
				net[1].set_layer_outputs(net[0]);
				net[2].set_layer_outputs(net[1]);

				//backpropagation

				net[2].set_last_layer_deltas(ideals[j]);
				net[1].set_deltas(net[2]);
				net[0].set_deltas(net[1]);

				actual = net[2].get_layer_outputs();
				counter += error_is(actual, ideals[j]) * error_is(actual, ideals[j]);
			}

			counter /= dataset.size();
		} 
		
		for_ideal()
			prediction[i] = war(net, test)[i];

		int temp = get_core_num() * 3; // 3 - output_size
		for (int i = temp, j = 0; i < temp + 3; i++) {
			bus_write(i, convert(war(net, test))[j]);
			j++;
			}
		cout << endl;

		data_bo.write(0);
		addr_bo.write(0);
		wr_o.write(0);
		
	}
	
	// methods for debugging
	void get_ideal() {
		for(int j(0); j < set_size; j++){
			for_ideal()
				cout << ideals[j][i] << " ";

			cout << endl;
		}
	}
	
	void get_dataset() {
		for (int j(0); j < set_size; j++) {
			for_train() {
				cout << dataset[j][i] << " ";
				if (i % 7 == 0)
					cout << endl;
			}
			cout << endl << endl;
		}
	}

	void get_test() {
		for_train() {
			cout << test[i] << " ";
			if (i % 7 == 0)
				cout << endl;
		}
	}

	// get core number
	int get_core_num() {
		return core_num;
	}

	SC_CTOR(core) {
		
		core_num = count;
		count++;

		addr_bo.initialize(0);
		data_bo.initialize(0);
		wr_o.initialize(0);
				
		dataset.resize(set_size);
		for (int i(0); i < set_size; i++)
			dataset[i].resize(train_dim);
	
		ideals.resize(set_size);
		for (int i(0); i < set_size; i++)
			ideals[i].resize(ideal_dim);

		test.resize(train_dim);
		prediction.resize(ideal_dim);

		SC_CTHREAD(input_read, clk_i.pos());
	
	}

private:
	vector<vector<float>> dataset;
	vector<vector<float>> ideals;
	vector<float> test;
	vector<float> prediction;
};

int core::count = 0;


