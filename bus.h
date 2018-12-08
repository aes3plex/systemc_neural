#pragma once

#include "systemc.h"
#include "input.h"
#define bus_size 3
#define for_bus() for(int i(0); i < bus_size; i++)

using namespace std;


SC_MODULE(bus) {

	sc_in<bool>  clk_i;
	sc_in<int>   addr_bi[bus_size];		// reading address
	sc_in<int>   data_bi[bus_size];		// reading data
	sc_in<bool>  wr_i[bus_size];		// reading flag
	sc_out<bool>  wr_f;					// writing flag
	sc_out<int>  data_bo;				// writing data
	
	// bus main thread
	void mem_read()
	{
		wait();
		wait();
		for (int j(0); j < 9; j++) { 
			wait();
			for_bus() {
				if (wr_i[i].read())
					mem[addr_bi[i].read()] = data_bi[i].read();
			}
		}
		
		wait();
		wr_f.write(1);
		for (int i(0); i < 9; i++) {
			data_bo.write(mem[i]);
			wait();
		}

		wr_f.write(0);
		data_bo.write(0);
				
	}

	SC_CTOR(bus) {

		for (int i(0); i < 9; i++) {
			mem[i] = 0;
		}
		
		SC_CTHREAD(mem_read, clk_i.pos());
	}

private:
	int mem[9];

};