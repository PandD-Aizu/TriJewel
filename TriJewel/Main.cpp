# include <Siv3D.hpp>
# include "puzzle.h"
# include "story.h"
# include "rule.h"

using App = SceneManager<String>;

#define DIFF_NUM 3  // 難易度数
#define STAGE_NUM 30    // ステージ数

#define CHAPTER_NUM 3   // 章の数
#define STORY_NUM 10    // 物語の数

// セーブデータ
typedef struct {
    int data[DIFF_NUM][STAGE_NUM];  // ステージのクリア状況
    int total[DIFF_NUM];    // クリアしたステージの合計(難易度別)
}SaveData;

SaveData save;  // セーブデータ

int clear_flag = 0;  // クリアフラグ
int diff_before = 0;    // 直前に選ばれていた難易度
int stage_before = 0;   // 直前に選ばれていたステージ

int story_flag = 0; // ストーリー再生フラグ
int chapter_before = 0; // 直前に選ばれていた章

String caption[CHAPTER_NUM][STORY_NUM];

// クリアしたステージの合計(難易度別)
void updateSave() {
    for (int i = 0; i < DIFF_NUM; i++) {
        save.total[i] = 0;
        for (int j = 0; j < STAGE_NUM; j++) {
            save.total[i] += save.data[i][j];
        }
    }
}

// 物語データ読み込み
void readCaption() {
    TextReader reader;

    for (int i = 0; i < CHAPTER_NUM; i++) {
        if (!reader.open(U"Data/Story/{}/caption.txt"_fmt(i + 1))) {
            throw Error(U"Failed to open caption.txt");
        }

        for (int j = 0; j < STORY_NUM; j++) {
            reader.readLine(caption[i][j]);
        }

        reader.close();
    }
}

// セーブデータ読み込み
void readSave() {
    TextReader reader;
    String line;

    if (!reader.open(U"Data/Save/save.txt")) {
        throw Error(U"Failed to open save.txt");
    }

    std::stringstream ss;

    // ステージクリア状況
    for (int i = 0; i < DIFF_NUM; i++) {
        reader.readLine(line);
        ss << line;
        for (int j = 0; j < STAGE_NUM; j++) {
            ss >> save.data[i][j];
        }
    }

    reader.close();

    // クリアしたステージの合計(難易度別)
    updateSave();
}

// セーブデータ上書き
void writeSave() {
    TextWriter writer;
    String line;

    if (!writer.open(U"Data/Save/save.txt")) {
        throw Error(U"Failed to open save.txt");
    }

    std::stringstream ss;

    // ステージクリア状況
    for (int i = 0; i < DIFF_NUM; i++) {
        for (int j = 0; j < STAGE_NUM; j++) {
            writer.write(U"{} "_fmt(save.data[i][j]));
        }
        writer.writeln(U"");
    }

    writer.close();
}

// タイトルシーン
class Title : public App::Scene
{
public:

    // コンストラクタ（必ず実装）
    Title(const InitData& init)
        : IScene(init)
    {
        AudioAsset(U"bgm_title").setLoop(true);
        AudioAsset(U"bgm_title").play();
    }

    // 更新関数
    void update() override
    {
        int button_width = 150;

        // 「はじめる」ボタン
        if (SimpleGUI::Button(U"はじめる", Vec2(400 - button_width / 2, 250), button_width))
        {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"Select");
            AudioAsset(U"bgm_title").stop();
        }

        // 「おはなし」ボタン
        if (SimpleGUI::Button(U"おはなし", Vec2(400 - button_width / 2, 300), button_width))
        {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"StorySelect");
            AudioAsset(U"bgm_title").stop();
        }

        // 「あそびかた」ボタン
        if (SimpleGUI::Button(U"あそびかた", Vec2(400 - button_width / 2, 350), button_width))
        {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"HowToPlay");
            AudioAsset(U"bgm_title").stop();
        }

        // 「おわる」ボタン
        if (SimpleGUI::Button(U"おわる", Vec2(400 - button_width / 2, 400), button_width))
        {
            AudioAsset(U"se_cancel").play();
            while (AudioAsset(U"se_cancel").isPlaying());
            System::Exit();
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        int button_width = 150;

        //Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
        TextureAsset(U"title").draw(0, 0);
        TextureAsset(U"logo").drawAt(400, 120);

        SimpleGUI::Button(U"はじめる", Vec2(400 - button_width / 2, 250), button_width);
        SimpleGUI::Button(U"おはなし", Vec2(400 - button_width / 2, 300), button_width);
        SimpleGUI::Button(U"あそびかた", Vec2(400 - button_width / 2, 350), button_width);
        SimpleGUI::Button(U"おわる", Vec2(400 - button_width / 2, 400), button_width);

        //FontAsset(U"TitleFont")(U"TriJewel(仮)").drawAt(400, 100);
    }
};

// ステージセレクトシーン
class Select : public App::Scene
{
private:
    int mode;   // シーン内モード管理(レベル選択 <---> ステージ選択)
    int difficult;  // 難易度
    int stage;      // ステージ番号

    s3d::String diff_str[DIFF_NUM];   // 難易度を表す文字列

    const int init_stage = 6;   // 最初から開放されているステージ

public:

    // コンストラクタ（必ず実装）
    Select(const InitData& init)
        : IScene(init)
    {
        mode = clear_flag == 1 ? 1 : 0;
        difficult = diff_before;

        diff_str[0] = U"かんたん";
        diff_str[1] = U"ふつう";
        diff_str[2] = U"むずかしい";

        clear_flag = 0;
    }

    // 更新関数
    void update() override
    {
        switch (mode) {
        // レベル選択
        case 0:
            // タイトルへ戻る
            if (SimpleGUI::Button(U"タイトル", Vec2(10, 10)))
            {
                AudioAsset(U"se_cancel").playOneShot();
                changeScene(U"Title");
            }

            // どれかのレベルが選択されたら、ステージ選択へ移動する
            for (int i = 0; i < DIFF_NUM; i++) {
                if (SimpleGUI::Button(diff_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150))
                {
                    AudioAsset(U"se_click").playOneShot();

                    mode = 1;
                    difficult = i + 1;
                    diff_before = difficult;
                }
            }

            break;

        // ステージ選択
        case 1:
            // レベル選択へ戻る
            if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
            {
                AudioAsset(U"se_cancel").playOneShot();
                mode = 0;
            }

            // パズル画面へ移動する
            for (int i = 0; i < STAGE_NUM; i++) {
                bool cond = (save.total[diff_before - 1] > i - init_stage);

                if (SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 100 * (i % init_stage), 200 + 50 * (i / init_stage)), unspecified, cond))
                {
                    AudioAsset(U"se_click").playOneShot();

                    stage = i + 1;
                    stage_before = stage;
                    puzzle_init(difficult, stage);
                    changeScene(U"Puzzle");
                }
            }
            break;

        default:
            break;
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        //Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
        TextureAsset(U"select").draw(0, 0);

        switch (mode) {
            // レベル選択
        case 0:
            // タイトルへ戻るボタン
            SimpleGUI::Button(U"タイトル", Vec2(10, 10));

            // 難易度ボタン
            for (int i = 0; i < DIFF_NUM; i++) {
                SimpleGUI::Button(diff_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150);
            }
            break;

        // ステージ選択
        case 1:
            // 戻るボタン
            SimpleGUI::Button(U"もどる", Vec2(10, 10));
            // ステージ番号
            for (int i = 0; i < STAGE_NUM; i++) {
                bool cond = (save.total[diff_before - 1] > i - init_stage);
                SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 100 * (i % init_stage), 200 + 50 * (i / init_stage)), unspecified, cond);
                if (save.data[diff_before - 1][i] == 1) {
                    Rect(100 + 100 * (i % init_stage), 200 + 50 * (i / init_stage), 65, 35).draw(ColorF(1,1,0,0.5));
                }
            }
            break;

        default:
            break;
        }

        FontAsset(U"TitleFont")(U"ステージセレクト").draw(184, 104, Palette::Gray);
        FontAsset(U"TitleFont")(U"ステージセレクト").draw(180, 100, Palette::Lightgreen);
    }
};

// パズルシーン
class Puzzle : public App::Scene
{
private:
    int puzzle_state;   // パズルのクリア状況
    s3d::Audio bgm; // BGM
public:

    // コンストラクタ（必ず実装）
    Puzzle(const InitData& init)
        : IScene(init)
    {
        puzzle_state = 0;
        bgm = AudioAsset(U"bgm_stage{}"_fmt(diff_before));

        bgm.setLoop(true);
        bgm.play();
    }

    // 更新関数
    void update() override
    {
        // クリアしていない間、パズルを遊べる
        if (puzzle_state == 0) {
            puzzle_state = puzzle_update();

            // ステージセレクトへ戻る
            if (SimpleGUI::Button(U"もどる", Vec2(10, 10))) {
                if (bgm.isPlaying()) {
                    bgm.stop();
                }

                AudioAsset(U"se_cancel").playOneShot();

                clear_flag = 1;

                changeScene(U"Select");
            }
        }

        // クリアしたら、ステージセレクトへ戻る
        else {
            if (bgm.isPlaying()) {
                bgm.stop();
            }

            if (puzzle_state == 1) {
                AudioAsset(U"bgm_clear").play();
                puzzle_state = 2;
            }

            if (MouseL.down()) {
                AudioAsset(U"bgm_clear").stop();
                AudioAsset(U"se_click").playOneShot();

                save.data[diff_before - 1][stage_before - 1] = 1;
                updateSave();

                clear_flag = 1;
                changeScene(U"Select");
            }
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        String chapter[CHAPTER_NUM] = {
            U"シロナのねがい",
            U"リンドルのねがい",
            U"チャマのねがい"
        };

        Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
        
        puzzle_draw();

        SimpleGUI::Button(U"もどる", Vec2(10, 10));

        if (puzzle_state != 0) {
            FontAsset(U"TitleFont")(U"クリア！").drawAt(Scene::Center().x + 4, Scene::Center().y + 4, Palette::Gray);
            FontAsset(U"TitleFont")(U"クリア！").drawAt(Scene::Center());

            if (save.data[diff_before - 1][stage_before - 1] == 0 && (save.total[diff_before - 1] + 1) % 3 == 0) {
                FontAsset(U"StoryFont")(U"おはなしがふえたよ！").drawAt(Scene::Center().x + 4, Scene::Center().y + 52, Palette::Gray);
                FontAsset(U"StoryFont")(U"おはなしがふえたよ！").drawAt(Scene::Center().x, Scene::Center().y + 50);

                String story = U"　"+chapter[diff_before - 1] + U"「" + caption[diff_before - 1][(save.total[diff_before - 1] + 1) / 3 - 1] + U"」　";

                FontAsset(U"StoryFont")(story).drawAt(Scene::Center().x, Scene::Center().y + 90).draw(Palette::White).drawFrame(1, Palette::Black);

                FontAsset(U"StoryFont")(story).drawAt(Scene::Center().x, Scene::Center().y + 90, Palette::Green);
            }
        }

        //FontAsset(U"TitleFont")(U"パズル").drawAt(400, 100);
    }
};

// ストーリーセレクトシーン
class StorySelect : public App::Scene
{
private:
    int mode;   // シーン内モード管理(章選択 <---> 話数選択)
    int chapter;    // 章番号
    int story;  // 話数

    s3d::String chap_str[CHAPTER_NUM];   // 章を表す文字列

public:

    // コンストラクタ（必ず実装）
    StorySelect(const InitData& init)
        : IScene(init)
    {
        mode = (story_flag == 1 && chapter_before != 0) ? 1 : 0;
        chapter = chapter_before;
        story = 0;

        chap_str[0] = U"シロナのねがい";
        chap_str[1] = U"リンドルのねがい";
        chap_str[2] = U"チャマのねがい";

        story_flag = 0;
    }

    // 更新関数
    void update() override
    {
        switch (mode) {
        case 0:
            // タイトルへ戻る
            if (SimpleGUI::Button(U"タイトル", Vec2(10, 10)))
            {
                AudioAsset(U"se_cancel").playOneShot();

                changeScene(U"Title");
            }

            // プロローグ
            if (SimpleGUI::Button(U"はじまり", Vec2(100, Scene::Height() / 4 + 50), 150))
            {
                AudioAsset(U"se_click").playOneShot();

                chapter = 0;
                chapter_before = chapter;
                story = 0;
                story_init(chapter, story);
                changeScene(U"Story");
            }

            // どれかの物語が選択されたら、話数選択画面へ移動する
            for (int i = 0; i < CHAPTER_NUM; i++) {
                if (SimpleGUI::Button(chap_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 180))
                {
                    AudioAsset(U"se_click").playOneShot();

                    mode = 1;
                    chapter = i + 1;
                    chapter_before = chapter;
                }
            }

            // スタッフクレジット
            if (SimpleGUI::Button(U"スタッフクレジット", Vec2(500, Scene::Height() / 4 * 3))) {
                AudioAsset(U"se_click").playOneShot();

                chapter = 0;
                chapter_before = chapter;
                story = 0;
                changeScene(U"Staff");
            }

            break;

        case 1:
            // 章選択画面へ戻る
            if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
            {
                AudioAsset(U"se_cancel").playOneShot();

                mode = 0;
            }

            // ストーリー再生画面へ移動する
            for (int i = 0; i < STORY_NUM; i++) {
                bool cond = save.total[chapter_before - 1] / (STAGE_NUM / STORY_NUM) >= (i + 1);

                if (SimpleGUI::Button(caption[chapter - 1][i], Vec2(250, 150 + 40 * i), 300, cond))
                {
                    AudioAsset(U"se_click").playOneShot();

                    story = i + 1;
                    story_init(chapter,story);
                    changeScene(U"Story");
                }
            }
            break;

        default:
            break;
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        //Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
        TextureAsset(U"story").draw(0, 0);
        Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(0.8, 0.8, 0.8, 0.3));

        switch (mode) {
            // 章選択
        case 0:
            // タイトルへ戻るボタン
            SimpleGUI::Button(U"タイトル", Vec2(10, 10));

            SimpleGUI::Button(U"はじまり", Vec2(100, Scene::Height() / 4 + 50), 150);

            // 各章ボタン
            for (int i = 0; i < CHAPTER_NUM; i++) {
                SimpleGUI::Button(chap_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 180);
            }

            SimpleGUI::Button(U"スタッフクレジット", Vec2(500, Scene::Height() / 4 * 3));

            break;

            // 話数選択
        case 1:
            // 戻るボタン
            SimpleGUI::Button(U"もどる", Vec2(10, 10));
            // 話数
            for (int i = 0; i < STORY_NUM; i++) {
                bool cond = save.total[chapter_before - 1] / (STAGE_NUM / STORY_NUM) >= (i + 1);
                SimpleGUI::Button(caption[chapter - 1][i], Vec2(250, 150 + 40 * i), 300, cond);
            }
            break;

        default:
            break;
        }

        FontAsset(U"TitleFont")(U"ストーリーセレクト").drawAt(404, 104, Palette::Gray);
        FontAsset(U"TitleFont")(U"ストーリーセレクト").drawAt(400, 100, Palette::White);
    }
};

// ストーリー再生シーン
class Story : public App::Scene
{
public:

    // コンストラクタ（必ず実装）
    Story(const InitData& init)
        : IScene(init)
    {

    }

    // 更新関数
    void update() override
    {
        if (story_update() == 1) {
            AudioAsset(U"bgm_story1").stop();
            AudioAsset(U"bgm_story2").stop();
            story_flag = 1;
            changeScene(U"StorySelect");
        }

        // ストーリーセレクトへ戻る
        if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
        {
            AudioAsset(U"bgm_story1").stop();
            AudioAsset(U"bgm_story2").stop();
            AudioAsset(U"se_cancel").playOneShot();

            story_flag = 1;
            changeScene(U"StorySelect");
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        //Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
        TextureAsset(U"story").draw(0, 0);
        Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(0.8, 0.8, 0.8, 0.3));

        story_draw();

        SimpleGUI::Button(U"もどる", Vec2(10, 10));

        //FontAsset(U"TitleFont")(U"ストーリー再生中...").drawAt(400, 100);
    }
};

// チュートリアルシーン
class HowToPlay : public App::Scene
{
public:

    // コンストラクタ（必ず実装）
    HowToPlay(const InitData& init)
        : IScene(init)
    {

    }

    // 更新関数
    void update() override
    {
        // タイトルへ戻る
        if (SimpleGUI::Button(U"タイトル", Vec2(10, 10)))
        {
            AudioAsset(U"se_cancel").playOneShot();

            changeScene(U"Title");
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        //Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
        TextureAsset(U"title").draw(0, 0);

        drawRule();

        SimpleGUI::Button(U"タイトル", Vec2(10, 10));

        FontAsset(U"TitleFont")(U"あそびかた").drawAt(404, 104, Palette::Gray);
        FontAsset(U"TitleFont")(U"あそびかた").drawAt(400, 100);
    }
};

// スタッフクレジットシーン
class Staff : public App::Scene
{
private:
    Array<String> credit;   // スタッフクレジット(一行ずつ格納する)
    int scroll;   // スクロール位置(y座標)

public:

    // コンストラクタ（必ず実装）
    Staff(const InitData& init)
        : IScene(init)
    {
        scroll = Scene::Height() / 2 + 200;

        TextReader reader;
        String line;

        if (!reader.open(U"Data/staff.txt")) {
            throw Error(U"Failed to open staff.txt");
        }

        // スタッフクレジット情報の読み込み
        while (reader.readLine(line)) {
            // 空行は大きなスペース
            if (line.isEmpty()) {
                for (int i = 0; i < 3; i++) {
                    credit << U"";
                }
            }

            // 一行ずつ読み込む
            else {
                credit << line;
            }
        }

        reader.close();

        AudioAsset(U"bgm_ed").play();
    }

    // 更新関数
    void update() override
    {
        scroll -= 1;

        // ストーリー選択画面へ戻る
        if (MouseR.down() || !AudioAsset(U"bgm_ed").isPlaying())
        {
            AudioAsset(U"bgm_ed").stop();
            changeScene(U"StorySelect");
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        String fontName;
        Color color;

        TextureAsset(U"logo").drawAt(Scene::Width() / 2, scroll - 200);

        for (int i = 0; i < credit.size(); i++) {
            if (credit[i][0] == '(')
                fontName = U"StoryFont";
            else
                fontName = U"TitleFont";

            if (credit[i][0] == '<')
                color = Palette::Lightgreen;
            else
                color = Palette::White;

            FontAsset(fontName)(credit[i]).drawAt(Scene::Width() / 2, scroll + 60 * i, color);
        }
    }
};

void Main()
{
    Window::SetTitle(U"シロナと願いの石～みんなともだち～");

	// フォント
    FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
    FontAsset::Register(U"StoryFont", 30);
    FontAsset::Register(U"RuleFont", 25);

    // 画像
    TextureAsset::Register(U"title", U"Data/Image/title.png");
    TextureAsset::Register(U"logo", U"Data/Image/logo.png");

    TextureAsset::Register(U"select", U"Data/Image/select.png");
    
    TextureAsset::Register(U"story", U"Data/Image/story.png");
    
    TextureAsset::Register(U"player", U"Data/Image/game/player.png");
    TextureAsset::Register(U"road", U"Data/Image/game/grass.png");
    TextureAsset::Register(U"wall", U"Data/Image/game/tree.png");
    TextureAsset::Register(U"rock", U"Data/Image/game/rock.png");
    TextureAsset::Register(U"goal", U"Data/Image/game/goal.png");
    TextureAsset::Register(U"box", U"Data/Image/game/box.png");
    TextureAsset::Register(U"place", U"Data/Image/game/place.png");
    TextureAsset::Register(U"door", U"Data/Image/game/door.png");
    TextureAsset::Register(U"button", U"Data/Image/game/button.png");
    TextureAsset::Register(U"match", U"Data/Image/game/match.png");

    TextureAsset::Register(U"シロナ", U"Data/Image/story/sirona.png");
    TextureAsset::Register(U"リンドル", U"Data/Image/story/rindol.png");
    TextureAsset::Register(U"チャマ", U"Data/Image/story/chama.png");
    TextureAsset::Register(U"ファイ", U"Data/Image/story/phi.png");
    TextureAsset::Register(U"エメ", U"Data/Image/story/eme.png");
    TextureAsset::Register(U"メルビィ", U"Data/Image/story/meruby.png");
    TextureAsset::Register(U"next", U"Data/Image/story/next.png");

    // 効果音
    AudioAsset::Register(U"se_click", U"Data/Sound/se/click.ogg");
    AudioAsset::Register(U"se_cancel", U"Data/Sound/se/cancel.ogg");
    AudioAsset::Register(U"se_step", U"Data/Sound/se/step.ogg");
    AudioAsset::Register(U"se_select", U"Data/Sound/se/select.ogg");
    AudioAsset::Register(U"se_unlock", U"Data/Sound/se/unlock.ogg");

    // BGM
    AudioAsset::Register(U"bgm_title", U"Data/Sound/bgm/title.ogg");
    AudioAsset::Register(U"bgm_stage1", U"Data/Sound/bgm/stage1.ogg");
    AudioAsset::Register(U"bgm_stage2", U"Data/Sound/bgm/stage2.ogg");
    AudioAsset::Register(U"bgm_stage3", U"Data/Sound/bgm/stage3.ogg");
    AudioAsset::Register(U"bgm_clear", U"Data/Sound/bgm/clear.ogg");
    AudioAsset::Register(U"bgm_story1", U"Data/Sound/bgm/story.ogg");
    AudioAsset::Register(U"bgm_story2", U"Data/Sound/bgm/story2.ogg");
    AudioAsset::Register(U"bgm_ed", U"Data/Sound/bgm/ed_theme.ogg");

	// シーンマネージャーを作成
	App manager;

	// シーン登録
	manager.add<Title>(U"Title");
    manager.add<Select>(U"Select");
    manager.add<Puzzle>(U"Puzzle");
    manager.add<StorySelect>(U"StorySelect");
    manager.add<Story>(U"Story");
    manager.add<HowToPlay>(U"HowToPlay");
    manager.add<Staff>(U"Staff");

    readSave();
    readCaption();
	while (System::Update())
	{
        // 現在のシーンを実行
        if (!manager.update())
        {
            break;
        }
	}

    writeSave();
}