#include <iostream>
#include "systemc.h"
#include "core.h"
#include "memory.h"
#include "input.h"
#include "bus.h"


int sc_main(int argc, char* argv[]) {
	
	//memory memory("memory");
	core core1("core1"), core2("core2");
	//bus bus("bus");
	input input("input");

	sc_clock clk("clk", sc_time(10, SC_NS));
	//sc_signal<int> addr[2];
	//sc_signal<int> data[2];
	//sc_signal<bool> wr[2];
	//sc_signal<bool> rd;
	//sc_signal<int> to_memory;
	sc_signal<int> input_bus[input_size];
	sc_signal<bool> is_input;
	//sc_signal<int> out;

	
	//INPUT

	input.clk_i(clk);
	forn()
		input.data_bo[i](input_bus[i]);
	input.wr_o(is_input);
	
	// CORE1

	core1.clk_i(clk);
	//core1.addr_bo(addr[0]);
	//core1.data_bo(data[0]);
	//core1.wr_o(wr[0]);
	forn()
		core1.data_bi[i](input_bus[i]);

	core1.wr_i(is_input);
	
	
	// CORE2

	core2.clk_i(clk);
	//core2.addr_bo(addr[1]);
	//core2.data_bo(data[1]);
	//core2.wr_o(wr[1]);
	forn()
		core2.data_bi[i](input_bus[i]);

	core2.wr_i(is_input);

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
		
	sc_trace(wf, input_bus[0], "input_bus_0");
	sc_trace(wf, input_bus[1], "input_bus_1");
	sc_trace(wf, input_bus[2], "input_bus_2");
	sc_trace(wf, is_input, "is_input");
	
	//sc_trace(wf, out, "out");
	
	
	sc_start(sc_time(150, SC_NS));
	cout << "Core 1 local memory: ";
	core1.get_local_memory();
	cout << endl << "Core 2 local memory: ";
	core2.get_local_memory();
	//cout << endl << "Bus buffer: ";
	//bus.get_mem();
	//cout << endl << "Buffer sum: " << bus.get_buff_sum();
	sc_close_vcd_trace_file(wf);

	return(0);
}