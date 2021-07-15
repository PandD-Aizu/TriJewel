#ifndef _STORY_H_
#define _STORY_H_

#include <siv3D.hpp>

// �A�N�^�[
typedef struct {
	int id;	// �ԍ�
	s3d::String name;	// ���O
	int x, y;	// ���W
	int width, height;	// ���̒����A�c�̒���
}Actor;

// �Z���t
typedef struct {
	int left, right;	// ���ɗ��L�����A�E�ɗ��L����(�e�L�����ɂ� 0�`5 �̔ԍ�������U���܂��B-1�̏ꍇ�A�L�����͕\������܂���)
	s3d::String text;	// �Z���t
	int speaker;	// �b��(0: �N������Ȃ��A1: ���̃L�����A2: �E�̃L����)
}Dialogue;

void story_init(int, int);	// �X�g�[���[�̏�����
int story_update();	// �X�g�[���[�̍X�V�֐�
void story_draw();	// �X�g�[���[�̕`��֐�

#endif