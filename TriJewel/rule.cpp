#include"rule.h"

// ルール説明描画
void drawRule() {
	/*** ここを編集してください ***/
	
	FontAsset(U"RuleFont")(U"・道中の障害物を移動させてゴールを目指しましょう").draw(31, 161,Palette::Black);
	FontAsset(U"RuleFont")(U"・道中の障害物を移動させてゴールを目指しましょう").draw(30, 160);

	FontAsset(U"RuleFont")(U"・ステージ選択やプレーヤーの移動のような基本操作はマウスで").draw(31, 191,Palette::Black);
	FontAsset(U"RuleFont")(U"行います").draw(31, 221,Palette::Black); 
	FontAsset(U"RuleFont")(U"・ステージ選択やプレーヤーの移動のような基本操作はマウスで").draw(30, 190);
	FontAsset(U"RuleFont")(U"行います").draw(30, 220);

	TextureAsset(U"player").draw(30, 370);
	FontAsset(U"RuleFont")(U"操作するプレーヤーキャラ").draw(71, 371,Palette::Black);
	FontAsset(U"RuleFont")(U"操作するプレーヤーキャラ").draw(70, 370);
	TextureAsset(U"wall").draw(30, 400);
	FontAsset(U"RuleFont")(U"外壁：通過及び移動もできない障害物").draw(71, 401,Palette::Black);
	FontAsset(U"RuleFont")(U"外壁：通過及び移動もできない障害物").draw(70, 400);
	TextureAsset(U"rock").draw(30, 430);
	FontAsset(U"RuleFont")(U"岩：移動させることができる障害物").draw(71, 431,Palette::Black);
	FontAsset(U"RuleFont")(U"岩：移動させることができる障害物").draw(70, 430);
	TextureAsset(U"goal").draw(30, 460);
	FontAsset(U"RuleFont")(U"ゴール：この地点に到達することでクリアになる").draw(71, 461,Palette::Black);
	FontAsset(U"RuleFont")(U"ゴール：この地点に到達することでクリアになる").draw(70, 460);
	TextureAsset(U"box").draw(30, 490);
	FontAsset(U"RuleFont")(U"箱：移動させることができる障害物").draw(71, 491,Palette::Black);
	FontAsset(U"RuleFont")(U"箱：移動させることができる障害物").draw(70, 490);
	TextureAsset(U"place").draw(30, 520);
	FontAsset(U"RuleFont")(U"配置場所：通過可能。箱と重なることで扉が開く").draw(71, 521,Palette::Black);
	FontAsset(U"RuleFont")(U"配置場所：通過可能。箱と重なることで扉が開く").draw(70, 520);
	TextureAsset(U"door").draw(30, 550);
	FontAsset(U"RuleFont")(U"扉：全ての配置場所に箱が設置されることで通れるようになる").draw(71, 551,Palette::Black);
	FontAsset(U"RuleFont")(U"扉：全ての配置場所に箱が設置されることで通れるようになる").draw(70, 550);
}