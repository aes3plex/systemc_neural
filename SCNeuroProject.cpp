#include <iostream>
#include "systemc.h"
#include "core.h"
#include "memory.h"
#include "input.h"


int sc_main(int argc, char* argv[]) {
	
	//memory memory("memory");
	core core("core");
	input input("input");

	sc_clock clk("clk", sc_time(10, SC_NS));
	sc_signal<int> addr;
	sc_signal<int> data;
	sc_signal<bool> wr;
	sc_signal<bool> rd;
	sc_signal<int> input_bus[input_size];


	input.clk_i(clk);
	forn()
		input.data_bo[i](input_bus[i]);

	core.clk_i(clk);
	core.addr_bo(addr);
	core.data_bo(data);
	core.wr_o(wr);
	core.wr_f(rd);

	forn()
		core.data_bi[i](input_bus[i]);


	/*
	memory.clk_i(clk);
	memory.addr_bi(addr);
	memory.data_bi(data);
	memory.wr_i(wr);
	memory.is_wr_f(rd);
	
	
	*/
	


	sc_trace_file *wf = sc_create_vcd_trace_file("wave");
	sc_trace(wf, clk, "clk");
	sc_trace(wf, addr, "addr");
	sc_trace(wf, data, "data");
	sc_trace(wf, wr, "wr");
	sc_trace(wf, rd, "rd");
	
	forn()
		sc_trace(wf, input_bus[i], "mem_out");
	
	
	sc_start(sc_time(150, SC_NS));
	core.get_local_memory();
	//sc_start();
	sc_close_vcd_trace_file(wf);

	return(0);
}