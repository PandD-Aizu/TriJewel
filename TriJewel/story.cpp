#include"story.h"

static Actor actors[6];	// �L�����N�^�[�B
static Array<Dialogue> dialogue;	// �Z���t
static int scene;	// �Z���t�ԍ�

static int start;

// �X�g�[���[�̏�����
void story_init(int chapter, int story) {
	dialogue = {
		Dialogue(0,1,U"�����͂����V�C�ł��ˁB\n�C���������ł��B",1),
		Dialogue(0,1,U"�͂��B���������v���܂��B", 2),
		Dialogue(-1,-1,U"���΂炭����...",0),
		Dialogue(1,2,U"�����Y��ł��ˁB",1),
		Dialogue(1,2,U"���̒ʂ�ł��B",2)
	};

	scene = 0;
	start = Scene::Time() * 1000;
}

// �X�g�[���[�̍X�V�֐�
// �߂�l: �X�g�[���[�Đ����̏ꍇ�� 0
// �@�@�@  �Đ����I�����ꍇ�� 1 ��Ԃ�
int story_update() {
	if (MouseL.down()) {
		if (scene == dialogue.size() - 1)
			return 1;
		
		scene++;
		start = Scene::Time() * 1000;
	}

	return 0;
}

// �X�g�[���[�̕`��֐�
void story_draw() {
	const int length = (int)((Scene::Time() * 1000 - start) / 50);
	const int namebox_size = 65;
	const int chara_size = 128;

	Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10, chara_size, chara_size).draw(Palette::Yellow);
	Rect(Scene::Width() / 16 * 15 - chara_size, (Scene::Height() / 16) * 12 - chara_size - namebox_size - 10, chara_size, chara_size).draw(Palette::Yellow);

	if (dialogue[scene].speaker != 0) {
		Rect namebox = Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12 - namebox_size, 150, namebox_size).draw(Palette::White).drawFrame(1, 0, Palette::Black);
		FontAsset(U"StoryFont")(U"�L����{}"_fmt(dialogue[scene].speaker)).draw(namebox.stretched(-10), Palette::Black);
	}

	Rect textbox = Rect(Scene::Width() / 16, (Scene::Height() / 16) * 12, (Scene::Width() / 16) * 14, (Scene::Height() / 16) * 3).draw(Palette::White).drawFrame(1, 0, Palette::Black);
	FontAsset(U"StoryFont")(dialogue[scene].text.substr(0, length)).draw(textbox.stretched(-10), Palette::Black);
}