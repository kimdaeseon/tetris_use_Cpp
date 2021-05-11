#pragma once
#include "Block.h"


class B_O_M_B : public Block {
private:
	int num;
public:
	B_O_M_B() {   // 블록 모양 지정
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

void B_O_M_B::print() {      //현재 위치에 맞게 커서를 이동한 후 블럭 출력

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
void B_O_M_B::del() {             // 현재 위치에 맞게 커서를 이동한후 ' '출력
	                              // 콘솔을 초기화 하지 않고 print() 한번더 호출하면 블록이 계속 남아있으므로
	                              // 지워주는 역할의 함수
	                              // print() -> del() 순서로 호출되어야함
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

void B_O_M_B::operator+(char board[][boardSize]) { // +연산자를 사용 안하므로 구현 x
}

void B_O_M_B::change() {  // 바꾸는게 의미 없으므로 구현 X
	return;
}