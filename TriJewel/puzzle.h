#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <siv3D.hpp>

#define STAGE_SIZE 12

#define ROAD 0
#define WALL 1
#define ROCK 2
#define GOAL 3
#define BOX 4
#define PLACE 5
#define DOOR 6

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// プレイヤー
typedef struct {
	int i, j;	// 添え字
	int x, y;	// 座標
	int width, height;	// 横の長さ、縦の長さ
	int direction;	// 方向
}Player;

// ブロック
typedef struct {
	int i, j;	// 添え字
	int x, y;	// 座標
	int width, height;	// 横の長さ、縦の長さ
	int type;	// 方向
	int flag;	// 扉がしまっているかのフラグ
}Block;

void readfile(String); // パズルデータ用ファイル読み込み
void puzzle_init(int, int);		// パズルの初期化
int puzzle_update();	// パズルの更新関数
void puzzle_draw();		// パズルの描画関数

void baseinit();		// base_dataの初期化関数

bool objstack(char, int);	 //	岩、箱が動くかの判定
bool playerstack(char, int);		//プレイヤーが動けるかの判定

void objmove(char, int);	//岩、箱の移動処理

bool checkdoor();		//扉が開くかの判定
#endif