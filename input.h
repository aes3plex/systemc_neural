#pragma once

#include "systemc.h"
#include <vector>
#include "func.h"

#define input_size 3
#define output_size 3
#define forn() for(int i(0); i < input_size; i++)
#define foro() for(int i(0); i < output_size; i++)

using namespace std;

SC_MODULE(input) {

	sc_in<bool>  clk_i;
	sc_out<int>  data_bo[input_size];	// data transmition
	sc_out<bool> wr_o;
	vector<vector<int>> arr;
	

	void core_write() {
		wait();
		wr_o.write(1);
		for (int j(0); j < 2; j++) {
			
			forn() {
				data_bo[i].write(arr[j][i] + return_22());
				}

			wait();
		}
		
		wr_o.write(0);
		forn()
			data_bo[i].write(0);
		
	}

	//void send() {

	//	forn()
	//		data_bo[i].write(arr[i]);
	//}

	SC_CTOR(input) {
		
		wr_o.initialize(0);

		forn()
			data_bo[i].initialize(0);

		arr.resize(input_size);

		arr = { { 3, 4, 5 }, {6, 7, 8} };
	
		/*
		SC_METHOD(send);
		forn()
			sensitive << clk_i.pos();
		*/

		SC_CTHREAD(core_write, clk_i.pos());

	}

};