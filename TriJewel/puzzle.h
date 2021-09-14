#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <siv3D.hpp>

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

void puzzle_init(int, int);		// パズルの初期化
int puzzle_update();	// パズルの更新関数
void puzzle_draw();		// パズルの描画関数

bool objmove();	 //	岩、箱が動くかの判定
bool playermove();	//プレイヤーの動く判定

#endif