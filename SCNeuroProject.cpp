#include <iostream>
#include "systemc.h"
#include "core.h"
#include "memory.h"
#include "input.h"
#include "bus.h"


int sc_main(int argc, char* argv[]) {
	
	//memory memory("memory");
	core core1("core1"), core2("core2");
	bus bus("bus");
	//input input("input");

	sc_clock clk("clk", sc_time(10, SC_NS));
	sc_signal<int> addr[2];
	sc_signal<int> data[2];
	sc_signal<bool> wr[2];

	//sc_signal<bool> rd;
	//sc_signal<int> input_bus[input_size];

	/*
	input.clk_i(clk);
	forn()
		input.data_bo[i](input_bus[i]);
*/
	
	
	core1.clk_i(clk);
	core1.addr_bo(addr[0]);
	core1.data_bo(data[0]);
	core1.wr_o(wr[0]);
	


	/*
	forn()
		core1.data_bi[i](input_bus[i]);
	
	*/
	core2.clk_i(clk);
	core2.addr_bo(addr[1]);
	core2.data_bo(data[1]);
	core2.wr_o(wr[1]);
	
	bus.clk_i(clk);

	for_bus()
		bus.addr_bi[i](addr[i]);
	
	for_bus()
		bus.data_bi[i](data[i]);
	
	for_bus()
		bus.wr_i[i](wr[i]);
	

	
	/*
	forn()
		core2.data_bi[i](input_bus[i]);

	
	memory.clk_i(clk);
	memory.addr_bi(addr);
	memory.data_bi(data);
	memory.wr_i(wr);
	memory.is_wr_f(rd);
	
	*/
	
	


	sc_trace_file *wf = sc_create_vcd_trace_file("wave");
	sc_trace(wf, clk, "clk");
	
	for_bus()
		sc_trace(wf, addr[i], "addr");

	for_bus()
		sc_trace(wf, data[i], "data");

	for_bus()
		sc_trace(wf, wr[i], "wr");
	
	/*
	forn()
		sc_trace(wf, input_bus[i], "mem_out");
	*/
	
	sc_start(sc_time(150, SC_NS));
	bus.get_mem();
	sc_close_vcd_trace_file(wf);

	return(0);
}