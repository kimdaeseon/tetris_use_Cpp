#pragma once
#include <iostream>
#include <Windows.h>
#include "position.h"

#define boardSize 25

void gotoxy(int x, int y) {   // �ܼ�â�� Ŀ���� x, y�� �̵���Ű�� �Լ�
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Block {

public:
	Block() {  // ����� �ʱ� ��ġ
		pos.x = 5;
		pos.y = 0;
	}
	virtual void print() = 0; // ��� ���
	virtual void del() = 0;  // ��� ��� ����
	void move_Left() {  // ���� �̵�
		pos.x--;
	}
	void move_Right() { // ������ �̵�
		pos.x++;
	}
	void move_down() { // �Ʒ� �̵�
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
	virtual void operator+(char board[][boardSize]) = 0; // ����� �ٴڿ� ������� ����� tetris�� ���Խ�Ű�� ������
	virtual void change() = 0; // ȸ��
	void init_pos() {  // ��ġ �ʱ�ȭ
		pos.x = 5;
		pos.y = 0;
	}

protected:
	position pos;      //��� ��ġ
	position Blocksize; //��� ũ��
	char** form;  // ��� ���
};