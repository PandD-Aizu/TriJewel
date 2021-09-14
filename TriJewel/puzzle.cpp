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
		if (playerstack('x',-1)) {
			player.i--;
		}
	}
	if (KeyRight.down()) {
		if (playerstack('x', 1)) {
			player.i++;
		}
	}
	if (KeyUp.down()) {
		if (playerstack('y', -1)) {
			player.j--;
		}
	}
	if (KeyDown.down()) {
		if (playerstack('y', 1)) {
			player.j++;
		}
	}

	return 0;
}

// パズルの描画関数
void puzzle_draw() {
	/*** ここを編集してください ***/
}

bool objstack(char t, int n) {
	int data;

	if (strcmp(&t, "x")) {
		if (n > 0) {
			data = stage_data[player.i + 2][player.j];
		}
		else {
			data = stage_data[player.i - 2][player.j];
		}
	}
	if (strcmp(&t, "y")) {
		if (n > 0) {
			data = stage_data[player.i][player.j + 2];
		}
		else {
			data = stage_data[player.i][player.j - 2];
		}
	}

	if (data == (0 || 3 || 5)) {
		return true;
	}
	else {
		return false;
	}
}

bool playerstack(char t, int n) {
	int data;

	if (strcmp(&t, "x")) {
		if (n > 0) {
			data = stage_data[player.i + 1][player.j];
		}
		else {
			data = stage_data[player.i - 1][player.j];
		}
	}
	if (strcmp(&t, "y")) {
		if (n > 0) {
			data = stage_data[player.i][player.j + 1];
		}
		else {
			data = stage_data[player.i][player.j - 1];
		}
	}
	else
		return false;

	if (data == (0 || 3 || 5)) {
		return true;
	}
	else if (data == (2 || 4)) {
		return objstack(t, n);
	}
	else {
		return false;
	}
}