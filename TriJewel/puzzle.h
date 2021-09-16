#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <siv3D.hpp>

#define STAGE_SIZE 12

#define ROAD 0
#define WALL 1
#define ROCK 2
#define GOAL 3
#define BOX 4
#define PLACE 5
#define DOOR 6

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// �v���C���[
typedef struct {
	int i, j;	// �Y����
	int x, y;	// ���W
	int width, height;	// ���̒����A�c�̒���
	int direction;	// ����
}Player;

// �u���b�N
typedef struct {
	int i, j;	// �Y����
	int x, y;	// ���W
	int width, height;	// ���̒����A�c�̒���
	int type;	// ����
	int flag;	// �������܂��Ă��邩�̃t���O
}Block;

void readfile(String); // �p�Y���f�[�^�p�t�@�C���ǂݍ���
void puzzle_init(int, int);		// �p�Y���̏�����
int puzzle_update();	// �p�Y���̍X�V�֐�
void puzzle_draw();		// �p�Y���̕`��֐�

void baseinit();		// base_data�̏������֐�

bool objstack(char, int);	 //	��A�����������̔���
bool playerstack(char, int);		//�v���C���[�������邩�̔���

void objmove(char, int);	//��A���̈ړ�����

bool checkdoor();		//�����J�����̔���
#endif