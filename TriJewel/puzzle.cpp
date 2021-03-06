#include"puzzle.h"

static Grid<int> stage_data;	// ステージ情報
static Array<Grid<int>> stage_data_log;	// ステージ情報のログ
static Grid<int> stage_data_init;	// ステージ情報(初期状態)
static Grid<int> base_data;		//岩や箱を除いたステージ情報

static Player player;	// プレイヤー
static Array<Player> player_log;	// プレイヤーの移動ログ

static int door_flag;	// 扉解錠フラグ

// 操作ボタン
Rect up(600, 300, 100, 100);
Rect right(700, 400, 100, 100);
Rect down(600, 500, 100, 100);
Rect left(500, 400, 100, 100);

int BoxNum = 0;		//配置場所（箱）の数をカウントする変数

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
	readfile(U"./Data/Stage/{}/{:0>2}.txt"_fmt(diff, stage));
	stage_data_init = Grid<int>(stage_data.width(), stage_data.height());
	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			stage_data_init[i][j] = stage_data[i][j];
		}
	}

	base_data = Grid<int>(stage_data.width(), stage_data.height(), -1);
	baseinit();

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
	if (player.x > 100 + player.width * stage_data.width()) player.x = 100 + player.width * stage_data.width();
	if (player.y < 100) player.y = 100;
	if (player.y > 100 + player.height * stage_data.height()) player.y = 100 + player.height * stage_data.height();

	if (player.i < 0) player.i = 0;
	if (player.i > stage_data.height()) player.i = stage_data.height() - 1;
	if (player.j < 0) player.j = 0;
	if (player.j > stage_data.width()) player.j = stage_data.width() - 1;

	// ログの初期化
	player_log.clear();
	player_log << player;

	stage_data_log.clear();
	stage_data_log << stage_data;

	door_flag = 0;
}

// パズルの更新関数
// 戻り値: パズルを続行中の場合は 0
// 　　　  クリアした場合は 1 を返す
int puzzle_update() {
	/*** ここを編集してください ***/

	//プレイヤー移動
	if (left.intersects(Cursor::Pos()) && MouseL.down()) {
		AudioAsset(U"se_step").playOneShot();

		player.direction = LEFT;

		if (playerstack('x',-1)) {
			player.x -= player.width;
			player.j--;
		}

		player_log << player;
		stage_data_log << stage_data;
	}
	if (right.intersects(Cursor::Pos()) && MouseL.down()) {
		AudioAsset(U"se_step").playOneShot();

		player.direction = RIGHT;

		if (playerstack('x', 1)) {
			player.x += player.width;
			player.j++;
		}

		player_log << player;
		stage_data_log << stage_data;
	}
	if (up.intersects(Cursor::Pos()) && MouseL.down()) {
		AudioAsset(U"se_step").playOneShot();
		
		player.direction = UP;

		if (playerstack('y', -1)) {
			player.y -= player.height;
			player.i--;
		}

		player_log << player;
		stage_data_log << stage_data;
	}
	if (down.intersects(Cursor::Pos()) && MouseL.down()) {
		AudioAsset(U"se_step").playOneShot();
		
		player.direction = DOWN;

		if (playerstack('y', 1)) {
			player.y += player.height;
			player.i++;
		}

		player_log << player;
		stage_data_log << stage_data;
	}

	// 一歩戻る
	if (MouseR.down() && player_log.size() > 1) {
		AudioAsset(U"se_step").playOneShot();
		
		player_log.pop_back();
		player = player_log.back();

		stage_data_log.pop_back();
		stage_data = stage_data_log.back();
	}

	//扉を開ける
	if (checkdoor()) {
		if (door_flag == 0) {
			door_flag = 1;
			AudioAsset(U"se_unlock").playOneShot();
		}

		for (int i = 0; i < stage_data.height(); i++) {
			for (int j = 0; j < stage_data.width(); j++) {
				if (stage_data[i][j] == DOOR) {
					stage_data[i][j] = ROAD;
				}
			}
		}
	}

	// 条件を満たしていない時、扉を閉める
	else {
		if (door_flag == 1) {
			door_flag = 0;
		}

		for (int i = 0; i < stage_data.height(); i++) {
			for (int j = 0; j < stage_data.width(); j++) {
				if (stage_data[i][j] == ROAD && base_data[i][j] == DOOR) {
					stage_data[i][j] = DOOR;
				}
			}
		}
	}

	// クリア
	if (stage_data[player.i][player.j] == GOAL) {
		return 1;
	}

	// パズルのリセット
	if (SimpleGUI::Button(U"やりなおし", Vec2(120, 10))) {
		AudioAsset(U"se_cancel").playOneShot();

		player = player_log[0];
		player_log.clear();
		player_log << player;

		stage_data = stage_data_log[0];
		stage_data_log.clear();
		stage_data_log << stage_data;

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

	{
		// 画像を少しだけ暗くする
		const ScopedColorMul2D state(ColorF(1, 0.8, 1, 1));

		// 背景
		for (int i = 0; i * 30 - 10 < Scene::Height(); i++) {
			for (int j = 0; j * 30 - 10 < Scene::Width(); j++) {
				TextureAsset(U"road").draw(j * 30 - 10, i * 30 - 10);
			}
		}

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
					if (stage_data_init[i][j] == PLACE) {
						TextureAsset(U"match").draw(100 + j * 30, 100 + i * 30);
					}
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
	}
	//主人公
	//Rect(player.x, player.y, 30, 30).draw(Palette::Blue);
	TextureAsset(U"player").rotated(player.direction * 90_deg).draw(player.x, player.y);

	// 操作ボタン
	TextureAsset(U"button").rotated(0).draw(up.x,up.y);
	TextureAsset(U"button").rotated(90_deg).draw(right.x, right.y);
	TextureAsset(U"button").rotated(90_deg * 2).draw(down.x, down.y);
	TextureAsset(U"button").rotated(90_deg * 3).draw(left.x, left.y);

	if (up.intersects(Cursor::Pos())) {
		up.draw(ColorF(1.0, 1.0, 0, 0.5));
	}
	if (right.intersects(Cursor::Pos())) {
		right.draw(ColorF(1.0, 1.0, 0, 0.5));
	}
	if (down.intersects(Cursor::Pos())) {
		down.draw(ColorF(1.0, 1.0, 0, 0.5));
	}
	if (left.intersects(Cursor::Pos())) {
		left.draw(ColorF(1.0, 1.0, 0, 0.5));
	}

	SimpleGUI::Button(U"やりなおし", Vec2(120, 10));

	FontAsset(U"StoryFont")(U"みぎクリック: いっかい もどる").draw(50, 500);
	FontAsset(U"StoryFont")(U"ひだりクリックで\nそうさしてね！").draw(up.x - 100, up.y - 100);
}


// base_dataの初期化関数
void baseinit() {
	BoxNum = 0;
	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			// 岩と箱の下には道がある
			if (stage_data[i][j] == ROCK || stage_data[i][j] == BOX) {
				base_data[i][j] = ROAD;
			}
			else {
				base_data[i][j] = stage_data[i][j];
			}

			// 箱(配置場所)の数をカウント
			if (stage_data[i][j] == PLACE) {
				BoxNum++;
			}
		}
	}
}

// 岩、箱が動くかの判定
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

// プレイヤーが動けるかの判定
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

// 岩、箱の移動処理
void objmove(char t, int n) {
	if (objstack(t, n)) {
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

// 扉が開くかの判定
bool checkdoor(){
	int n = 0;

	if (BoxNum == 0) {
		return false;
	}

	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			if ((stage_data[i][j] == BOX) && (base_data[i][j] == PLACE)) {
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