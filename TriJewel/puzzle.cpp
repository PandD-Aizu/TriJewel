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
	player.height = 30;
	player.width = 30;
}

// パズルの更新関数
// 戻り値: パズルを続行中の場合は 0
// 　　　  クリアした場合は 1 を返す
int puzzle_update() {
	/*** ここを編集してください ***/

	//プレイヤー移動
	if (KeyLeft.down()) {
		if (player.i - 1 == (0 || 3 || 5)) {
			player.i--;
		}
		else if (player.i - 1 == (2 || 4)) {
			if (player.i - 2 == (0 || 3 || 5)) {
				player.i--;
			}
		}
	}
	if (KeyRight.down()) {
		if (player.i + 1 == (0 || 3 || 5)) {
			player.i++;
		}
		else if (player.i + 1 == (2 || 4)) {
			if (player.i + 2 == (0 || 3 || 5)) {
				player.i++;
			}
		}
	}
	if (KeyUp.down()) {
		if (player.j - 1 == (0 || 3 || 5)) {
			player.j--;
		}
		else if (player.j - 1 == (2 || 4)) {
			if (player.j - 2 == (0 || 3 || 5)) {
				player.j--;
			}
		}
	}
	if (KeyDown.down()) {
		if (player.j + 1 == (0 || 3 || 5)) {
			player.j++;
		}
		else if (player.j + 1 == (2 || 4)) {
			if (player.j + 2 == (0 || 3 || 5)) {
				player.j++;
			}
		}
	}

	return 0;
}

// パズルの描画関数
void puzzle_draw() {
	/*** ここを編集してください ***/
}

bool objmove() {

}

bool playermove() {

}