#include <iostream>
#include "systemc.h"
#include "core.h"
#include "memory.h"
#include "input.h"
#include "bus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "out.h"

int sc_main(int argc, char* argv[]) {
	
	input input("input");
	core core1("core1"), core2("core2"), core3("core3");
	bus bus("bus");
	memory memory("memory");
	out_module out_module("out_module");
	
	
	sc_clock clk("clk", sc_time(10, SC_NS));
	sc_signal<bool> is_input;				// input flag
	sc_signal<bool> train_bus[train_dim];	// dataset to input
	sc_signal<bool> ideal_bus[ideal_dim];	// ideal to input
	sc_signal<bool> test_bus[train_dim];	// test to input
	sc_signal<int> addr[3];					// address to bus
	sc_signal<int> data[3];					// data to bus
	sc_signal<bool> wr[3];					// bus flag 
	sc_signal<bool> rd;						// mem flag
	sc_signal<int> to_memory;				// data to memory
	sc_signal<bool> to_out;					// out flag
	sc_signal<int> data_to_out;				// data to out
	sc_signal<int> out_signal;				// out

	
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
	core1.addr_bo(addr[0]);
	core1.data_bo(data[0]);
	core1.wr_o(wr[0]);
	for_train()
		core1.train_data_i[i](train_bus[i]);
		
	for_ideal()
		core1.ideal_data_i[i](ideal_bus[i]);

	for_train()
		core1.test_i[i](test_bus[i]);

	core1.wr_i(is_input);
	
	
	// CORE2

	core2.clk_i(clk);
	core2.addr_bo(addr[1]);
	core2.data_bo(data[1]);
	core2.wr_o(wr[1]);
	for_train()
		core2.train_data_i[i](train_bus[i]);
	
	for_ideal()
		core2.ideal_data_i[i](ideal_bus[i]);

	for_train()
		core2.test_i[i](test_bus[i]);

	core2.wr_i(is_input);
	

	// CORE3

	core3.clk_i(clk);
	core3.addr_bo(addr[2]);
	core3.data_bo(data[2]);
	core3.wr_o(wr[2]);
	for_train()
		core3.train_data_i[i](train_bus[i]);

	for_ideal()
		core3.ideal_data_i[i](ideal_bus[i]);

	for_train()
		core3.test_i[i](test_bus[i]);

	core3.wr_i(is_input);

	   	
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
	
	
	// MEMORY

	memory.clk_i(clk);
	memory.is_wr_f(rd);
	memory.to_out_o(to_out);
	memory.data_bo(data_to_out);
	memory.data_bi(to_memory);
	

	//OUT

	out_module.clk_i(clk);
	out_module.data_out_bi(data_to_out);
	out_module.wr_out_i(to_out);
	out_module.out_to_out(out_signal);


	// TRACING

	sc_trace_file *wf = sc_create_vcd_trace_file("wave");
	sc_trace(wf, clk, "clk");
	
	sc_trace(wf, out_signal, "out_signal");
	sc_trace(wf, data_to_out, "data_to_out");
	sc_trace(wf, to_out, "to_out");
	sc_trace(wf, to_memory, "to_memory");
	sc_trace(wf, rd, "rd");
	sc_trace(wf, addr[0], "addr0");
	sc_trace(wf, data[0], "data0");
	sc_trace(wf, wr[0], "wr0");
	   
	for_ideal()
		sc_trace(wf, ideal_bus[i], "ideal_bus" + to_string(i));

	sc_trace(wf, is_input, "is_input");

	cout << endl << "_________________________" << endl << endl << "Calculating..." << endl << "_________________________" << endl;
	sc_start(sc_time(400, SC_NS));
	
	core1.get_prediction();
	core2.get_prediction();
	core3.get_prediction();


	cout << endl << "RESULT IS: ";
	out_module.parsing_result(out_module.get_out());
	cout << endl << endl << endl;

	sc_close_vcd_trace_file(wf);
	
	return(0);
}