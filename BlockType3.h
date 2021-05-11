#pragma once

#include "Block.h"


class BlockType3 : public Block {
	int num;       // ����� ȸ�� ���¸� ��Ÿ���� ����
public:
	BlockType3() { // ��� ��� ����
		num = 0;
		Blocksize.x = 3;
		Blocksize.y = 2;
		form = new char* [3];
		for (int i = 0; i < 3; i++) {
			form[i] = new char[3];
		}
		for (int i = 0; i < Blocksize.x; i++) {
			for (int j = 0; j < Blocksize.y; j++) {
				form[i][j] = 127;
			}
		}
		form[0][1] = ' ';
		form[2][0] = ' ';
	}
	virtual void print();
	virtual void del();
	virtual void operator+(char board[][boardSize]);
	virtual void change();

//private:
};

void BlockType3::print() {      //���� ��ġ�� �°� Ŀ���� �̵��� �� �� ���

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
void BlockType3::del() {          // ���� ��ġ�� �°� Ŀ���� �̵����� ' '���
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

void BlockType3::operator+(char board[][boardSize]) {   // ���� ����� ��ġ�� �°� ��Ʈ���� ���� ���Ҹ� 127�� �ʱ�ȭ
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			if (form[i][j] == 127)
				board[j + pos.x][i + pos.y] = 127;
		}
	}
}
void BlockType3::change() {                              // ȸ���Ҷ��� ����� �°� ����� ũ�� ������ �����ϰ�
														 // ��翡 �°� form �迭�� �ʱ�ȭ�Ѵ�.	
	switch (num) {
	case 0:
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				form[i][j] = ' ';
			}
		}
		Blocksize.x = 2;
		Blocksize.y = 3;
		for (int i = 0; i < Blocksize.x; i++) {
			for (int j = 0; j < Blocksize.y; j++) {
				form[i][j] = 127;
			}
		}
		form[0][0] = ' ';
		form[1][2] = ' ';
		num++;
		break;
	}
	case 1:
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				form[i][j] = ' ';
			}
		}
		Blocksize.x = 3;
		Blocksize.y = 2;
		for (int i = 0; i < Blocksize.x; i++) {
			for (int j = 0; j < Blocksize.y; j++) {
				form[i][j] = 127;
			}
		}
		form[0][1] = ' ';
		form[2][0] = ' ';
		num = 0;
		break;
	}

	}
}