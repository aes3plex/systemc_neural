#pragma once

#include "systemc.h"
#include "input.h"

using namespace std;

SC_MODULE(memory) {

	sc_in<bool>  clk_i;
	sc_in<int>   addr_bi;				// reception from addr_bo
	sc_in<int>   data_bi;				// reception from data_bo
	//sc_out<int>  data_bo[output_size];	// data transmition
	sc_in<bool>  wr_i;					// reception wr_o
	sc_in<bool>  is_wr_f;				// reception rd_o
	

	void mem_read()
	{
		if (wr_i.read())
			mem[addr_bi.read()] = data_bi.read();
	}
	

	void get_mem() {
		for (int i(0); i < 10; i++) {
			cout << mem[i] << " ";
		}
	}

	SC_CTOR(memory) {
		
		/*
		foro()
			data_bo[i].initialize(0);
		*/

		//mem_init

		SC_METHOD(mem_read);
		sensitive << clk_i.pos();
		
		
	}

	private:
		int mem[10];
};
