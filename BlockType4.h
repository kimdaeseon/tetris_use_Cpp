#pragma once
#include "Block.h"


class BlockType4 : public Block {
	int num;       // 블록의 회전 형태를 나타내는 변수
public:
	BlockType4() {  // 블록 모양 지정
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

void BlockType4::print() {      //현재 위치에 맞게 커서를 이동한 후 블럭 출력

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
void BlockType4::del() {          // 현재 위치에 맞게 커서를 이동한후 ' '출력
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
void BlockType4::operator+(char board[][boardSize]) {   // 현재 블록의 위치에 맞게 테트리스 보드 원소를 127로 초기화
	for (int i = 0; i < Blocksize.x; i++) {
		for (int j = 0; j < Blocksize.y; j++) {
			if (form[i][j] == 127)
				board[j + pos.x][i + pos.y] = 127;
		}
	}
}
void BlockType4::change() {                              // 회전할때의 모양의 맞게 블록의 크기 변수를 수정하고
														 // 모양에 맞게 form 배열을 초기화한다.	
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