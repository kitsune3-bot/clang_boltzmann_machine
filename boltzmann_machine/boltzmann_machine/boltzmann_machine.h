#pragma once
#include <stdlib.h>

typedef struct {
	int nodeNum;  // ノード数
	double *node;  // ノード変数
	double *bias;  //バイアス
	double **weight;  // ウェイト
	int ** adjacency_matrix;  // 隣接行列(全結合BMだと別になくてもいいけど)
} BM;

typedef struct {
	int dataSize;
	int nodeNum;
	int dataset;  // dataset[DATA_INDEX][NODE_INDEX]
} BM_DATASET;

/**
* @fn
* ボルツマンマシン構造体確保
* @param (node_num) ノード数
* @return ボルツマンマシン構造体のポインタ
*/
BM *bm_new(static int node_num);

/**
* @fn
* ボルツマンマシン構造体解放, 二重解放予防にNULL返す
* @param (node_num) ボルツマンマシン構造体のポインタ
* @return NULL
*/
void *bm_free(BM *bm);

/**
* @fn
* ボルツマンマシン構造体のパラメータ初期化
* @param (bm) ボルツマンマシン構造体のポインタ
*/
void bm_init(BM *bm);

/**
* @fn
* ボルツマンマシンの条件付き確率
* @param (bm) ボルツマンマシン構造体のポインタ
* @param (node_index) ノード番号
* @param (value) 値
* @return 確率値
*/
double bm_conditional_probablity(BM *bm, int node_index, double value);

/**
* @fn
* ボルツマンマシンのギブスサンプリング(x_i \in {-1, +1})
* @param (bm) ボルツマンマシン構造体のポインタ
* @param (node_index) ノード番号
* @return サンプル値
*/
double bm_gibbs_sampling(BM *bm, int node_index);

/**
* @fn
* [0, 1]の乱数(一応インターフェースのつもり, 適当に実装してもらいたし。)
* @return 乱数値
*/
double bm_uniform();

/**
* @fn
* ギブスサンプリングによるボルツマンマシンの更新
* @param (bm) ボルツマンマシン構造体のポインタ
* @param (node_index) ノード番号
* @return サンプル値
*/
double bm_update_by_gibbs_sampling(BM *bm, int node_index);

