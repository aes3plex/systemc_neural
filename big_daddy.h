#pragma once
#include "systemc.h"
#include "input1.h"
#include "AND2.h"

SC_MODULE(big_daddy) {

	sc_in <bool> in;
	sc_out <bool> out;

	AND2 AND2;
	input1 input1;

	sc_signal<bool> inv_out;

	SC_CTOR(big_daddy): AND2("AND2"), input1("input1") {
		
		input1.clk_i(in);
		input1.out(inv_out);
		
		AND2.clk_i(in);
		AND2.a(inv_out);
		AND2.out(out);
	}
};