#include"puzzle.h"

static Grid<int> stage_data;	// ステージ情報

static Player player;

// パズルの初期化
void puzzle_init(int diff, int stage) {

	// ステージ読み込み

	stage_data = {
		{1,1,1,1,1,1,1},
		{1,1,1,0,0,3,1},
		{1,1,1,0,0,0,1},
		{1,0,0,2,0,0,1},
		{1,0,0,0,1,1,1},
		{1,0,0,0,1,1,1},
		{1,1,1,1,1,1,1}
	};

	// プレイヤー初期座標
	player.i = 5;
	player.j = 1;

	player.x = 130;
	player.y = 250;
	player.width = 30;
	player.height = 30;

	if (player.x < 100) player.x = 100;
	if (player.x > 250) player.x = 250;
	if (player.y < 100) player.y = 100;
	if (player.y > 250) player.y = 250;

	if (player.i < 0) player.i = 0;
	if (player.i > stage_data.height()) player.i = stage_data.height();
	if (player.j < 0) player.j = 0;
	if (player.j > stage_data.width()) player.j = stage_data.width();


}

// パズルの更新関数
// 戻り値: パズルを続行中の場合は 0
// 　　　  クリアした場合は 1 を返す
int puzzle_update() {
	/*** ここを編集してください ***/

	//プレイヤー移動
	if (KeyLeft.down()) {
		if (playerstack('x',-1)) {
			player.x -= player.width;
			player.j--;
		}
	}
	if (KeyRight.down()) {
		if (playerstack('x', 1)) {
			player.x += player.width;
			player.j++;
		}
	}
	if (KeyUp.down()) {
		if (playerstack('y', -1)) {
			player.y -= player.height;
			player.i--;
		}
	}
	if (KeyDown.down()) {
		if (playerstack('y', 1)) {
			player.y += player.height;
			player.i++;
		}
	}

	if (stage_data[player.i][player.j] == 3) {
		return 1;
	}

	return 0;
}

// パズルの描画関数
void puzzle_draw() {



	/*** ここを編集してください ***/

	for (int i = 0; i < stage_data.width(); i++) {
		for (int j = 0; j < stage_data.height(); j++) {
			switch (stage_data[i][j]) {
			case 0:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Green);
				break;

			case 1:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Gray);
				break;

			case 2:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Orange);
				break;

			case 3:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Yellow);
				break;


			case 4:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Black);
				break;



			}
		}
	}
	//主人公
	Rect(player.x, player.y, 30, 30).draw(Palette::Blue);
}

bool objstack(char t, int n) {
	int data = -1;

	if (t == 'x') {
		if (n > 0) {
			data = stage_data[player.i][player.j + 2];
		}
		else {
			data = stage_data[player.i][player.j - 2];
		}
	}
	else if (t == 'y') {
		if (n > 0) {
			data = stage_data[player.i + 2][player.j];
		}
		else {
			data = stage_data[player.i - 2][player.j];
		}
	}

	if (data == 0 || data == 3 || data == 5) {
		return true;
	}
	else {
		return false;
	}
}

bool playerstack(char t, int n) {
	int data = -1;

	if (t == 'x') {
		if (n > 0) {
			data = stage_data[player.i][player.j + 1];
		}
		else {
			data = stage_data[player.i][player.j - 1];
		}
	}
	else if (t == 'y') {
		if (n > 0) {
			data = stage_data[player.i + 1][player.j];
		}
		else {
			data = stage_data[player.i - 1][player.j];
		}
	}
	else
		return false;

	if (data == 0 || data == 3 || data == 5) {
		return true;
	}
	else if (data == 2 || data == 4) {
		return objstack(t, n);
	}
	else {
		return false;
	}
}