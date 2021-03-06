#include"story.h"

static Actor actors[6];	// キャラクター達
static Array<Dialogue> dialogue;	// セリフ
static int scene;	// セリフ番号

static int playing;	// セリフ再生中かどうかフラグ
static int start;	// 開始時間(セリフ再生のために必要)
static int length;	// 表示させるセリフの長さ

// ストーリーの初期化
void story_init(int chapter, int story) {
	// ファイル読み込み用変数
	TextReader reader(U"Data/Story/{}/{}.txt"_fmt(chapter, story));
	String line;

	// 読み込みデータ
	int left, right;
	String text;
	int speaker;

	// ファイルが読み込めなかった場合、エラーメッセージを表示させる
	if (!reader){
		throw Error(U"Failed to open `test.txt`");
	}

	dialogue.clear();

	// ファイル読み込み
	while (1) {
		Dialogue d;

		reader.readLine(line);
		d.left = Parse<int>(line);

		reader.readLine(line);
		d.right = Parse<int>(line);

		reader.readLine(d.text);

		reader.readLine(line);
		d.speaker = Parse<int>(line);

		reader.readLine(line);
		d.bgm = Parse<int>(line);

		dialogue.push_back(d);

		if (!reader.readLine(line)) break;
	}

	reader.close();

	scene = 0;
	start = Scene::Time() * 1000;
	length = (int)((Scene::Time() * 1000 - start) / 50);
	playing = 0;
}

// ストーリーの更新関数
// 戻り値: ストーリー再生中の場合は 0
// 　　　  再生を終えた場合は 1 を返す
int story_update() {
	s3d::Audio bgm[2] = {
		AudioAsset(U"bgm_story1"),
		AudioAsset(U"bgm_story2")
	};

	// BGM再生
	if (scene == 0) {
		if (!bgm[dialogue[scene].bgm].isPlaying()) {
			bgm[dialogue[scene].bgm].setLoop(true);
			bgm[dialogue[scene].bgm].play();
		}
	}

	// BGM変更
	else if (dialogue[scene].bgm != dialogue[scene - 1].bgm) {
		if (!bgm[dialogue[scene].bgm].isPlaying()) {
			bgm[dialogue[scene - 1].bgm].stop();
			bgm[dialogue[scene].bgm].setLoop(true);
			bgm[dialogue[scene].bgm].play();
		}
	}

	// クリックで会話を進める
	if (MouseL.down()) {
		AudioAsset(U"se_select").playOneShot();

		// 次の会話へ移る
		if (playing == 1) {

			// 最後のセリフに到達した場合は、終了する
			if (scene == dialogue.size() - 1) {
				bgm[dialogue[scene].bgm].stop();
				return 1;
			}

			scene++;
			start = Scene::Time() * 1000;
			playing = 0;
			length = (int)((Scene::Time() * 1000 - start) / 50);
		}

		// 会話が表示途中の場合、全部表示させる
		else {
			length = dialogue[scene].text.length();
		}
	}

	// 会話が表示途中かどうか判定
	if (length >= dialogue[scene].text.length()) {
		playing = 1;
	}

	// 会話の表示制御
	if (playing == 0) {
		length = (int)((Scene::Time() * 1000 - start) / 50);
	}
	return 0;
}

// ストーリーの描画関数
void story_draw() {
	const int namebox_size = 65;
	const int chara_size = 128 * 1.5;
	const String name[6] = {
		U"シロナ",
		U"リンドル",
		U"チャマ",
		U"ファイ",
		U"エメ",
		U"メルビィ"
	};

	if (dialogue[scene].left >= 0) {
		if (dialogue[scene].speaker != 1) {
			const ScopedColorMul2D state(ColorF(0.6, 0.6, 0.6));
			TextureAsset(name[dialogue[scene].left]).scaled(1.5).drawAt(Scene::Width() / 16 + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
		else {
			TextureAsset(name[dialogue[scene].left]).scaled(1.5).drawAt(Scene::Width() / 16 + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
	}

	if (dialogue[scene].right >= 0) {
		if (dialogue[scene].speaker != 2) {
			const ScopedColorMul2D state(ColorF(0.6, 0.6, 0.6));
			TextureAsset(name[dialogue[scene].right]).scaled(1.5).drawAt(Scene::Width() / 16 * 15 - chara_size + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
		else {
			TextureAsset(name[dialogue[scene].right]).scaled(1.5).drawAt(Scene::Width() / 16 * 15 - chara_size + chara_size / 2, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10 + chara_size / 2);
		}
	}

	if (dialogue[scene].speaker != 0) {
		Rect namebox = Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12 - namebox_size, 150, namebox_size).draw(Palette::White).drawFrame(1, 0, Palette::Black);
		FontAsset(U"StoryFont")(name[dialogue[scene].speaker == 1 ? dialogue[scene].left : dialogue[scene].right]).draw(namebox.stretched(-10), Palette::Black);
	}

	Rect textbox = Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12, (Scene::Width() / 16) * 14, (Scene::Height() / 16) * 3).draw(Palette::White).drawFrame(1, 0, Palette::Black);
	FontAsset(U"StoryFont")(dialogue[scene].text.substr(0, length)).draw(textbox.stretched(-10), Palette::Black);

	if (playing == 1)
		TextureAsset(U"next").draw((Scene::Width() / 16) * 14, (Scene::Height() / 16) * 14);
}