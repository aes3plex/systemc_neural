#pragma once
#include "systemc.h"


SC_MODULE(AND2) {
	
	sc_in <bool> clk_i;
	sc_in <bool> a;
	sc_out <bool> out;


	void add() {
	
			out.write(clk_i.read() || a.read());

	}
	
	SC_CTOR(AND2) {
		SC_METHOD(add);
		sensitive << clk_i.pos() << clk_i.neg();
	}
};

