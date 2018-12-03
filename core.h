#pragma once
#include "systemc.h"
#include "input.h"

SC_MODULE(core) {

	sc_in<bool>  clk_i;
	sc_out<int>  addr_bo;				// adress transmition
	sc_out<int>  data_bo;				// data transmition
	sc_in<int>   data_bi[input_size];	// data reception
	sc_out<bool> wr_o;					// writing flag
	sc_out<bool> wr_f;					// reading flag


	void bus_write(int addr, int data) {

		addr_bo.write(addr);
		data_bo.write(data);
		wr_o.write(1);

		wait();
		wait();
		
		//wr_o.write(0);

		cout << "CORE: WRITE " << endl;
		cout << "  -> addr: " << hex << addr << endl;
		cout << "  -> data: " << hex << data << endl;
	}

	void do_it() {
		wait();
		for (int i(0); i < 3; i++) {
			bus_write(i, i*i);
		}
		
		data_bo.write(0);
		addr_bo.write(0);
		wr_o.write(0);


		wait();
		wr_f.write(1);
		wait();
		wr_f.write(0);
		//sc_stop();

	}


	void input_read() {
		forn()
			local_memory[i] = data_bi[i].read();
	}

	void get_local_memory() {
		forn()
			cout << local_memory[i] << " ";
	}

	SC_CTOR(core) {
		addr_bo.initialize(0);
		data_bo.initialize(0);
		wr_o.initialize(0);
		wr_f.initialize(0);
		
		forn()
			local_memory[i] = 0;

		SC_METHOD(input_read);
		forn()
			sensitive << clk_i.pos();
		
		
		//SC_CTHREAD(do_it, clk_i.pos());
	}

private:
	int local_memory[input_size];
};