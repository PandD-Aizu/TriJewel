#include"puzzle.h"

static Grid<int> stage_data;	// ステージ情報
static Player player;

// パズルの初期化
void puzzle_init(int diff, int stage) {

	// ステージ読み込み
	stage_data = {
		{1,1,0,0,3},
		{1,1,0,0,0},
		{0,0,2,0,0},
		{0,0,0,1,1},
		{0,0,0,1,1}
	};

	// プレイヤー初期座標
	player.i = 4;
	player.j = 0;
}

// パズルの更新関数
// 戻り値: パズルを続行中の場合は 0
// 　　　  クリアした場合は 1 を返す
int puzzle_update() {
	/*** ここを編集してください ***/

	return 0;
}

// パズルの描画関数
void puzzle_draw() {
	/*** ここを編集してください ***/
}