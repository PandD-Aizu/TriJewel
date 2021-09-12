#include"story.h"

static Actor actors[6];	// キャラクター達
static Array<Dialogue> dialogue;	// セリフ
static int scene;	// セリフ番号

static int start;

// ストーリーの初期化
void story_init(int chapter, int story) {
	dialogue = {
		Dialogue(0,1,U"今日はいい天気ですね。\n気分がいいです。",1),
		Dialogue(0,1,U"はい。私もそう思います。", 2),
		Dialogue(-1,-1,U"しばらくして...",0),
		Dialogue(1,2,U"月が綺麗ですね。",1),
		Dialogue(1,2,U"その通りです。",2)
	};

	scene = 0;
	start = Scene::Time() * 1000;
}

// ストーリーの更新関数
// 戻り値: ストーリー再生中の場合は 0
// 　　　  再生を終えた場合は 1 を返す
int story_update() {
	if (MouseL.down()) {
		if (scene == dialogue.size() - 1)
			return 1;
		
		scene++;
		start = Scene::Time() * 1000;
	}

	return 0;
}

// ストーリーの描画関数
void story_draw() {
	const int length = (int)((Scene::Time() * 1000 - start) / 50);

	Rect textbox = Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12, (Scene::Width() / 16) * 14, (Scene::Height() / 16) * 3).draw(Palette::White);
	FontAsset(U"StoryFont")(dialogue[scene].text.substr(0, length)).draw(textbox.stretched(-10), Palette::Black);
}