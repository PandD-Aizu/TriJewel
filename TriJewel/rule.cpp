#include"rule.h"

// ���[�������`��
void drawRule() {
	/*** ������ҏW���Ă������� ***/
	
	FontAsset(U"RuleFont")(U"�E�����̏�Q�����ړ������ăS�[����ڎw���܂��傤").draw(31, 161,Palette::Black);
	FontAsset(U"RuleFont")(U"�E�����̏�Q�����ړ������ăS�[����ڎw���܂��傤").draw(30, 160);

	FontAsset(U"RuleFont")(U"�E�X�e�[�W�I����v���[���[�̈ړ��̂悤�Ȋ�{����̓}�E�X��").draw(31, 191,Palette::Black);
	FontAsset(U"RuleFont")(U"�s���܂�").draw(31, 221,Palette::Black); 
	FontAsset(U"RuleFont")(U"�E�X�e�[�W�I����v���[���[�̈ړ��̂悤�Ȋ�{����̓}�E�X��").draw(30, 190);
	FontAsset(U"RuleFont")(U"�s���܂�").draw(30, 220);

	TextureAsset(U"player").draw(30, 370);
	FontAsset(U"RuleFont")(U"���삷��v���[���[�L����").draw(71, 371,Palette::Black);
	FontAsset(U"RuleFont")(U"���삷��v���[���[�L����").draw(70, 370);
	TextureAsset(U"wall").draw(30, 400);
	FontAsset(U"RuleFont")(U"�O�ǁF�ʉߋy�шړ����ł��Ȃ���Q��").draw(71, 401,Palette::Black);
	FontAsset(U"RuleFont")(U"�O�ǁF�ʉߋy�шړ����ł��Ȃ���Q��").draw(70, 400);
	TextureAsset(U"rock").draw(30, 430);
	FontAsset(U"RuleFont")(U"��F�ړ������邱�Ƃ��ł����Q��").draw(71, 431,Palette::Black);
	FontAsset(U"RuleFont")(U"��F�ړ������邱�Ƃ��ł����Q��").draw(70, 430);
	TextureAsset(U"goal").draw(30, 460);
	FontAsset(U"RuleFont")(U"�S�[���F���̒n�_�ɓ��B���邱�ƂŃN���A�ɂȂ�").draw(71, 461,Palette::Black);
	FontAsset(U"RuleFont")(U"�S�[���F���̒n�_�ɓ��B���邱�ƂŃN���A�ɂȂ�").draw(70, 460);
	TextureAsset(U"box").draw(30, 490);
	FontAsset(U"RuleFont")(U"���F�ړ������邱�Ƃ��ł����Q��").draw(71, 491,Palette::Black);
	FontAsset(U"RuleFont")(U"���F�ړ������邱�Ƃ��ł����Q��").draw(70, 490);
	TextureAsset(U"place").draw(30, 520);
	FontAsset(U"RuleFont")(U"�z�u�ꏊ�F�ʉ߉\�B���Əd�Ȃ邱�ƂŔ����J��").draw(71, 521,Palette::Black);
	FontAsset(U"RuleFont")(U"�z�u�ꏊ�F�ʉ߉\�B���Əd�Ȃ邱�ƂŔ����J��").draw(70, 520);
	TextureAsset(U"door").draw(30, 550);
	FontAsset(U"RuleFont")(U"���F�S�Ă̔z�u�ꏊ�ɔ����ݒu����邱�ƂŒʂ��悤�ɂȂ�").draw(71, 551,Palette::Black);
	FontAsset(U"RuleFont")(U"���F�S�Ă̔z�u�ꏊ�ɔ����ݒu����邱�ƂŒʂ��悤�ɂȂ�").draw(70, 550);
}