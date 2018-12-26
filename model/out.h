#pragma once

#include "systemc.h"

using namespace std;

SC_MODULE(out_module) {

	sc_in<bool>  clk_i;
	sc_in<int>  data_out_bi;	// reading data
	sc_in<bool>	wr_out_i;		// reading flag
	sc_out<int> out_to_out;		// writing OUTPUT
	 
	// get out array
	vector<int> get_out() {
		return out_arr;
	}

	// parsing result
	void parsing_result(vector<int> out) {
		if (out[0] == 1 && out[1] == 0 && out[2] == 0)
			cout << "SQUARE";

		else if (out[0] == 0 && out[1] == 1 && out[2] == 0)
			cout << "TRIANGLE";

		else if (out[0] == 0 && out[1] == 0 && out[2] == 1)
			cout << "CIRCLE";

		else 
			cout << "CAN'T RECOGNIZE";
	}

	// arrays comparison
	bool is_equal(vector<int> v1, vector<int> v2) {
		if (v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2])
			return true;
		else
			return false;
	}

	//out main thread
	void give_me_out()
	{
		wait();
		wait();
		for (int i(0), temp = 0; i < 29; i++) {
			wait();
			if (wr_out_i.read()) {
				buff[temp] = data_out_bi.read();
				temp++;
			}
		}
		wait();

		for (int i(0); i < 3; i++) {
			arr1[i] = buff[i];
			arr2[i] = buff[i + 3];
			arr3[i] = buff[i + 6];
		}

		if (is_equal(arr1, arr2) || is_equal(arr1, arr3))
			out_arr = arr1;

		if (is_equal(arr2, arr3))
			out_arr = arr2;
	
		for (int i(0); i < 3; i++) {
			out_to_out.write(out_arr[i]);
			wait();
		}

		out_to_out.write(0);
	
	}

	SC_CTOR(out_module) {

		out_to_out.initialize(0);
		arr1.resize(3);
		arr2.resize(3);
		arr3.resize(3);
		out_arr.resize(3);

		for (int i(0); i < 9; i++)
			buff[i] = 0;

		SC_CTHREAD(give_me_out, clk_i.pos());

	}

private:
	int buff[9];
	vector<int> arr1, arr2, arr3, out_arr;
};