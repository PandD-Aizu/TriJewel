#include"puzzle.h"

static Grid<int> stage_data;	// �X�e�[�W���

static Player player;

// �p�Y���̏�����
void puzzle_init(int diff, int stage) {

	// �X�e�[�W�ǂݍ���

	//stage_data = {
		//{4,4,4,4,4,4,4},
		//{4,1,1,0,0,3,4},
		//{4,1,1,0,0,0,4},
		//{4,0,0,2,0,0,4},
	   // {4,0,0,0,1,1,4},
		//{4,0,0,0,1,1,4},
		//{4,4,4,4,4,4,4}
	//};

	stage_data = {
		{4,4,4,4,4,4,4,4,4,4,4,4},
		{4,0,0,0,0,0,0,5,4,4,4,4},
		{4,0,1,1,2,1,1,0,4,4,4,4},
		{4,0,0,0,6,0,0,0,4,4,4,4},
		{4,2,1,1,2,1,1,2,4,4,4,4},
		{4,0,0,0,6,0,0,0,4,4,4,4},
		{4,0,1,1,2,1,1,0,4,4,4,4},
		{4,5,0,0,0,0,0,0,7,0,3,4},
		{4,4,4,4,4,4,4,4,4,4,4,4}
	};

	// �v���C���[�������W
	player.i = 5;
	player.j = 1;

	player.x = 130;
	player.y = 250;

	if (player.x < 100) player.x = 100;
	if (player.x > 250) player.x = 250;
	if (player.y < 100) player.y = 100;
	if (player.y > 250) player.y = 250;

	if (player.i < 0) player.i = 0;
	if (player.i > stage_data.height()) player.i = stage_data.height();
	if (player.j < 0) player.j = 0;
	if (player.j > stage_data.width()) player.j = stage_data.width();


}

// �p�Y���̍X�V�֐�
// �߂�l: �p�Y���𑱍s���̏ꍇ�� 0
// �@�@�@  �N���A�����ꍇ�� 1 ��Ԃ�
int puzzle_update() {

	if (KeyUp.down()) {
		switch (stage_data[player.i - 1][player.j]) {
		case 0:
			player.y -= 30, player.i--;
			break;
		case 2:
			if (stage_data[player.i - 2][player.j] == 0) {
				stage_data[player.i - 1][player.j] = 0, stage_data[player.i - 2][player.j] = 2, player.y -= 30, player.i--;
			}
			break;
		case 3:
			player.y -= 30, player.i--;
			return 1;
			break;
		}
	}
	else if (KeyDown.down()) {
		switch (stage_data[player.i + 1][player.j]) {
		case 0:
			player.y += 30, player.i++;
			break;
		case 2:
			if (stage_data[player.i + 2][player.j] == 0) {
				stage_data[player.i + 1][player.j] = 0, stage_data[player.i + 2][player.j] = 2, player.y += 30, player.i++;
			}
			break;
		case 3:
			player.y += 30, player.i++;
			return 1;
			break;
		}
	}
	else if (KeyRight.down()) {
		switch (stage_data[player.i][player.j + 1]) {
		case 0:
			player.x += 30, player.j++;
			break;
		case 2:
			if (stage_data[player.i][player.j + 2] == 0) {
				stage_data[player.i][player.j + 1] = 0, stage_data[player.i][player.j + 2] = 2, player.x += 30, player.j++;
			}
			break;
		case 3:
			player.x += 30, player.j++;
			return 1;
			break;
		}
	}
	else if (KeyLeft.down()) {
		switch (stage_data[player.i][player.j - 1]) {
		case 0:
			player.x -= 30, player.j--;
			break;
		case 2:
			if (stage_data[player.i][player.j - 2] == 0) {
				stage_data[player.i][player.j - 1] = 0, stage_data[player.i][player.j - 2] = 2, player.x -= 30, player.j--;
			}
			break;
		case 3:
			player.x -= 30, player.j--;
			return 1;
			break;
		}
	}
	/*** ������ҏW���Ă������� ***/
	return 0;
}

// �p�Y���̕`��֐�
void puzzle_draw() {



	/*** ������ҏW���Ă������� ***/

	for (int i = 0; i < stage_data.width(); i++) {
		for (int j = 0; j < stage_data.height(); j++) {
			switch (stage_data[i][j]) {
			case 0:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Green);
				break;

			case 1:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Gray);
				break;

			case 2:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Orange);
				break;

			case 3:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Yellow);
				break;


			case 4:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Black);
				break;

			case 5:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Red);
				break;

			case 6:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::White);
				break;

			case 7:
				Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Black);
				break;

			}
		}
	}
	//��l��
	Rect(player.x, player.y, 30, 30).draw(Palette::Blue);
}

bool objmove() {
	return true;
}

bool playermove() {
	return true;
}