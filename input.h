#pragma once

#include "systemc.h"
#include <vector>

#define input_size 3
#define output_size 3
#define forn() for(int i(0); i < input_size; i++)
#define foro() for(int i(0); i < output_size; i++)

using namespace std;

SC_MODULE(input) {

	sc_in<bool>  clk_i;
	sc_out<int>  data_bo[input_size];	// data transmition
	int arr[input_size];


	void send() {

		forn()
			data_bo[i].write(arr[i]);
	}

	SC_CTOR(input) {
		
		forn()
			data_bo[i].initialize(0);

		forn() // Here will be dataset[i] download
			arr[i] = i + 32;

		SC_METHOD(send);
		forn()
			sensitive << clk_i.pos();
		

	}

};