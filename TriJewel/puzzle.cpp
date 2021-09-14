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
		if (playerstack('x',-1)) {
			player.i--;
		}
	}
	if (KeyRight.down()) {
		if (playerstack('x', 1)) {
			player.i++;
		}
	}
	if (KeyUp.down()) {
		if (playerstack('y', -1)) {
			player.j--;
		}
	}
	if (KeyDown.down()) {
		if (playerstack('y', 1)) {
			player.j++;
		}
	}

	return 0;
}

// �p�Y���̕`��֐�
void puzzle_draw() {
	/*** ������ҏW���Ă������� ***/
}

bool objstack(char t, int n) {
	int data;

	if (strcmp(&t, "x")) {
		if (n > 0) {
			data = stage_data[player.i + 2][player.j];
		}
		else {
			data = stage_data[player.i - 2][player.j];
		}
	}
	if (strcmp(&t, "y")) {
		if (n > 0) {
			data = stage_data[player.i][player.j + 2];
		}
		else {
			data = stage_data[player.i][player.j - 2];
		}
	}

	if (data == (0 || 3 || 5)) {
		return true;
	}
	else {
		return false;
	}
}

bool playerstack(char t, int n) {
	int data;

	if (strcmp(&t, "x")) {
		if (n > 0) {
			data = stage_data[player.i + 1][player.j];
		}
		else {
			data = stage_data[player.i - 1][player.j];
		}
	}
	if (strcmp(&t, "y")) {
		if (n > 0) {
			data = stage_data[player.i][player.j + 1];
		}
		else {
			data = stage_data[player.i][player.j - 1];
		}
	}
	else
		return false;

	if (data == (0 || 3 || 5)) {
		return true;
	}
	else if (data == (2 || 4)) {
		return objstack(t, n);
	}
	else {
		return false;
	}
}