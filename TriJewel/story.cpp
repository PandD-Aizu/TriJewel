#include"story.h"

static Actor actors[6];	// �L�����N�^�[�B
static Array<Dialogue> dialogue;	// �Z���t

// �X�g�[���[�̏�����
void story_init(int chapter, int story) {
	dialogue = {
		Dialogue(0,1,U"�����͂����V�C�ł��ˁB",1),
		Dialogue(0,1,U"�͂��B���������v���܂��B", 2),
		Dialogue(-1,-1,U"���΂炭����...",0),
		Dialogue(1,2,U"�����Y��ł��ˁB",1),
		Dialogue(1,2,U"���̒ʂ�ł��B",2)
	};
}

// �X�g�[���[�̍X�V�֐�
// �߂�l: �X�g�[���[�Đ����̏ꍇ�� 0
// �@�@�@  �Đ����I�����ꍇ�� 1 ��Ԃ�
int story_update() {
	/*** ������ҏW���Ă������� ***/

	return 0;
}

// �X�g�[���[�̕`��֐�
void story_draw() {
	/*** ������ҏW���Ă������� ***/
}