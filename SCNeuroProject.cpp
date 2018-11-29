#include <iostream>
#include "systemc.h"
#include "big_daddy.h"


int sc_main(int argc, char* argv[]) {
	big_daddy big_daddy("big_daddy");
	sc_clock clk("clk", sc_time(10, SC_NS));
	sc_signal<bool> out;

	big_daddy.in(clk);
	big_daddy.out(out);


	sc_trace_file *wf = sc_create_vcd_trace_file("wave");
	sc_trace(wf, clk, "clk");
	sc_trace(wf, out, "out");


	sc_start(sc_time(60, SC_NS));

	sc_close_vcd_trace_file(wf);

	return(0);
}