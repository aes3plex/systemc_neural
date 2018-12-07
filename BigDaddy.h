#include <iostream>
#include <vector>
#include "Neuron.h"
#include "Layer.h"
#include <fstream>


using namespace std;

float error_is(vector<float> actual, vector<float> ideal);

vector<float> print_layer(Layer layer);

vector<float> war(vector<Layer> fit_net, vector<float> what_is_it);

vector<vector<float>> from_file(string filename, int set_size, int elements_in_set);

