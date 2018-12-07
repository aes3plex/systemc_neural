#include <iostream>
#include "systemc.h"
#include "core.h"
#include "memory.h"
#include "input.h"
#include "bus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int sc_main(int argc, char* argv[]) {
	
	//memory memory("memory");
	core core1("core1"), core2("core2"), core3("core3");
	//bus bus("bus");
	
	input input("input");
	
	sc_clock clk("clk", sc_time(10, SC_NS));
	sc_signal<int> addr[2];
	sc_signal<int> data[2];
	sc_signal<bool> wr[2];
	//sc_signal<bool> rd;
	//sc_signal<int> to_memory;
	sc_signal<int> train_bus[train_dim];
	sc_signal<int> ideal_bus[ideal_dim];
	sc_signal<int> test_bus[train_dim];
	sc_signal<bool> is_input;
	
	//sc_signal<int> out;

	
	//INPUT

	input.clk_i(clk);
	for_train()
		input.train_data_o[i](train_bus[i]);
	
	for_ideal()
		input.ideal_data_o[i](ideal_bus[i]);
	
	for_train()
		input.test_o[i](test_bus[i]);

	input.wr_o(is_input);
	
	// CORE1

	core1.clk_i(clk);
	//core1.addr_bo(addr[0]);
	//core1.data_bo(data[0]);
	//core1.wr_o(wr[0]);
	for_train()
		core1.train_data_i[i](train_bus[i]);
		
	for_ideal()
		core1.ideal_data_i[i](ideal_bus[i]);

	for_train()
		core1.test_i[i](test_bus[i]);

	core1.wr_i(is_input);
	
	
	// CORE2

	core2.clk_i(clk);
	//core2.addr_bo(addr[1]);
	//core2.data_bo(data[1]);
	//core2.wr_o(wr[1]);
	for_train()
		core2.train_data_i[i](train_bus[i]);
	
	for_ideal()
		core2.ideal_data_i[i](ideal_bus[i]);

	for_train()
		core2.test_i[i](test_bus[i]);

	core2.wr_i(is_input);
	

	// CORE3

	core3.clk_i(clk);
	//core3.addr_bo(addr[1]);
	//core3.data_bo(data[1]);
	//core3.wr_o(wr[1]);
	for_train()
		core3.train_data_i[i](train_bus[i]);

	for_ideal()
		core3.ideal_data_i[i](ideal_bus[i]);

	for_train()
		core3.test_i[i](test_bus[i]);

	core3.wr_i(is_input);



	/*
	// BUS
	
	bus.clk_i(clk);
	for_bus()
		bus.addr_bi[i](addr[i]);
	
	for_bus()
		bus.data_bi[i](data[i]);
	
	for_bus()
		bus.wr_i[i](wr[i]);
	
	bus.wr_f(rd);
	bus.data_bo(to_memory);
	
	
	// MEMORY + OUT 

	memory.clk_i(clk);
	memory.is_wr_f(rd);
	memory.data_bo(out);
	memory.data_bi(to_memory);
	
	*/


	sc_trace_file *wf = sc_create_vcd_trace_file("wave");
	sc_trace(wf, clk, "clk");
	
	
	//sc_trace(wf, addr[0], "addr0");
	//sc_trace(wf, data[0], "data0");
	//sc_trace(wf, wr[0], "wr0");

	//sc_trace(wf, addr[1], "addr1");
	//sc_trace(wf, data[1], "data1");
	//sc_trace(wf, wr[1], "wr1");
		//
		//sc_trace(wf, rd, "rd");
	
	
	
	for_train()
		sc_trace(wf, train_bus[i], "train_bus");
	
	for_ideal()
		sc_trace(wf, ideal_bus[i], "ideal_bus" + to_string(i));


	sc_trace(wf, is_input, "is_input");
	//sc_trace(wf, wr, "wr");
	
	//sc_trace(wf, out, "out");
	
	cout << endl << "_________________________" << endl << endl << "Calculating..." << endl << "_________________________" << endl;
	sc_start(sc_time(150, SC_NS));
	
	
	//cout << "Core 1 local memory: ";
	//core1.get_test();
	//core1.get_dataset();

	//cout << "Core 2 local memory: ";
	//core2.get_ideal();
	//core2.get_dataset();
	//
	//cout << endl << "Core 2 local memory: ";
	//core2.get_local_memory();
	//cout << endl << "Bus buffer: ";
	//bus.get_mem();
	//cout << endl << "Buffer sum: " << bus.get_buff_sum();
	
	sc_close_vcd_trace_file(wf);
	
	return(0);
}