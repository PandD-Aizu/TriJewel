#include"puzzle.h"

static Grid<int> stage_data;	// �X�e�[�W���
static Player player;

// �p�Y���̏�����
void puzzle_init(int diff, int stage) {

	// �X�e�[�W�ǂݍ���
	stage_data = {
		{1,1,0,0,3},
		{1,1,0,0,0},
		{0,0,2,0,0},
		{0,0,0,1,1},
		{0,0,0,1,1}
	};

	// �v���C���[�������W
	player.i = 4;
	player.j = 0;
}

// �p�Y���̍X�V�֐�
// �߂�l: �p�Y���𑱍s���̏ꍇ�� 0
// �@�@�@  �N���A�����ꍇ�� 1 ��Ԃ�
int puzzle_update() {
	/*** ������ҏW���Ă������� ***/

	return 0;
}

// �p�Y���̕`��֐�
void puzzle_draw() {
	/*** ������ҏW���Ă������� ***/
}