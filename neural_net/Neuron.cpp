#include <random>
#include "Neuron.h"


Neuron::Neuron() {
	inputs_size = 49; // 
	inputs.resize(inputs_size);
	output = 0;


	for (int i(0); i < inputs_size; i++) {
		inputs[i] = 0.45 - (double)rand() / (RAND_MAX); //initial weight for synapses 
	}
}

Neuron::~Neuron() {
	inputs.clear();
}

void Neuron::set_inputs(int input_num, float new_weight) {
	inputs[input_num] = new_weight;
}

vector<float> Neuron::get_inputs() {
	return inputs;
}

void Neuron::set_output(float value) {
	output = value;
}

float Neuron::get_output() {
	return output;
}

void Neuron::get_neuro() {
	cout << "Inputs: ";
	for (unsigned i(0); i < inputs.size(); i++) {
		printf("%.6f ", inputs[i]);
	}
	cout << "Output: " << output << endl;
}


