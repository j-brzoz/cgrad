#include "../src/data_structs/value.h"
#include "../src/data_structs/array.h"
#include "../src/backward.h"
#include "../src/data_structs/neuron.h"
#include "../src/data_structs/layer.h"
#include "../src/data_structs/mlp.h"
#include "../src/loss.h"
#include "../src/data_structs/input.h"
#include "../src/data_structs/output.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t* id = NULL;
val_array_p global_array = NULL;

int main() {
	srand(time(NULL));

	// mlp structure	
	size_t* n = malloc(sizeof(size_t) * 3);
	n[0] = 4;
	n[1] = 4;
	n[2] = 1;
	mlp_p m = make_mlp(3, 3, n);
	
	// reading in input
	FILE *input_file = fopen("example/input.txt", "r");
	input_p in = read_input(input_file);
	fclose(input_file);

	// reading desired output
	FILE *output_file = fopen("example/output.txt", "r");
	output_p out = read_output(output_file);
	fclose(output_file);

	// training
	train_mlp(m, 50, in, out, 0.1, 1);
	
	// freeing memory
	free_input(in);
	free_output(out);
	free_mlp(m);
	free_val_array(global_array);
	free(id);
	return 0;
}
