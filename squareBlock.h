#pragma once
#include "Block.h"

#define blockSize_X 2
#define blockSize_Y 2


class squareBlock : public Block{
	int num;       // ����� ȸ�� ���¸� ��Ÿ���� ����
public:
	squareBlock() {   // ��� ��� ����
		num = 0;
		Blocksize.x = 2;
		Blocksize.y = 2;
		form = new char*[2];
		for (int i = 0; i < 2; i++) {
			form[i] = new char[2];
		}
		for (int i = 0; i < Blocksize.x; i++) {
			for (int j = 0; j < Blocksize.y; j++) {
				form[i][j] = 127;
			}
		}

	}
	virtual void print();
	virtual void del();
	virtual void operator+(char board[][boardSize]);
	virtual void change();
};

void squareBlock::print() {      //���� ��ġ�� �°� Ŀ���� �̵��� �� �� ���

	char a = 127;
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			gotoxy(pos.x + j+3, pos.y + i);
			if (form[i][j] == 127)
				std::cout << a;
		}
		std::cout << std::endl;
	}
}
void squareBlock::del() {          // ���� ��ġ�� �°� Ŀ���� �̵����� ' '���
								  // �ܼ��� �ʱ�ȭ ���� �ʰ� print() �ѹ��� ȣ���ϸ� ����� ��� ���������Ƿ�
								  // �����ִ� ������ �Լ�
								  // print() -> del() ������ ȣ��Ǿ����
	char a = ' ';
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			gotoxy(pos.x + j+3, pos.y + i);
			if (form[i][j] == 127)
				std::cout << a;
		}
		std::cout << std::endl;
	}
}
void squareBlock::operator+(char board[][boardSize]) {   // ���� ����� ��ġ�� �°� ��Ʈ���� ���� ���Ҹ� 127�� �ʱ�ȭ
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			if (form[i][j] == 127)
				board[j + pos.x][i + pos.y] = 127;
		}
	}
}
void squareBlock::change() {  // ȸ���Ͽ��� ����� �����Ƿ� ���� X
	return;
}