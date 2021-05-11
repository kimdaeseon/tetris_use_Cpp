#pragma once
#include "Block.h"

#define blockSize_X 2
#define blockSize_Y 2


class squareBlock : public Block{
	int num;       // 블록의 회전 형태를 나타내는 변수
public:
	squareBlock() {   // 블록 모양 지정
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

void squareBlock::print() {      //현재 위치에 맞게 커서를 이동한 후 블럭 출력

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
void squareBlock::del() {          // 현재 위치에 맞게 커서를 이동한후 ' '출력
								  // 콘솔을 초기화 하지 않고 print() 한번더 호출하면 블록이 계속 남아있으므로
								  // 지워주는 역할의 함수
								  // print() -> del() 순서로 호출되어야함
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
void squareBlock::operator+(char board[][boardSize]) {   // 현재 블록의 위치에 맞게 테트리스 보드 원소를 127로 초기화
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			if (form[i][j] == 127)
				board[j + pos.x][i + pos.y] = 127;
		}
	}
}
void squareBlock::change() {  // 회전하여도 모양이 같으므로 구현 X
	return;
}