#pragma once

#include "systemc.h"
#include "input.h"

using namespace std;

SC_MODULE(memory) {

	sc_in<bool>  clk_i;
	sc_in<int>   data_bi;			// reading data
	sc_in<bool>  is_wr_f;			// reading flag
	sc_out<int>  data_bo;			// writing data
	sc_out<bool> to_out_o;			// writing flag

	// memory main thread
	void mem_read()
	{
		wait();
		wait();
		for (int i(0), temp = 0; i < 19; i++) {
			wait();
			if (is_wr_f.read()){
				mem[temp] = data_bi.read();
				temp++;
			}
		}
		wait();
		to_out_o.write(1);
		
		for (int i(0); i < 9; i++){
			data_bo.write(mem[i]);
			wait();
		}

		to_out_o.write(0);
		data_bo.write(0);
		
	}
	
	// get memory
	void get_mem() {
		for (int i(0); i < 9; i++) {
			cout << mem[i] << " ";
		}
	}

	SC_CTOR(memory) {
		

		to_out_o.initialize(0);
		data_bo.initialize(0);

		for (int i(0); i < 9; i++)
			mem[i] = 0;

		SC_CTHREAD(mem_read, clk_i.pos());
	
	}

	private:
		int mem[9];
};
