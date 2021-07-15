#ifndef _STORY_H_
#define _STORY_H_

#include <siv3D.hpp>

// アクター
typedef struct {
	int id;	// 番号
	s3d::String name;	// 名前
	int x, y;	// 座標
	int width, height;	// 横の長さ、縦の長さ
}Actor;

// セリフ
typedef struct {
	int left, right;	// 左に立つキャラ、右に立つキャラ(各キャラには 0～5 の番号が割り振られます。-1の場合、キャラは表示されません)
	s3d::String text;	// セリフ
	int speaker;	// 話者(0: 誰も喋らない、1: 左のキャラ、2: 右のキャラ)
}Dialogue;

void story_init(int, int);	// ストーリーの初期化
int story_update();	// ストーリーの更新関数
void story_draw();	// ストーリーの描画関数

#endif