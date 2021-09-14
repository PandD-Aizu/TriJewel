#ifndef _PUZZLE_H_
#define _PUZZLE_H_

#include <siv3D.hpp>

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

void puzzle_init(int, int);		// �p�Y���̏�����
int puzzle_update();	// �p�Y���̍X�V�֐�
void puzzle_draw();		// �p�Y���̕`��֐�

bool objstack(char, int);	 //	��A�����������̔���
bool playerstack(char, int);		//�v���C���[�������邩�̔���
#endif