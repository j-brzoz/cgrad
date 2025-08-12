#include "../src/ml_structs/value.h"
#include "../src/data_structs/array.h"
#include "../src/backward.h"
#include "../src/ml_structs/neuron.h"
#include "../src/ml_structs/layer.h"
#include "../src/ml_structs/mlp.h"
#include "../src/loss.h"
#include "../src/io/input.h"
#include "../src/io/output.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
	srand(time(NULL));

	value_system_init();

	// mlp structure	
	size_t* n = malloc(sizeof(size_t) * 3);
	n[0] = 8;
	n[1] = 8;
	n[2] = 1;
	mlp_p m = make_mlp(3, 3, n);
	
	// reading in input
	FILE *input_file = fopen("big_example/input.txt", "r");
	input_p in = read_input(input_file);
	fclose(input_file);
	get_stats_input(in);
	scale_input(in);

	// reading desired output
	FILE *output_file = fopen("big_example/output.txt", "r");
	output_p out = read_output(output_file);
	fclose(output_file);
	get_stats_output(out);
	scale_output(out);

	// training
	train_mlp(m, 20, in, out, 0.1, 100, mean_sqr_error, 1);

	// get results
	double final_loss = evaluate_mlp(m, in, out, mean_sqr_error, "results.txt");
	printf("Final loss: %f\n", final_loss);

	// freeing memory
	free_input(in);
	free_output(out);
	free_mlp(m);
	value_system_cleanup();
	return 0;
}
