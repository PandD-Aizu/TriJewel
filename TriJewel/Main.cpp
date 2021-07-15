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

    }

    // 描画関数 (const 修飾)
    void draw() const override
    {
        Scene::SetBackground(ColorF(0.3, 0.4, 0.5));

        FontAsset(U"TitleFont")(U"TriJewel(仮)").drawAt(400, 100);

        Circle(Cursor::Pos(), 50).draw(Palette::Orange);
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

	while (System::Update())
	{
        // 現在のシーンを実行
        if (!manager.update())
        {
            break;
        }
	}
}