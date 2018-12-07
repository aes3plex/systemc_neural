#include <vector>
#include "Layer.h"
#include <math.h>

#define e_speed 5

using namespace std;

int Layer::layers_amount = 0;

float sigmoid(float arg) {

	return 1 / (1 + exp(-arg));

}

float sigmoid_d(float arg) {

	return arg * (1 - arg);

}

Layer::Layer(int size) {
	layers_amount++;
	number_of_layer = layers_amount;
	layer.resize(size);
	layer_size = size;
	E = e_speed + get_layer_number() / 3;
}

Layer::~Layer() {
	layer.clear();
}

void Layer::set_first_layer_outputs(vector<float> values) {

	for (int i(0); i < layer_size; i++) 
		layer[i].set_output(values[i]);

}

void Layer::set_layer_outputs(Layer prev_layer) {
	for (int i(0); i < layer_size; i++) {
		float count = 0;
		for (int j(0); j < prev_layer.get_layer_size(); j++) {
			count += prev_layer.get_neuron(j).get_output() * layer[i].get_inputs()[j];
		}
		layer[i].set_output(sigmoid(count));
	}
}

vector<float> Layer::get_layer_outputs() {
	vector<float> outputs(layer_size);
	for (int i(0); i < layer_size; i++) {
		outputs[i] = layer[i].get_output();
	}

	return outputs;
}

vector<Neuron> Layer::get_layer() {
	return layer;
}

int Layer::get_layer_size() {
	return layer_size;
}

Neuron Layer::get_neuron(int numb) {
	return layer[numb];
}

void Layer::set_last_layer_deltas(vector<float> ideal) {
	vector<float> deltas_in(layer_size);
	if (layer_size == ideal.size()) {
		for (int i(0); i < deltas_in.size(); i++) {
			deltas_in[i] = sigmoid_d(layer[i].get_output()) * (ideal[i] - layer[i].get_output());
		}
		deltas = deltas_in;
	}
	else {
		cout << "False dimensions";
	}
}

vector<float> Layer::get_deltas() {
	return deltas;
}

void Layer::set_deltas(Layer &next_layer) {
	vector<float> deltas_in(layer_size);

	for (int i(0); i < layer_size; i++) {
		float counter = 0;
		for (int j(0); j < next_layer.layer_size; j++) {
			counter += next_layer.get_deltas()[j] * next_layer.get_neuron(j).get_inputs()[i];
		}

		deltas_in[i] = sigmoid_d(layer[i].get_output()) * counter;


		for (int j(0); j < next_layer.layer_size; j++) {
			float grad = layer[i].get_output() * next_layer.get_deltas()[j];
			float weight_change = E * grad;
			next_layer.set_neuron_inputs(j, i, next_layer.get_neuron(j).get_inputs()[i] + weight_change);

		}
	}

	deltas = deltas_in;
}

void Layer::set_neuron_inputs(int neuron, int input, float value) {
	layer[neuron].set_inputs(input, value);
}

int Layer::get_layer_number() {
	return number_of_layer;
}