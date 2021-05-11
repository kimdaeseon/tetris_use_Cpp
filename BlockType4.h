#pragma once
#include "Block.h"


class BlockType4 : public Block {
	int num;       // ����� ȸ�� ���¸� ��Ÿ���� ����
public:
	BlockType4() {  // ��� ��� ����
		num = 0;
		Blocksize.x = 4;
		Blocksize.y = 1;
		form = new char* [4];
		for (int i = 0; i < 4; i++) {
			form[i] = new char[4];
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
//private:
};

void BlockType4::print() {      //���� ��ġ�� �°� Ŀ���� �̵��� �� �� ���

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
void BlockType4::del() {          // ���� ��ġ�� �°� Ŀ���� �̵����� ' '���
								  // �ܼ��� �ʱ�ȭ ���� �ʰ� print() �ѹ��� ȣ���ϸ� ����� ��� ���������Ƿ�
								  // �����ִ� ������ �Լ�
								  // print() -> del() ������ ȣ��Ǿ����
	char a = ' ';
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			gotoxy(pos.x + j + 3, pos.y + i);
			if (form[i][j] == 127)
				std::cout << a;
		}
		std::cout << std::endl;
	}
}
void BlockType4::operator+(char board[][boardSize]) {   // ���� ����� ��ġ�� �°� ��Ʈ���� ���� ���Ҹ� 127�� �ʱ�ȭ
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			if (form[i][j] == 127)
				board[j + pos.x][i + pos.y] = 127;
		}
	}
}
void BlockType4::change() {                              // ȸ���Ҷ��� ����� �°� ����� ũ�� ������ �����ϰ�
														 // ��翡 �°� form �迭�� �ʱ�ȭ�Ѵ�.	
	switch (num) {
	case 0:
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				form[i][j] = ' ';
			}
		}
		Blocksize.x = 1;
		Blocksize.y = 4;
		for (int i = 0; i < Blocksize.x; i++) {
			for (int j = 0; j < Blocksize.y; j++) {
				form[i][j] = 127;
			}
		}
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
		Blocksize.x = 4;
		Blocksize.y = 1;
		for (int i = 0; i < Blocksize.x; i++) {
			for (int j = 0; j < Blocksize.y; j++) {
				form[i][j] = 127;
			}
		}
		num = 0;
		break;
	}
	case 2:
	{
		break;
	}
	case 3:
	{
		break;
	}

	}
}