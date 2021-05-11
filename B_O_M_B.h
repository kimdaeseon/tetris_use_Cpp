#pragma once
#include "Block.h"


class B_O_M_B : public Block {
private:
	int num;
public:
	B_O_M_B() {   // ��� ��� ����
		num = 0;
		Blocksize.x = 1;
		Blocksize.y = 1;
		form = new char* [1];
		for (int i = 0; i < 1; i++) {
			form[i] = new char[1];
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

void B_O_M_B::print() {      //���� ��ġ�� �°� Ŀ���� �̵��� �� �� ���

	char a = 'B';
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			gotoxy(pos.x + j + 3, pos.y + i);
			if (form[i][j] == 127)
				std::cout << a;
		}
		std::cout << std::endl;
	}
}
void B_O_M_B::del() {             // ���� ��ġ�� �°� Ŀ���� �̵����� ' '���
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

void B_O_M_B::operator+(char board[][boardSize]) { // +�����ڸ� ��� ���ϹǷ� ���� x
}

void B_O_M_B::change() {  // �ٲٴ°� �ǹ� �����Ƿ� ���� X
	return;
}