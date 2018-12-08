#pragma once

#include "systemc.h"
#include <vector>
#include "BigDaddy.h"

#define train_dim 49
#define ideal_dim 3
#define set_size 6

#define for_train() for(int i(0); i < train_dim; i++)
#define for_ideal() for(int i(0); i < ideal_dim; i++)

using namespace std;

SC_MODULE(input) {

	sc_in<bool>  clk_i;
	sc_out <int> train_data_o[train_dim];	// writing dataset
	sc_out <int> ideal_data_o[ideal_dim];	// writing ideals
	sc_out <int> test_o[train_dim];			// writing test
	sc_out <bool> wr_o;						// writing flag

	vector<vector<int>> train_arr;
	vector<vector<int>> ideal_arr;
	vector<int> test_arr;

	// input main thread
	void core_write() {
		wait();
		wr_o.write(1);
		
		
			for (int j(0); j < set_size; j++) {
			
				for_train() 
					train_data_o[i].write(train_arr[j][i]);
					

				for_ideal() 
					ideal_data_o[i].write(ideal_arr[j][i]);
				

				for_train()
					test_o[i].write(test_arr[i]);


				wait();
			}
		
		wr_o.write(0);
		
		for_train() 
			train_data_o[i].write(0);
			
		for_ideal()
			ideal_data_o[i].write(0);
		
		for_train()
			test_o[i].write(0);
		
	}

	SC_CTOR(input) {
		
		wr_o.initialize(0);

		for_train()
			train_data_o[i].initialize(0);

		for_ideal()
			ideal_data_o[i].initialize(0);

		
		train_arr.resize(set_size);
		for (int i(0); i < set_size; i++)
			train_arr[i].resize(train_dim);

		ideal_arr.resize(set_size);
		for (int i(0); i < set_size; i++)
			ideal_arr[i].resize(ideal_dim);

		test_arr.resize(train_dim);
		
		for (int j(0); j < set_size; j++) {
			for_train()
				train_arr[j][i] = from_file("txt_files/dataset.txt", set_size, train_dim)[j][i];
		}

		for (int j(0); j < set_size; j++) {
			for_ideal()
				ideal_arr[j][i] = from_file("txt_files/ideals.txt", set_size, ideal_dim)[j][i];
		}

		ifstream fin("txt_files/test_triangle.txt");
		while (!fin.eof()) {
			for (int i(0); i < train_dim; i++) 
				fin >> test_arr[i];
		}
		
		
		SC_CTHREAD(core_write, clk_i.pos());

	}

};


