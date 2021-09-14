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
	if (KeyUp.down()) player.j -= 30;
	if (KeyDown.down()) player.j += 30;
	if (KeyRight.down()) player.i += 30;
	if (KeyLeft.down()) player.i -= 30;
	/*** ここを編集してください ***/

	return 0;
}

// パズルの描画関数
void puzzle_draw() {
	int wallx = 6, wally = 6, goalx=350,goaly=350,Startx = 200, Starty = 200 ,Blockx = 290,Blocky=290;
	int limitx=0, limity=0;
	int d[5][5];

	for (int i = 0; i < wallx; i++) {
		for (int j = 0; j < wally ; j++) {
			Rect((Startx + 30) + i * 30, (Starty + 30) + j * 30, 30, 30).draw(Palette::Green);
		}
	}

	//壁
	for (int j = 0; j < wallx; j++) {
		Rect(Startx + j * 30, Starty, 30, 30).draw(Palette::Gray);
	}

	for (int i = 0; i < wally; i++) {
		Rect(Startx , Starty + i*30, 30, 30).draw(Palette::Gray);
	}

	for (int k = 0; k <= wally; k++) {
		Rect(Startx + 30 * wallx, Starty + k * 30, 30, 30).draw(Palette::Gray);
	}

	for (int l = 0; l <= wallx; l++) {
		Rect(Startx + l*30, Starty + wally * 30, 30, 30).draw(Palette::Gray);
	}

	//地面
	for (int i = 0; i < wallx-1; i++) {
		for (int j = 0; j < wally-1; j++) {
			Rect((Startx+30)+i*30 , (Starty + 30) + j * 30, 30, 30).draw(Palette::Green);
		}
	}

	//壁追加
	for (int i = 1; i <= 2; i++) {
		Rect(Startx + i *30, Starty + 30 * 1, 30, 30).draw(Palette::Gray);
	}

	for (int i = 1; i <= 2; i++) {
		Rect(Startx + i * 30, Starty + 30 * 2, 30, 30).draw(Palette::Gray);
	}

	for (int i = 4; i <= 5; i++) {
		Rect(Startx + i * 30, Starty + 30 * 4, 30, 30).draw(Palette::Gray);
	}

	for (int i = 4; i <= 5; i++) {
		Rect(Startx + i * 30, Starty + 30 * 5, 30, 30).draw(Palette::Gray);
	}

	Rect(Blockx, Blocky, 30, 30).draw(Palette::Black);


	//ゴール
	Rect(goalx,goaly, 30, 30).draw(Palette::Yellow);
	//主人公
	Rect(player.i, player.j, 30, 30).draw(Palette::Blue);
	/*** ここを編集してください ***/
}

bool objmove() {
	return true;
}

bool playermove() {
	return true;
}