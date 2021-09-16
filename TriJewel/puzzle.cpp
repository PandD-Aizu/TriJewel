#include"puzzle.h"

static Grid<int> stage_data;	// ステージ情報

static Player player;

// パズルデータ用ファイル読み込み
void readfile(String file) {
	TextReader reader;
	String line;

	if (!reader.open(file)) {
		throw Error(U"Failed to open `" + file + U"`");
	}

	std::stringstream ss;

	stage_data = Grid<int>(STAGE_SIZE, STAGE_SIZE);

	int i = 0;
	while (reader.readLine(line)) {
		ss << line;
		if (i < STAGE_SIZE) {
			for (int j = 0; j < STAGE_SIZE; j++) {
				ss >> stage_data[i][j];
			}
		}

		else {
			ss >> player.i;
			ss >> player.j;
		}

		i++;
	}

	player.x = 100 + player.j * 30;
	player.y = 100 + player.i * 30;

	reader.close();
}

// パズルの初期化
void puzzle_init(int diff, int stage) {


	// ステージ読み込み
	readfile(U"./Data/Stage/test.txt");

	/*
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
	*/

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

	if (stage_data[player.i][player.j] == GOAL) {
		return 1;
	}

	return 0;
}

// パズルの描画関数
void puzzle_draw() {



	/*** ここを編集してください ***/

	for (int i = 0; i < stage_data.width(); i++) {
		for (int j = 0; j < stage_data.height(); j++) {
			TextureAsset(U"road").draw(100 + j * 30, 100 + i * 30);

			switch (stage_data[i][j]) {
			case ROAD:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Green);
				TextureAsset(U"road").draw(100 + j * 30, 100 + i * 30);
				break;

			case WALL:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Gray);
				TextureAsset(U"wall").draw(100 + j * 30, 100 + i * 30);
				break;

			case ROCK:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Orange);
				TextureAsset(U"rock").draw(100 + j * 30, 100 + i * 30);
				break;

			case GOAL:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Yellow);
				TextureAsset(U"goal").draw(100 + j * 30, 100 + i * 30);
				break;

			case BOX:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Black);
				TextureAsset(U"box").draw(100 + j * 30, 100 + i * 30);
				break;

			case PLACE:
				TextureAsset(U"place").draw(100 + j * 30, 100 + i * 30);
				break;

			case DOOR:
				TextureAsset(U"door").draw(100 + j * 30, 100 + i * 30);
				break;

			default:
				break;
			}
		}
	}
	//主人公
	//Rect(player.x, player.y, 30, 30).draw(Palette::Blue);
	TextureAsset(U"player").draw(player.x, player.y);
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

	if (data == ROAD || data == GOAL || data == PLACE) {
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

	if (data == ROAD || data == GOAL || data == PLACE) {
		return true;
	}
	else if (data == ROCK || data == BOX) {
		return objstack(t, n);
	}
	else {
		return false;
	}
}