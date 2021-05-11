#pragma once
#include <iostream>
#include <Windows.h>
#include "position.h"

#define boardSize 25

void gotoxy(int x, int y) {   // 콘솔창의 커서를 x, y로 이동시키는 함수
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Block {

public:
	Block() {  // 블록의 초기 위치
		pos.x = 5;
		pos.y = 0;
	}
	virtual void print() = 0; // 블록 출력
	virtual void del() = 0;  // 블록 출력 해제
	void move_Left() {  // 왼쪽 이동
		pos.x--;
	}
	void move_Right() { // 오른쪽 이동
		pos.x++;
	}
	void move_down() { // 아래 이동
		pos.y++;
	}
	int posX() {
		return pos.x;
	}
	int posY() {
		return pos.y;
	}
	int blockSizeX() {
		return Blocksize.x;
	}
	int blockSizeY() {
		return Blocksize.y;
	}
	void setposX(int x) {
		pos.x = x;
	}
	void setposY(int y) {
		pos.y = y;
	}
	char getform(int x, int y) { 
		return form[x][y];
	}
	virtual void operator+(char board[][boardSize]) = 0; // 블록이 바닥에 닿았을때 블록을 tetris에 포함시키는 연산자
	virtual void change() = 0; // 회전
	void init_pos() {  // 위치 초기화
		pos.x = 5;
		pos.y = 0;
	}

protected:
	position pos;      //블록 위치
	position Blocksize; //블록 크기
	char** form;  // 블록 모양
};