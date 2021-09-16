#include"puzzle.h"

static Grid<int> stage_data;	// �X�e�[�W���
static Array<Grid<int>> stage_data_log;	// �X�e�[�W���̃��O
static Grid<int> stage_data_init;	// �X�e�[�W���(�������)
static Grid<int> base_data;		//��┠���������X�e�[�W���

static Player player;	// �v���C���[
static Array<Player> player_log;	// �v���C���[�̈ړ����O

int BoxNum = 0;		//�z�u�ꏊ�i���j�̐����J�E���g����ϐ�

// �p�Y���f�[�^�p�t�@�C���ǂݍ���
void readfile(String file) {
	TextReader reader;
	String line;

	if (!reader.open(file)) {
		throw Error(U"Failed to open `" + file + U"`");
	}

	std::stringstream ss;

	stage_data = Grid<int>(STAGE_SIZE, STAGE_SIZE);

	int i = 0;
	while (reader.readLine(line)) {
		ss << line;
		if (i < STAGE_SIZE) {
			for (int j = 0; j < STAGE_SIZE; j++) {
				ss >> stage_data[i][j];
			}
		}

		else {
			ss >> player.i;
			ss >> player.j;
		}

		i++;
	}

	player.x = 100 + player.j * 30;
	player.y = 100 + player.i * 30;

	player.direction = UP;

	reader.close();
}

// �p�Y���̏�����
void puzzle_init(int diff, int stage) {


	// �X�e�[�W�ǂݍ���
	readfile(U"./Data/Stage/{}/{:0>2}.txt"_fmt(diff, stage));
	stage_data_init = Grid<int>(stage_data.width(), stage_data.height());
	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			stage_data_init[i][j] = stage_data[i][j];
		}
	}

	base_data = Grid<int>(stage_data.width(), stage_data.height(), -1);
	baseinit();

	/*
	stage_data = {
		{1,1,1,1,1,1,1},
		{1,1,1,0,0,3,1},
		{1,1,1,0,0,0,1},
		{1,0,0,2,0,0,1},
		{1,0,0,0,1,1,1},
		{1,0,0,0,1,1,1},
		{1,1,1,1,1,1,1}
	};

	// �v���C���[�������W
	player.i = 5;
	player.j = 1;

	player.x = 130;
	player.y = 250;
	*/

	player.width = 30;
	player.height = 30;

	if (player.x < 100) player.x = 100;
	if (player.x > 100 + player.width * stage_data.width()) player.x = 100 + player.width * stage_data.width();
	if (player.y < 100) player.y = 100;
	if (player.y > 100 + player.height * stage_data.height()) player.y = 100 + player.height * stage_data.height();

	if (player.i < 0) player.i = 0;
	if (player.i > stage_data.height()) player.i = stage_data.height() - 1;
	if (player.j < 0) player.j = 0;
	if (player.j > stage_data.width()) player.j = stage_data.width() - 1;

	// ���O�̏�����
	player_log.clear();
	player_log << player;

	stage_data_log.clear();
	stage_data_log << stage_data;
}

// �p�Y���̍X�V�֐�
// �߂�l: �p�Y���𑱍s���̏ꍇ�� 0
// �@�@�@  �N���A�����ꍇ�� 1 ��Ԃ�
int puzzle_update() {
	/*** ������ҏW���Ă������� ***/

	//�v���C���[�ړ�
	if (KeyLeft.down()) {
		player.direction = LEFT;

		if (playerstack('x',-1)) {
			player.x -= player.width;
			player.j--;
		}

		player_log << player;
		stage_data_log << stage_data;
	}
	if (KeyRight.down()) {
		player.direction = RIGHT;

		if (playerstack('x', 1)) {
			player.x += player.width;
			player.j++;
		}

		player_log << player;
		stage_data_log << stage_data;
	}
	if (KeyUp.down()) {
		player.direction = UP;

		if (playerstack('y', -1)) {
			player.y -= player.height;
			player.i--;
		}

		player_log << player;
		stage_data_log << stage_data;
	}
	if (KeyDown.down()) {
		player.direction = DOWN;

		if (playerstack('y', 1)) {
			player.y += player.height;
			player.i++;
		}

		player_log << player;
		stage_data_log << stage_data;
	}

	// ����߂�
	if (MouseR.down() && player_log.size() > 1) {
		player_log.pop_back();
		player = player_log.back();

		stage_data_log.pop_back();
		stage_data = stage_data_log.back();
	}

	//�����J����
	if (checkdoor()) {
		for (int i = 0; i < stage_data.height(); i++) {
			for (int j = 0; j < stage_data.width(); j++) {
				if (stage_data[i][j] == DOOR) {
					stage_data[i][j] = ROAD;
				}
			}
		}
	}

	// �N���A
	if (stage_data[player.i][player.j] == GOAL) {
		return 1;
	}

	// �p�Y���̃��Z�b�g
	if (SimpleGUI::Button(U"���Ȃ���", Vec2(120, 10))) {
		player = player_log[0];
		player_log.clear();
		player_log << player;

		for (int i = 0; i < stage_data.height(); i++) {
			for (int j = 0; j < stage_data.width(); j++) {
				stage_data[i][j] = stage_data_init[i][j];
			}
		}
	}

	// �S�[��
	if (stage_data[player.i][player.j] == GOAL) {
		return 1;
	}

	return 0;
}

// �p�Y���̕`��֐�
void puzzle_draw() {
	/*** ������ҏW���Ă������� ***/

	for (int i = 0; i < stage_data.width(); i++) {
		for (int j = 0; j < stage_data.height(); j++) {
			TextureAsset(U"road").draw(100 + j * 30, 100 + i * 30);

			switch (stage_data[i][j]) {
			case ROAD:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Green);
				TextureAsset(U"road").draw(100 + j * 30, 100 + i * 30);
				break;

			case WALL:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Gray);
				TextureAsset(U"wall").draw(100 + j * 30, 100 + i * 30);
				break;

			case ROCK:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Orange);
				TextureAsset(U"rock").draw(100 + j * 30, 100 + i * 30);
				break;

			case GOAL:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Yellow);
				TextureAsset(U"goal").draw(100 + j * 30, 100 + i * 30);
				break;

			case BOX:
				//Rect(100 + j * 30, 100 + i * 30, 30, 30).draw(Palette::Black);
				TextureAsset(U"box").draw(100 + j * 30, 100 + i * 30);
				break;

			case PLACE:
				TextureAsset(U"place").draw(100 + j * 30, 100 + i * 30);
				break;

			case DOOR:
				TextureAsset(U"door").draw(100 + j * 30, 100 + i * 30);
				break;

			default:
				break;
			}
		}
	}
	//��l��
	//Rect(player.x, player.y, 30, 30).draw(Palette::Blue);
	TextureAsset(U"player").rotated(player.direction * 90_deg).draw(player.x, player.y);

	SimpleGUI::Button(U"���Ȃ���", Vec2(120, 10));
}


// base_data�̏������֐�
void baseinit() {
	BoxNum = 0;
	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			// ��Ɣ��̉��ɂ͓�������
			if (stage_data[i][j] == ROCK || stage_data[i][j] == BOX) {
				base_data[i][j] = ROAD;
			}
			else {
				base_data[i][j] = stage_data[i][j];
			}

			// ��(�z�u�ꏊ)�̐����J�E���g
			if (stage_data[i][j] == PLACE) {
				BoxNum++;
			}
		}
	}
}

// ��A�����������̔���
bool objstack(char t, int n) {
	int data = -1;

	if (t == 'x') {
		if (n > 0) {
			data = stage_data[player.i][player.j + 2];
		}
		else {
			data = stage_data[player.i][player.j - 2];
		}
	}
	else if (t == 'y') {
		if (n > 0) {
			data = stage_data[player.i + 2][player.j];
		}
		else {
			data = stage_data[player.i - 2][player.j];
		}
	}

	if (data == ROAD || data == GOAL || data == PLACE) {
		return true;
	}
	else {
		return false;
	}
}

// �v���C���[�������邩�̔���
bool playerstack(char t, int n) {
	int data = -1;

	if (t == 'x') {
		if (n > 0) {
			data = stage_data[player.i][player.j + 1];
		}
		else {
			data = stage_data[player.i][player.j - 1];
		}
	}
	else if (t == 'y') {
		if (n > 0) {
			data = stage_data[player.i + 1][player.j];
		}
		else {
			data = stage_data[player.i - 1][player.j];
		}
	}
	else
		return false;

	if (data == ROAD || data == GOAL || data == PLACE) {
		return true;
	}
	else if (data == ROCK || data == BOX) {
		if (objstack(t, n)) {
			objmove(t, n);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

// ��A���̈ړ�����
void objmove(char t, int n) {
	if (objstack(t, n)) {
		if (t == 'x') {
			if (n > 0) {
				stage_data[player.i][player.j + 2] = stage_data[player.i][player.j + 1];
				stage_data[player.i][player.j + 1] = base_data[player.i][player.j + 1];
			}
			else {
				stage_data[player.i][player.j - 2] = stage_data[player.i][player.j - 1];
				stage_data[player.i][player.j - 1] = base_data[player.i][player.j - 1];
			}
		}
		else if (t == 'y') {
			if (n > 0) {
				stage_data[player.i + 2][player.j] = stage_data[player.i + 1][player.j];
				stage_data[player.i + 1][player.j] = base_data[player.i + 1][player.j];
			}
			else {
				stage_data[player.i - 2][player.j] = stage_data[player.i - 1][player.j];
				stage_data[player.i - 1][player.j] = base_data[player.i - 1][player.j];
			}
		}
	}
}

// �����J�����̔���
bool checkdoor(){
	int n = 0;

	for (int i = 0; i < stage_data.height(); i++) {
		for (int j = 0; j < stage_data.width(); j++) {
			if ((stage_data[i][j] == BOX) && (base_data[i][j] == PLACE)) {
				n++;
			}
		}
	}

	if (BoxNum == n) {
		return true;
	}
	else{
		return false;
	}
}