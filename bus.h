#pragma once

#include "systemc.h"
#include "input.h"
#define bus_size 2
#define for_bus() for(int i(0); i < bus_size; i++)

using namespace std;


SC_MODULE(bus) {

	sc_in<bool>  clk_i;

	sc_in<int>   addr_bi[bus_size];
	sc_in<int>   data_bi[bus_size];
	sc_in<bool>  wr_i[bus_size];
	

	void mem_read1()
	{
		for_bus() {
			if (wr_i[i].read())
				mem[addr_bi[i].read()] = data_bi[i].read();
		}
	}


	void get_mem() {
		for (int i(0); i < 10; i++) {
			cout << mem[i] << " ";
		}
	}

	SC_CTOR(bus) {

		for (int i(0); i < 10; i++) {
			mem[i] = 0;
		}
		
		SC_METHOD(mem_read1);
		for_bus()
			sensitive << clk_i.pos();
			

	}

private:
	int mem[10];

};