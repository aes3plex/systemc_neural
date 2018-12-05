#pragma once
#include "systemc.h"
#include "input.h"

SC_MODULE(core) {

	sc_in<bool>  clk_i;
	//sc_out<int>  addr_bo;				// adress transmition
	//sc_out<int>  data_bo;				// data transmition
	sc_in<int>   data_bi[input_size];	// data reception
	sc_in<bool>	 wr_i;
										//sc_out<bool> wr_o;					// writing flag
	//sc_out<bool> wr_f;					// reading flag
	static int count;
	int core_num;

	/*
	void bus_write(int addr, int data) {

		addr_bo.write(addr);
		data_bo.write(data);
		wr_o.write(1);

		wait();
		wait();
		
		//wr_o.write(0);

		cout << "CORE " << get_core_num() << ":" << endl;
		cout << "	addr: " <<  addr << endl;
		cout << "	data: " <<  data << endl << endl;
	}

	void do_it() {
		wait();
		


		int temp = get_core_num() * output_size;
		for (int i = temp, j = 0; i < temp + output_size; i++) {
			bus_write(i, local_memory[j]);
			j++;
		}
			
			
		
		
		data_bo.write(0);
		addr_bo.write(0);
		wr_o.write(0);


		wait();
		//wr_f.write(1);
		wait();
		//wr_f.write(0);
		//sc_stop();

	}
	*/
	
	void input_read() {
		
		wait(); // необходим, потому что нулевой такт сжирается слева ?????
		for(int j(0); j < 3; j ++){
			if (wr_i.read()) {
					forn(){
						cout << "data_bi on iter " << j << ": " << data_bi[i].read() << endl;
						local_memory[i] += data_bi[i].read();
					}
				}

		wait();
		}
	}
	

	void get_local_memory() {
		forn()
			cout << local_memory[i] << " ";
	}

	int get_core_num() {
		return core_num;
	}

	SC_CTOR(core) {
		
		core_num = count;
		count++;

		//addr_bo.initialize(0);
		//data_bo.initialize(0);
		//wr_o.initialize(0);
		//wr_f.initialize(0);
		
		forn()
			local_memory[i] = 0;

		/*
		SC_METHOD(input_read);
		forn()
			sensitive << clk_i.pos();
		*/

		SC_CTHREAD(input_read, clk_i.pos());
		
		//SC_CTHREAD(do_it, clk_i.pos());
	}

private:
	int local_memory[input_size];
};

int core::count = 0;