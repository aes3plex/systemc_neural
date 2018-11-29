#pragma once
#include "systemc.h"


SC_MODULE(input1) {

	sc_in <bool> clk_i;
	sc_out <bool> out;


	void transform() {
		for (int i(0); i < 5; i++) {
			out.write(1);
			wait(1);
			out.write(0);
			wait(1);
		}
	
	}

	SC_CTOR(input1) {
		SC_CTHREAD(transform, clk_i.pos());
		
	}
};
