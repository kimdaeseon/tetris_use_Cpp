#pragma once

#define board_X 10
#define board_Y 25

void printTetris(char[][board_Y], Block* block, Block* next, int &score, int &Bomb_count);      // tetris 보드판 출력
int makeBlock(Block*& block, int num);         // 블록 생성
bool check(char tetris[][board_Y], Block* block);  // 블록이 바닥에 닿았는지 판단
bool check_left(char tetris[][board_Y], Block* block);  // 블록이 왼쪽으로 이동 가능한지 판단
bool check_right(char tetris[][board_Y], Block* block); // 블록이 오른쪽으로 이동 가능한지 판단
void lineClear(char tetris[][board_Y], Block* block, int &score);  // 한 줄이 가득차면 줄을 지우고 점수 증가
int CanIChange(char tetris[][board_Y], Block* block);   // 현재 블록이 회전가능한 상태인지 판단
void change(char tetris[][board_Y], Block* block);      // 블록 회전
void save_load_Block(char tetris[][board_Y], Block*& originalblock, Block*& saveBlock);  // 블록 저장
void B_O_M_B_C(char tetris[][board_Y], Block*& block); // 폭탄아이템으로 블록 바꾸기
void B_O_M_B_clear(char tetris[][board_Y], Block* block);  //폭탄아이템 효과 적용



void printTetris(char tetris[][board_Y], Block* block, Block* next, int &score, int &Bomb_count) {

	for (int i = 0; i < board_Y - 1; i++) {        // 보드 출력
		gotoxy(2, i);
		cout << '|';
		for (int j = 0; j < board_X; j++) {
			cout << tetris[j][i];
		}
		cout << '|';
		cout << endl;
	}
	gotoxy(3, board_Y - 1);
	for (int i = 0; i < board_X; i++) { 
		cout << '-';
	}
	gotoxy(2, board_Y + 1);                 // 점수 출력
	cout << "점수 : " << score << endl;


	gotoxy(16, 3);
	cout << "-SAVE-";                // SAVE되어있는 블록 출력
	if (block != nullptr) {
		int x = block->posX();
		int y = block->posY();
		int X = block->blockSizeX();
		int Y = block->blockSizeY();
		if (X > 2 && Y > 2) {
			block->setposX(14);
			block->setposY(4);
		}
		else if (X <= 2 && Y > 2) {
			block->setposX(14);
			block->setposY(5);
		}
		else if (X > 2 && Y <= 2) {
			block->setposX(15);
			block->setposY(4);
		}
		else if (X <= 2 && Y <= 2) {
			block->setposX(15);
			block->setposY(5);
		}
		block->print();
		block->setposX(x);
		block->setposY(y);
	}
	gotoxy(16, 8);
	cout << "------";
	gotoxy(16, 9);
	cout << "-NEXT-";                // 다음 블록이 어떤 블록인지 출력
	if (block != nullptr) {
		int x = next->posX();
		int y = next->posY();
		int X = next->blockSizeX();
		int Y = next->blockSizeY();
		if (X > 2 && Y > 2) {
			next->setposX(14);
			next->setposY(10);
		}
		else if (X <= 2 && Y > 2) {
			next->setposX(14);
			next->setposY(11);
		}
		else if (X > 2 && Y <= 2) {
			next->setposX(15);
			next->setposY(10);
		}
		else if (X <= 2 && Y <= 2) {
			next->setposX(15);
			next->setposY(11);
		}
		next->print();
		next->setposX(x);
		next->setposY(y);
	}
	gotoxy(16, 14);
	cout << "------";
	gotoxy(16, 15);
	cout << "Bomb : " << Bomb_count;  // 사용가능한 폭탄아이템 갯수 출력

}

int makeBlock(Block*& block, int num) {
	int rnd = rand() % 5;

	while (rnd == num) {     // 연속으로 같은 블록이 나오지 않게 하기 위함
		rnd = rand() % 5;
	}

	switch (rnd) {
	case 0:
		block = new squareBlock;   // ㅁㅁ
		break;                     // ㅁㅁ
	case 1:
		block = new BlockType1;    //   ㅁ 
		break;                     // ㅁㅁㅁ
	case 2:
		block = new BlockType2;    // ㅁㅁㅁ
		break;                     //     ㅁ
	case 3:
		block = new BlockType3;    // ㅁ
		break;                     // ㅁㅁ 
	case 4:                        //   ㅁ

		block = new BlockType4;    //  ㅁ
		break;                     //  ㅁ
	}                              //  ㅁ 
	                               //  ㅁ
	return rnd;
}

bool check(char tetris[][board_Y], Block* block) {

	int X = block->blockSizeX();
	int Y = block->blockSizeY();
	int posX = block->posX();
	int posY = block->posY();
	bool result = false;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (block->getform(i,j) == 127){
				if (tetris[posX + j][posY + i + 1] == 127) // 블록의 아래가 닿았을때 true 리턴
					return true;
			}
		}
	}
	return result;
}

bool check_left(char tetris[][board_Y], Block* block) {
	int X = block->blockSizeX();
	int Y = block->blockSizeY();
	int posX = block->posX();
	int posY = block->posY();
	bool result = false;

	if (block->posX() == 0)  // 블록이 보드를 넘어가면 안되므로 
		return true;

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (block->getform(i,j) == 127) {
				if (tetris[posX + j - 1][posY + i] == 127)   // 블록 왼쪽이 닿았을때 true 리턴
					return true;
			}
		}
	}

	return false;
}

bool check_right(char tetris[][board_Y], Block* block) {
	int X = block->blockSizeX();
	int Y = block->blockSizeY();
	int posX = block->posX();
	int posY = block->posY();
	bool result = false;

	if (block->posX() + Y == board_X)      // 블록이 보드를 넘어가면 안되므로
		return true;

	for (int i = 0; i < X; i++) {
		for (int j = Y - 1; j >= 0; j--) {
			if (block->getform(i,j) == 127) {
				if (tetris[posX + j + 1][posY + i] == 127)   // 블록의 오른쪽이 닿았을때 true리턴
					return true;
			}
		}
	}

	return false;
}

void lineClear(char tetris[][board_Y], Block* block, int &score) {

	int Y = block->posY() + block->blockSizeX() - 1;
	bool IsClear = false;;
	bool check = false;
	int count = 0;
	for (int j = Y; j > 0; j--) {            //바닥에 닿은 블록을 기준으로 블록의 높이만큼 tetris 보드를 탐색함
		for (int i = 0; i < board_X; i++) {
			if (tetris[i][j] == 127) { 
				count++;                      // tetris 보드의 원소가 127 count ++
			}
			if (count == 10)                  // 한줄에 10개의 원소가 있으므로 10개의 원소가 전부 127일경우
			{
				IsClear = true;               // IsClear = true;
				Y = j;
				check = true;                 // 한줄이라도 10개의 원소가 전부 127경우 2중 for문을 탈출하기 위한 bool 변수
				break;
			}
		}
		if (check)
			break;
		count = 0;

	}
	if (IsClear) {       // 모든 원소가 127인 줄이 존재한다면
		for (int i = 0; i < board_X; i++) {
			tetris[i][Y] = ' ';               // 줄 내용 지우기
		}
		score += 100;
		check = true;
		for (int i = Y; i > 0; i--) {    // 한줄씩 아래로 당기기
			for (int j = 0; j < board_X; j++) {
				tetris[j][i] = tetris[j][i - 1];
			}
		}
	}
	if (check)       // 또다른 줄이 있는지 확인하기 위해 함수를 다시 호출
		lineClear(tetris, block, score);

	return;
}

int CanIChange(char tetris[][board_Y], Block* block) {  
	// 블록을 회전함으로써 블록이 tetris판을 넘어가거나 블록이 다른 블록을 건들이는 경우를 막기위한 함수
	for (int i = 0; i < block->blockSizeY(); i++) {    
		if (tetris[block->posX()][block->posY() + i] == 127)
			return 3;  // 블록 아래에 장애물이 있음
	}
	if (block->posX() + block->blockSizeX() > board_X) {
		return 0;       // 블록이 회전하면 tetris의 오른쪽 경계를 넘어가는 경우
	}
	else {
		for (int i = 0; i < block->blockSizeY(); i++) {
			for (int j = 0; j < block->blockSizeX(); j++) {
				if (tetris[block->posX() + j][block->posY() + i] == 127) {
					return 1;   // 블록이 회전하는데에 있어서 오른쪽에 장애물이 있는경우
				}
			}
		}                     // 블록의 위치 기준이 왼쪽임으로 오른쪽과 아래만 판단하면 됨
	}

	return 2; // 블록이 회전하여도 됨
}

void change(char tetris[][board_Y], Block* block) {

	bool count = true;  // 회전 여부를 결정하는 bool 변수
	int num = 0; // 몇칸 이동하였는지 저장하는 변수
	switch (CanIChange(tetris, block)) {
	case 0:      // tetris의 오른쪽 경계를 넘어가는 경우
		while (true) {
			if (block->posX() < 0 || check_left(tetris, block)) {   //왼쪽으로 이동이 불가능한 경우 회전이 불가능한 경우라고 판단
				block->setposX(block->posX() + num); // 왼쪽으로 이동한만큼 다시 오른쪽으로 이동
				count = false; 
				break;
			}
			if (CanIChange(tetris, block) == 2)
				break;
			block->move_Left();  // 왼쪽으로 한칸씩 이동
			num++;   
		}
		if (count)
			block->change();  // 블록 회전
		break;
	case 1:
		while (true) {   // 블록의 오른쪽에 장애물이 있는 경우
			if (block->posX() < 0 || check_left(tetris, block)) {  // case 0과 과정은 동일함
				block->setposX(block->posX() + num);
				count = false;
				break;
			}
			if (CanIChange(tetris, block) == 2)
				break;
			block->move_Left();
			num++;
		}
		if (count)
			block->change();
		break;
	case 2:   // 회전이 가능한경우
		block->change();
		break;
	case 3:   // 바닥이 장애물이 되는경우는 회전 불가능
		break;
	}
	return;
}

void save_load_Block(char tetris[][board_Y], Block*& originalblock, Block*& saveBlock) {
		Block* temp = originalblock;  // originalblock과 saveblock 교체
		originalblock = saveBlock;
		saveBlock = temp;
		saveBlock->init_pos(); // 바뀐 블록은 위치정보를 가지고 있으므로 초기값으로 초기화
}

void B_O_M_B_C(char tetris[][board_Y], Block*& block) {

	delete block;           
	block = new B_O_M_B;   // 블록을 폭탄 블록으로 교체
}

void B_O_M_B_clear(char tetris[][board_Y], Block* block) {   // 폭탄 블록으로 인한 효과
	int x = block->posX();    
	int y = block->posY();
	                                                     // 폭탄 블록 기준으로 좌우로 4칸씩, 위아래로 4칸씩 원소를 ' '로 초기화
	for (int i = 0; i < 4; i++) {                          
		for (int j = 0; j <= i; j++) {
			if ((x - j) >= 0) {
				if ((y + i - 4) >= 0) {
					tetris[x - j][y + i - 4] = ' ';
				}
			}
		}
		for (int j = 0; j <= i; j++) {
			if ((x - j) < board_X) {
				if ((y + i - 4) >= 0) {
					tetris[x + j][y + i - 4] = ' ';
				}
			}
		}

	}
	for (int i = -4; i <= 4; i++) {
		if ((x + i) >= 0 && (x + i) < board_X) {
			tetris[x + i][y] = ' ';
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= i; j++) {
			if ((x - j) >= 0) {
				if ((y - i + 4) < board_Y - 1) {
					tetris[x - j][y - i + 4] = ' ';
				}
			}

		}
		for (int j = 0; j <= i; j++) {
			if ((x - j) < board_X) {
				if ((y - i + 4) < board_Y - 1) {
					tetris[x + j][y - i + 4] = ' ';
				}
			}
		}
	}
}