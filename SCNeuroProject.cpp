#include <iostream>
#include "systemc.h"
#include "core.h"
#include "memory.h"


int sc_main(int argc, char* argv[]) {
	core core("core");
	memory memory("memory");
	sc_clock clk("clk", sc_time(10, SC_NS));
	sc_signal<int> addr;
	sc_signal<int> data;
	sc_signal<bool> wr;
	sc_signal<bool> rd;
	sc_signal<int> mem_out[3];


	core.clk_i(clk);
	core.addr_bo(addr);
	core.data_bo(data);
	core.wr_o(wr);
	core.wr_f(rd);

	memory.clk_i(clk);
	memory.addr_bi(addr);
	memory.data_bi(data);
	memory.wr_i(wr);
	memory.is_wr_f(rd);
	
	
	for (unsigned i(0); i < 3; i++) {
		memory.data_bo[i](mem_out[i]);
	}
	


	sc_trace_file *wf = sc_create_vcd_trace_file("wave");
	sc_trace(wf, clk, "clk");
	sc_trace(wf, addr, "addr");
	sc_trace(wf, data, "data");
	sc_trace(wf, wr, "wr");
	sc_trace(wf, rd, "rd");
	
	for(int i(0); i < 3; i++){
		sc_trace(wf, mem_out[i], "mem_out");
	}
	
	sc_start(sc_time(150, SC_NS));
	memory.get_mem();
	//sc_start();
	sc_close_vcd_trace_file(wf);

	return(0);
}