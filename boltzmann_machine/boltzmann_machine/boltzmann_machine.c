#include "boltzmann_machine.h"
#include <stdlib.h>
#include <math.h>

BM *bm_new(static int node_num) {
	BM *bm = (BM *)malloc(sizeof(BM));

	bm->nodeNum = node_num;
	bm->node = (double *)calloc(node_num, sizeof(double));
	bm->bias = (double *)calloc(node_num, sizeof(double));
	bm->weight = (double **)calloc(node_num, sizeof(double *));
	bm->adjacency_matrix = (int **)calloc(node_num, sizeof(int *));

	for (int i = 0; i < node_num; i++) {
		bm->weight[i] = (double *)calloc(node_num, sizeof(double));
		bm->adjacency_matrix[i] = (int *)calloc(node_num, sizeof(int));
	}
}

void *bm_free(BM *bm) {
	free(bm->node);
	free(bm->bias);

	for (int i = 0; i < bm->nodeNum; i++) {
		free(bm->weight[i]);
		free(bm->adjacency_matrix[i]);
	}

	free(bm);

	return NULL;
}

void bm_init(BM *bm) {
	// TODO: パラメータの初期化, 隣接行列の初期化をせよ
}

double bm_conditional_probablity(BM *bm, int node_index, double value) {
	double energy = bm->bias[node_index];

	// 行探索
	for (int i = 0; i < bm->nodeNum; i++) {
		if (i == node_index) continue;
		if (bm->adjacency_matrix[i][node_index] != 1) continue;  // 隣接行列で0の要素は計算しない

		energy += bm->weight[i][node_index] * bm->node[node_index];
	}

	// 列探索
	for (int j = 0; j < bm->nodeNum; j++) {
		if (j == node_index) continue;
		if (bm->adjacency_matrix[node_index][j] != 1) continue;  // 隣接行列で0の要素は計算しない

		energy += bm->weight[node_index][j] * bm->node[node_index];
	}

	return exp(value * energy) / (2 * cosh(energy));
}


double bm_gibbs_sampling(BM *bm, int node_index) {
	double u = bm_uniform();  // 一様乱数
	double prob = bm_conditional_probablity(bm, node_index, -1.0);

	double value = u < prob ? -1.0 : 1.0;

	return value;
}

double bm_uniform() {
	return ((double)rand() + 1.0) / ((double)RAND_MAX + 2.0);
}

double bm_update_by_gibbs_sampling(BM *bm, int node_index) {
	double value = bm_gibbs_sampling(bm, node_index);
	bm->node[node_index] = value;

	return value;
}
