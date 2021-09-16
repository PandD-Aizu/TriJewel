#include"puzzle.h"

static Grid<int> stage_data;	// ステージ情報
static Grid<int> stage_data_init;	// ステージ情報(初期状態)

static Player player;	// プレイヤー
static Array<Player> player_log;	// プレイヤーの移動ログ

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

	player.direction = UP;

	reader.close();
}

// パズルの初期化
void puzzle_init(int diff, int stage) {


	// ステージ読み込み
	readfile(U"./Data/Stage/test.txt");
	stage_data_init = Grid<int>(stage_data.width(), stage_data.height());
	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			stage_data_init[i][j] = stage_data[i][j];
		}
	}

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

	base_data = Grid<int>(stage_data.width(), stage_data.height(), -1);
	baseinit();

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

	player_log.clear();
	player_log << player;
}

// パズルの更新関数
// 戻り値: パズルを続行中の場合は 0
// 　　　  クリアした場合は 1 を返す
int puzzle_update() {
	/*** ここを編集してください ***/

	//プレイヤー移動
	if (KeyLeft.down()) {
		player.direction = LEFT;

		if (playerstack('x',-1)) {
			player.x -= player.width;
			player.j--;
		}

		player_log << player;
	}
	if (KeyRight.down()) {
		player.direction = RIGHT;

		if (playerstack('x', 1)) {
			player.x += player.width;
			player.j++;
		}

		player_log << player;
	}
	if (KeyUp.down()) {
		player.direction = UP;

		if (playerstack('y', -1)) {
			player.y -= player.height;
			player.i--;
		}

		player_log << player;
	}
	if (KeyDown.down()) {
		player.direction = DOWN;

		if (playerstack('y', 1)) {
			player.y += player.height;
			player.i++;
		}

		player_log << player;
	}

	if (MouseR.down() && player_log.size() > 1) {
		player_log.pop_back();
		player = player_log.back();
	}

	//扉を開ける
	if (BoxNum != -1) {
		if (checkdoor()) {
			for (int i = 0; i < stage_data.height(); i++) {
				for (int j = 0; j < stage_data.width(); j++) {
					if (stage_data[i][j] == 6) {
						stage_data[i][j] = 0;
					}
				}
			}

			//何度もforが回らないようにする
			BoxNum = -1;
		}
	}

	if (stage_data[player.i][player.j] == 3) {
		return 1;
	}

	// パズルのリセット
	if (SimpleGUI::Button(U"やりなおし", Vec2(120, 10))) {
		player = player_log[0];
		player_log.clear();
		player_log << player;

		for (int i = 0; i < stage_data.height(); i++) {
			for (int j = 0; j < stage_data.width(); j++) {
				stage_data[i][j] = stage_data_init[i][j];
			}
		}
	}

	// ゴール
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
	TextureAsset(U"player").rotated(player.direction * 90_deg).draw(player.x, player.y);

	SimpleGUI::Button(U"やりなおし", Vec2(120, 10));
}



void baseinit() {
	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			if (stage_data[i][j] == (2 || 4)) {
				base_data[i][j] = 0;
			}
			else {
				base_data[i][j] = stage_data[i][j];
			}

			if (stage_data[i][j] == 5) {
				BoxNum++;
			}
		}
	}
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
	else if (data == 2 || data == 4) {
		if (objstack(t, n)) {
			objmove(t, n);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

void objmove(char t, int n) {
	if (objstack(t, n)) {
		int data = -1;

		if (t == 'x') {
			if (n > 0) {
				stage_data[player.i][player.j + 2] = stage_data[player.i][player.j + 1];
				stage_data[player.i][player.j + 1] = base_data[player.i][player.j + 1];
			}
			else {
				stage_data[player.i][player.j - 2] = stage_data[player.i][player.j - 1];
				stage_data[player.i][player.j - 1] = base_data[player.i][player.j - 1];
			}
		}
		else if (t == 'y') {
			if (n > 0) {
				stage_data[player.i + 2][player.j] = stage_data[player.i + 1][player.j];
				stage_data[player.i + 1][player.j] = base_data[player.i + 1][player.j];
			}
			else {
				stage_data[player.i - 2][player.j] = stage_data[player.i - 1][player.j];
				stage_data[player.i - 1][player.j] = base_data[player.i - 1][player.j];
			}
		}
	}
}

bool checkdoor(){
	int n = 0;

	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			if ((stage_data[i][j] == 4) && (base_data[i][j] == 5)) {
				n++;
			}
		}
	}

	if (BoxNum == n) {
		return true;
	}
	else{
		return false;
	}
}