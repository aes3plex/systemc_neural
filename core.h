#pragma once
#include "systemc.h"
#include "input.h"

#define epochs 7

SC_MODULE(core) {

	sc_in<bool>  clk_i;
	//sc_out<int>  addr_bo;				
	//sc_out<int>  data_bo;				
	sc_in<int>   train_data_i[train_dim];
	sc_in<int>   ideal_data_i[ideal_dim];
	sc_in<int>   test_i[train_dim];
	sc_in<bool>	 wr_i;
	
	//sc_out<bool> wr_o;					// writing flag
	//sc_out<bool> wr_f;					// reading flag
	static int count;
	int core_num;

	
	/*void bus_write(int addr, int data) {

		addr_bo.write(addr);
		data_bo.write(data);
		wr_o.write(1);

		wait();
	
		cout << "CORE " << get_core_num() << ":" << endl;
		cout << "	addr: " <<  addr << endl;
		cout << "	data: " <<  data << endl << endl;
	}*/

	
	void input_read() {
		
		vector<float> actual;
		Layer layer1(49), layer2(49), layer3(3);
		vector<Layer> net = { layer1, layer2, layer3 };

		wait();
		wait();
		for (int j(0); j < set_size; j++) {
			if (wr_i.read()) {
				for_ideal() 
					ideals[j][i] = ideal_data_i[i].read();
				
				for_train()
					dataset[j][i] = train_data_i[i].read();

				for_train()
					test[i] = test_i[i].read();
			}

			wait();
		}
		
		for (int i(0); i < epochs; i++) {
			
			//cout << endl << endl << "epoch " << i << " core " << get_core_num() <<endl;
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
			cout << war(net, test)[i] << " ";


		/*
		int temp = get_core_num() * output_size;
		for (int i = temp, j = 0; i < temp + output_size; i++) {
			bus_write(i, local_memory[j]);
			j++;
		}

		data_bo.write(0);
		addr_bo.write(0);
		wr_o.write(0);
		*/
	}
	
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

	int get_core_num() {
		return core_num;
	}

	SC_CTOR(core) {
		
		core_num = count;
		count++;

	/*	addr_bo.initialize(0);
		data_bo.initialize(0);
		wr_o.initialize(0);*/
		//wr_f.initialize(0);
		
		dataset.resize(set_size);
		for (int i(0); i < set_size; i++)
			dataset[i].resize(train_dim);
	
		ideals.resize(set_size);
		for (int i(0); i < set_size; i++)
			ideals[i].resize(ideal_dim);

		test.resize(train_dim);

		SC_CTHREAD(input_read, clk_i.pos());
		
		
	}

private:
	vector<vector<float>> dataset;
	vector<vector<float>> ideals;
	vector<float> test;
};

int core::count = 0;


