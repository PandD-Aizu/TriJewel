#include"story.h"

static Actor actors[6];	// �L�����N�^�[�B
static Array<Dialogue> dialogue;	// �Z���t
static int scene;	// �Z���t�ԍ�

static int playing;	// �Z���t�Đ������ǂ����t���O
static int start;	// �J�n����(�Z���t�Đ��̂��߂ɕK�v)
static int length;	// �\��������Z���t�̒���

// �X�g�[���[�̏�����
void story_init(int chapter, int story) {
	// �t�@�C���ǂݍ��ݗp�ϐ�
	TextReader reader(U"Data/Story/test.txt");
	String line;

	// �ǂݍ��݃f�[�^
	int left, right;
	String text;
	int speaker;

	// �t�@�C�����ǂݍ��߂Ȃ������ꍇ�A�G���[���b�Z�[�W��\��������
	if (!reader){
		throw Error(U"Failed to open `test.txt`");
	}

	dialogue.clear();

	// �t�@�C���ǂݍ���
	while (1) {
		reader.readLine(line);
		left = Parse<int>(line);

		reader.readLine(line);
		right = Parse<int>(line);
		
		reader.readLine(text);
		
		reader.readLine(line);
		speaker = Parse<int>(line);

		dialogue.push_back(Dialogue(left, right, text, speaker));

		if (!reader.readLine(line)) break;
	}

	reader.close();

	scene = 0;
	start = Scene::Time() * 1000;
	playing = 0;
}

// �X�g�[���[�̍X�V�֐�
// �߂�l: �X�g�[���[�Đ����̏ꍇ�� 0
// �@�@�@  �Đ����I�����ꍇ�� 1 ��Ԃ�
int story_update() {
	if (MouseL.down()) {
		if (playing == 1) {
			if (scene == dialogue.size() - 1)
				return 1;

			scene++;
			start = Scene::Time() * 1000;
			playing = 0;
		}
		else {
			length = dialogue[scene].text.length();
		}
	}

	length = (int)((Scene::Time() * 1000 - start) / 50);

	if (length > dialogue[scene].text.length()) {
		playing = 1;
	}

	return 0;
}

// �X�g�[���[�̕`��֐�
void story_draw() {
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