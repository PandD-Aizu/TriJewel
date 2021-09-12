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
	player.height = 30;
	player.width = 30;
}

// �p�Y���̍X�V�֐�
// �߂�l: �p�Y���𑱍s���̏ꍇ�� 0
// �@�@�@  �N���A�����ꍇ�� 1 ��Ԃ�
int puzzle_update() {
	/*** ������ҏW���Ă������� ***/

	//�v���C���[�ړ�
	if (KeyLeft.down()) {
		if (player.i - 1 == (0 || 3 || 5)) {
			player.i--;
		}
		else if (player.i - 1 == (2 || 4)) {
			if (player.i - 2 == (0 || 3 || 5)) {
				player.i--;
			}
		}
	}
	if (KeyRight.down()) {
		if (player.i + 1 == (0 || 3 || 5)) {
			player.i++;
		}
		else if (player.i + 1 == (2 || 4)) {
			if (player.i + 2 == (0 || 3 || 5)) {
				player.i++;
			}
		}
	}
	if (KeyUp.down()) {
		if (player.j - 1 == (0 || 3 || 5)) {
			player.j--;
		}
		else if (player.j - 1 == (2 || 4)) {
			if (player.j - 2 == (0 || 3 || 5)) {
				player.j--;
			}
		}
	}
	if (KeyDown.down()) {
		if (player.j + 1 == (0 || 3 || 5)) {
			player.j++;
		}
		else if (player.j + 1 == (2 || 4)) {
			if (player.j + 2 == (0 || 3 || 5)) {
				player.j++;
			}
		}
	}

	return 0;
}

// �p�Y���̕`��֐�
void puzzle_draw() {
	/*** ������ҏW���Ă������� ***/
}

bool objmove() {

}

bool playermove() {

}