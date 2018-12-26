#include "Neuron.h"

using namespace std;

class Layer {

	static int layers_amount;
	vector<Neuron> layer;
	vector<float> deltas;
	int layer_size;
	int number_of_layer;
	float E;

public:
	Layer(int size);
	~Layer();

	void set_first_layer_outputs(vector<float> values);
	void set_layer_outputs(Layer prev_layer);
	vector<float> get_layer_outputs();
	vector<Neuron> get_layer();
	int get_layer_size();
	Neuron get_neuron(int numb);
	void set_last_layer_deltas(vector<float> ideal);
	void set_deltas(Layer &next_layer);
	vector<float> get_deltas();
	void set_neuron_inputs(int neuron, int input, float value);
	int get_layer_number();
};
