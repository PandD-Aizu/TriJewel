# include <Siv3D.hpp>
# include "puzzle.h"
# include "story.h"
# include "rule.h"

using App = SceneManager<String>;

int clear_flag = 0;  // クリアフラグ
int diff_before = 0;    // 直前に選ばれていた難易度

int story_flag = 0; // ストーリー再生フラグ
int chapter_before = 0; // 直前に選ばれていた章

// タイトルシーン
class Title : public App::Scene
{
public:

    // コンストラクタ（必ず実装）
    Title(const InitData& init)
        : IScene(init)
    {

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
        }

        // 「おはなし」ボタン
        if (SimpleGUI::Button(U"おはなし", Vec2(400 - button_width / 2, 300), button_width))
        {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"StorySelect");
        }

        // 「あそびかた」ボタン
        if (SimpleGUI::Button(U"あそびかた", Vec2(400 - button_width / 2, 350), button_width))
        {
            AudioAsset(U"se_click").playOneShot();
            changeScene(U"HowToPlay");
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

    s3d::String diff_str[3];   // 難易度を表す文字列

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
            for (int i = 0; i < 3; i++) {
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
            for (int i = 0; i < 30; i++) {
                if (SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 100 * (i % 6), 200 + 50 * (i / 6))))
                {
                    AudioAsset(U"se_click").playOneShot();

                    stage = i + 1;
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
            for (int i = 0; i < 3; i++) {
                SimpleGUI::Button(diff_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150);
            }
            break;

        // ステージ選択
        case 1:
            // 戻るボタン
            SimpleGUI::Button(U"もどる", Vec2(10, 10));
            // ステージ番号
            for (int i = 0; i < 30; i++) {
                SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 100 * (i % 6), 200 + 50 * (i / 6)));
            }
            break;

        default:
            break;
        }

        FontAsset(U"TitleFont")(U"ステージセレクト").drawAt(400, 100);
    }
};

// パズルシーン
class Puzzle : public App::Scene
{
private:
    int puzzle_state;   // パズルのクリア状況
public:

    // コンストラクタ（必ず実装）
    Puzzle(const InitData& init)
        : IScene(init)
    {
        puzzle_state = 0;
    }

    // 更新関数
    void update() override
    {
        // クリアしていない間、パズルを遊べる
        if (puzzle_state == 0) {
            puzzle_state = puzzle_update();

            // ステージセレクトへ戻る
            if (SimpleGUI::Button(U"もどる", Vec2(10, 10))) {
                AudioAsset(U"se_cancel").playOneShot();

                clear_flag = 1;
                changeScene(U"Select");
            }
        }

        // クリアしたら、ステージセレクトへ戻る
        else {
            if (MouseL.down()) {
                AudioAsset(U"se_click").playOneShot();

                clear_flag = 1;
                changeScene(U"Select");
            }
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        Scene::SetBackground(ColorF(0.3, 0.4, 0.5));
        
        puzzle_draw();

        SimpleGUI::Button(U"もどる", Vec2(10, 10));

        if (puzzle_state == 1) {
            FontAsset(U"TitleFont")(U"クリア！").drawAt(Scene::Center());
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

    s3d::String chap_str[3];   // 章を表す文字列

public:

    // コンストラクタ（必ず実装）
    StorySelect(const InitData& init)
        : IScene(init)
    {
        mode = story_flag == 1 ? 1 : 0;
        chapter = chapter_before;
        story = 0;

        chap_str[0] = U"物語1";
        chap_str[1] = U"物語2";
        chap_str[2] = U"物語3";

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

            // どれかの物語が選択されたら、話数選択画面へ移動する
            for (int i = 0; i < 3; i++) {
                if (SimpleGUI::Button(chap_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150))
                {
                    AudioAsset(U"se_click").playOneShot();

                    mode = 1;
                    chapter = i + 1;
                    chapter_before = chapter;
                }
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
            for (int i = 0; i < 10; i++) {
                if (SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 75 * (i % 5), 200 + 100 * (i / 5))))
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

        switch (mode) {
            // 章選択
        case 0:
            // タイトルへ戻るボタン
            SimpleGUI::Button(U"タイトル", Vec2(10, 10));

            // 各章ボタン
            for (int i = 0; i < 3; i++) {
                SimpleGUI::Button(chap_str[i], Vec2(100 + 200 * i, Scene::Height() / 2 - 25), 150);
            }
            break;

            // 話数選択
        case 1:
            // 戻るボタン
            SimpleGUI::Button(U"もどる", Vec2(10, 10));
            // 話数
            for (int i = 0; i < 10; i++) {
                SimpleGUI::Button(U"{:0>2}"_fmt(i + 1), Vec2(100 + 75 * (i % 5), 200 + 100 * (i / 5)));
            }
            break;

        default:
            break;
        }

        FontAsset(U"TitleFont")(U"ストーリーセレクト").drawAt(400, 100);
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
            story_flag = 1;
            changeScene(U"StorySelect");
        }

        // ストーリーセレクトへ戻る
        if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
        {
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

        story_draw();

        SimpleGUI::Button(U"もどる", Vec2(10, 10));

        FontAsset(U"TitleFont")(U"ストーリー再生中...").drawAt(400, 100);
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

        FontAsset(U"TitleFont")(U"あそびかた").drawAt(400, 100);
    }
};

void Main()
{
    Window::SetTitle(U"シロナと願いの石～みんなともだち～");

	// フォント
    FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
    FontAsset::Register(U"StoryFont", 30);

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
    TextureAsset::Register(U"シロナ", U"Data/Image/story/sirona.png");
    TextureAsset::Register(U"リンドル", U"Data/Image/story/rindol.png");
    TextureAsset::Register(U"チャマ", U"Data/Image/story/chama.png");
    TextureAsset::Register(U"ファイ", U"Data/Image/story/phi.png");
    TextureAsset::Register(U"エメ", U"Data/Image/story/eme.png");
    TextureAsset::Register(U"メルヴィ", U"Data/Image/story/meruby.png");
    TextureAsset::Register(U"next", U"Data/Image/story/next.png");

    // 音
    AudioAsset::Register(U"se_click", U"Data/Sound/se/click.ogg");
    AudioAsset::Register(U"se_cancel", U"Data/Sound/se/cancel.ogg");
    AudioAsset::Register(U"se_step", U"Data/Sound/se/step.ogg");
    AudioAsset::Register(U"se_select", U"Data/Sound/se/select.ogg");

	// シーンマネージャーを作成
	App manager;

	// シーン登録
	manager.add<Title>(U"Title");
    manager.add<Select>(U"Select");
    manager.add<Puzzle>(U"Puzzle");
    manager.add<StorySelect>(U"StorySelect");
    manager.add<Story>(U"Story");
    manager.add<HowToPlay>(U"HowToPlay");

	while (System::Update())
	{
        // 現在のシーンを実行
        if (!manager.update())
        {
            break;
        }
	}
}