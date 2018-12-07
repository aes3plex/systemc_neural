#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Neuron {

	vector <float> inputs;
	int inputs_size;
	float output;

public:
	Neuron();
	~Neuron();

	void set_inputs(int input_num, float new_weight);
	vector<float> get_inputs();

	void set_output(float value);
	float get_output();

	void get_neuro();

};