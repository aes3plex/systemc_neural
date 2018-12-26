#include "BigDaddy.h"

float error_is(vector<float> actual, vector<float> ideal) {
	if (actual.size() == ideal.size()) {
		float summ = 0, count = 0;
		for (unsigned i(0); i < actual.size(); i++) {
			count++;
			summ += ideal[i] - actual[i];
		}

		return abs(summ / count);
	}
	else {
		cout << "False dimensions";
	}
}

vector<float> print_layer(Layer layer) {

	vector<float> output(layer.get_layer_size());

	for (int i(0); i < layer.get_layer_size(); i++)
		output[i] = layer.get_neuron(i).get_output();

	return output;
}

vector<float> war(vector<Layer> fit_net, vector<float> what_is_it) {
	
	vector<float> out(3);

	fit_net[0].set_first_layer_outputs(what_is_it);
	fit_net[1].set_layer_outputs(fit_net[0]);
	fit_net[2].set_layer_outputs(fit_net[1]);

	for(int i(0); i < 3; i++)
		out[i] = fit_net[2].get_neuron(i).get_output();

	return out;
}

vector<vector<float>> from_file(string filename, int set_size, int elements_in_set) {
	ifstream fin(filename);
	vector<vector<float>> dataset(set_size, vector<float>(elements_in_set));
	while (!fin.eof()) {
		for (int i(0); i < set_size; i++) {
			for (int j(0); j < elements_in_set; j++)
				fin >> dataset[i][j];
		}
	}

	return dataset;
}

vector<int> convert(vector<float> out) {
	vector<int> int_out(out.size());
	for (int i(0); i < int_out.size(); i++) {
		if (out[i] > 0.90)
			int_out[i] = 1;
		else
			int_out[i] = 0;
	}

	return int_out;
} 