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
	sc_out<bool>  wr_f;
	sc_out<int>  data_bo;
	
	void mem_read()
	{
		wait();
		for (int j(0); j < 6; j++) { //stop hardcode j
			wait();
			for_bus() {
				if (wr_i[i].read())
					mem[addr_bi[i].read()] = data_bi[i].read();
			}
		}
		
		data_bo.write(get_buff_sum());
		wr_f.write(1);

		wait();
		wr_f.write(0);
		
	}

	void get_mem() {
		for (int i(0); i < 10; i++) {
			cout << mem[i] << " ";
		}
	}

	int get_buff_sum() {
		int counter = 0;
		for (int i(0); i < 10; i++)
			counter += mem[i];

		return counter;
	}

	SC_CTOR(bus) {

		data_bo.initialize(0);

		for (int i(0); i < 10; i++) {
			mem[i] = 0;
		}
		
		/*
		SC_METHOD(mem_read);
		for_bus()
			sensitive << clk_i.pos();
	*/
		SC_CTHREAD(mem_read, clk_i.pos());
	}

private:
	int mem[10];

};