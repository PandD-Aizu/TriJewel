# include <Siv3D.hpp>

using App = SceneManager<String>;

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
            changeScene(U"Select");
        }

        // 「おはなし」ボタン
        if (SimpleGUI::Button(U"おはなし", Vec2(400 - button_width / 2, 300), button_width))
        {
            changeScene(U"StorySelect");
        }

        // 「あそびかた」ボタン
        if (SimpleGUI::Button(U"あそびかた", Vec2(400 - button_width / 2, 350), button_width))
        {
            changeScene(U"HowToPlay");
        }

        // 「おわる」ボタン
        if (SimpleGUI::Button(U"おわる", Vec2(400 - button_width / 2, 400), button_width))
        {
            System::Exit();
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

        FontAsset(U"TitleFont")(U"TriJewel(仮)").drawAt(400, 100);
    }
};

// ステージセレクトシーン
class Select : public App::Scene
{
private:
    int mode;   // シーン内モード管理(レベル選択 <---> ステージ選択)

public:

    // コンストラクタ（必ず実装）
    Select(const InitData& init)
        : IScene(init)
    {
        mode = 0;
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
                changeScene(U"Title");
            }

            // どれかのレベルが選択されたら、ステージ選択へ移動する
            if (SimpleGUI::Button(U"かんたん", Vec2(100, Scene::Height() / 2 - 50)))
            {
                mode = 1;
            }
            if (SimpleGUI::Button(U"ふつう", Vec2(300, Scene::Height() / 2 - 50)))
            {
                mode = 1;
            }
            if (SimpleGUI::Button(U"むずかしい", Vec2(500, Scene::Height() / 2 - 50)))
            {
                mode = 1;
            }
            break;

        // ステージ選択
        case 1:
            // レベル選択へ戻る
            if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
            {
                mode = 0;
            }

            // パズル画面へ移動する
            if (SimpleGUI::Button(U"1", Vec2(100, 100)))
            {
                
            }
            break;

        default:
            break;
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

        FontAsset(U"TitleFont")(U"ステージセレクト").drawAt(400, 100);
    }
};

// ストーリーセレクトシーン
class StorySelect : public App::Scene
{
private:
    int mode;   // シーン内モード管理(章選択 <---> 話数選択)

public:

    // コンストラクタ（必ず実装）
    StorySelect(const InitData& init)
        : IScene(init)
    {
        mode = 0;
    }

    // 更新関数
    void update() override
    {
        switch (mode) {
        case 0:
            // タイトルへ戻る
            if (SimpleGUI::Button(U"タイトル", Vec2(10, 10)))
            {
                changeScene(U"Title");
            }

            // どれかの物語が選択されたら、話数選択画面へ移動する
            if (SimpleGUI::Button(U"物語1", Vec2(100, Scene::Height() / 2 - 50)))
            {
                mode = 1;
            }
            if (SimpleGUI::Button(U"物語2", Vec2(200, Scene::Height() / 2 - 50)))
            {
                mode = 1;
            }
            if (SimpleGUI::Button(U"物語3", Vec2(300, Scene::Height() / 2 - 50)))
            {
                mode = 1;
            }
            break;

        case 1:
            // 章選択画面へ戻る
            if (SimpleGUI::Button(U"もどる", Vec2(10, 10)))
            {
                mode = 0;
            }

            // ストーリー再生画面へ移動する
            if (SimpleGUI::Button(U"1", Vec2(50, 50)))
            {

            }
            break;

        default:
            break;
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

        FontAsset(U"TitleFont")(U"ストーリーセレクト").drawAt(400, 100);
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
            changeScene(U"Title");
        }
    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

        FontAsset(U"TitleFont")(U"あそびかた").drawAt(400, 100);
    }
};

void Main()
{
    Window::SetTitle(U"TriJewel(仮)");

	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

	// シーンマネージャーを作成
	App manager;

	// シーン登録
	manager.add<Title>(U"Title");
    manager.add<Select>(U"Select");
    manager.add<StorySelect>(U"StorySelect");
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