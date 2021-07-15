#include"story.h"

static Actor actors[6];	// キャラクター達
static Array<Dialogue> dialogue;	// セリフ

// ストーリーの初期化
void story_init(int chapter, int story) {
	dialogue = {
		Dialogue(0,1,U"今日はいい天気ですね。",1),
		Dialogue(0,1,U"はい。私もそう思います。", 2),
		Dialogue(-1,-1,U"しばらくして...",0),
		Dialogue(1,2,U"月が綺麗ですね。",1),
		Dialogue(1,2,U"その通りです。",2)
	};
}

// ストーリーの更新関数
// 戻り値: ストーリー再生中の場合は 0
// 　　　  再生を終えた場合は 1 を返す
int story_update() {
	/*** ここを編集してください ***/

	return 0;
}

// ストーリーの描画関数
void story_draw() {
	/*** ここを編集してください ***/
}