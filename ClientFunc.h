#pragma once

#define board_X 10
#define board_Y 25

void printTetris(char[][board_Y], Block* block, Block* next, int &score, int &Bomb_count);      // tetris ������ ���
int makeBlock(Block*& block, int num);         // ��� ����
bool check(char tetris[][board_Y], Block* block);  // ����� �ٴڿ� ��Ҵ��� �Ǵ�
bool check_left(char tetris[][board_Y], Block* block);  // ����� �������� �̵� �������� �Ǵ�
bool check_right(char tetris[][board_Y], Block* block); // ����� ���������� �̵� �������� �Ǵ�
void lineClear(char tetris[][board_Y], Block* block, int &score);  // �� ���� �������� ���� ����� ���� ����
int CanIChange(char tetris[][board_Y], Block* block);   // ���� ����� ȸ�������� �������� �Ǵ�
void change(char tetris[][board_Y], Block* block);      // ��� ȸ��
void save_load_Block(char tetris[][board_Y], Block*& originalblock, Block*& saveBlock);  // ��� ����
void B_O_M_B_C(char tetris[][board_Y], Block*& block); // ��ź���������� ��� �ٲٱ�
void B_O_M_B_clear(char tetris[][board_Y], Block* block);  //��ź������ ȿ�� ����



void printTetris(char tetris[][board_Y], Block* block, Block* next, int &score, int &Bomb_count) {

	for (int i = 0; i < board_Y - 1; i++) {        // ���� ���
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
	gotoxy(2, board_Y + 1);                 // ���� ���
	cout << "���� : " << score << endl;


	gotoxy(16, 3);
	cout << "-SAVE-";                // SAVE�Ǿ��ִ� ��� ���
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
	cout << "-NEXT-";                // ���� ����� � ������� ���
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
	cout << "Bomb : " << Bomb_count;  // ��밡���� ��ź������ ���� ���

}

int makeBlock(Block*& block, int num) {
	int rnd = rand() % 5;

	while (rnd == num) {     // �������� ���� ����� ������ �ʰ� �ϱ� ����
		rnd = rand() % 5;
	}

	switch (rnd) {
	case 0:
		block = new squareBlock;   // ����
		break;                     // ����
	case 1:
		block = new BlockType1;    //   �� 
		break;                     // ������
	case 2:
		block = new BlockType2;    // ������
		break;                     //     ��
	case 3:
		block = new BlockType3;    // ��
		break;                     // ���� 
	case 4:                        //   ��

		block = new BlockType4;    //  ��
		break;                     //  ��
	}                              //  �� 
	                               //  ��
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
				if (tetris[posX + j][posY + i + 1] == 127) // ����� �Ʒ��� ������� true ����
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

	if (block->posX() == 0)  // ����� ���带 �Ѿ�� �ȵǹǷ� 
		return true;

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (block->getform(i,j) == 127) {
				if (tetris[posX + j - 1][posY + i] == 127)   // ��� ������ ������� true ����
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

	if (block->posX() + Y == board_X)      // ����� ���带 �Ѿ�� �ȵǹǷ�
		return true;

	for (int i = 0; i < X; i++) {
		for (int j = Y - 1; j >= 0; j--) {
			if (block->getform(i,j) == 127) {
				if (tetris[posX + j + 1][posY + i] == 127)   // ����� �������� ������� true����
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
	for (int j = Y; j > 0; j--) {            //�ٴڿ� ���� ����� �������� ����� ���̸�ŭ tetris ���带 Ž����
		for (int i = 0; i < board_X; i++) {
			if (tetris[i][j] == 127) { 
				count++;                      // tetris ������ ���Ұ� 127 count ++
			}
			if (count == 10)                  // ���ٿ� 10���� ���Ұ� �����Ƿ� 10���� ���Ұ� ���� 127�ϰ��
			{
				IsClear = true;               // IsClear = true;
				Y = j;
				check = true;                 // �����̶� 10���� ���Ұ� ���� 127��� 2�� for���� Ż���ϱ� ���� bool ����
				break;
			}
		}
		if (check)
			break;
		count = 0;

	}
	if (IsClear) {       // ��� ���Ұ� 127�� ���� �����Ѵٸ�
		for (int i = 0; i < board_X; i++) {
			tetris[i][Y] = ' ';               // �� ���� �����
		}
		score += 100;
		check = true;
		for (int i = Y; i > 0; i--) {    // ���پ� �Ʒ��� ����
			for (int j = 0; j < board_X; j++) {
				tetris[j][i] = tetris[j][i - 1];
			}
		}
	}
	if (check)       // �Ǵٸ� ���� �ִ��� Ȯ���ϱ� ���� �Լ��� �ٽ� ȣ��
		lineClear(tetris, block, score);

	return;
}

int CanIChange(char tetris[][board_Y], Block* block) {  
	// ����� ȸ�������ν� ����� tetris���� �Ѿ�ų� ����� �ٸ� ����� �ǵ��̴� ��츦 �������� �Լ�
	for (int i = 0; i < block->blockSizeY(); i++) {    
		if (tetris[block->posX()][block->posY() + i] == 127)
			return 3;  // ��� �Ʒ��� ��ֹ��� ����
	}
	if (block->posX() + block->blockSizeX() > board_X) {
		return 0;       // ����� ȸ���ϸ� tetris�� ������ ��踦 �Ѿ�� ���
	}
	else {
		for (int i = 0; i < block->blockSizeY(); i++) {
			for (int j = 0; j < block->blockSizeX(); j++) {
				if (tetris[block->posX() + j][block->posY() + i] == 127) {
					return 1;   // ����� ȸ���ϴµ��� �־ �����ʿ� ��ֹ��� �ִ°��
				}
			}
		}                     // ����� ��ġ ������ ���������� �����ʰ� �Ʒ��� �Ǵ��ϸ� ��
	}

	return 2; // ����� ȸ���Ͽ��� ��
}

void change(char tetris[][board_Y], Block* block) {

	bool count = true;  // ȸ�� ���θ� �����ϴ� bool ����
	int num = 0; // ��ĭ �̵��Ͽ����� �����ϴ� ����
	switch (CanIChange(tetris, block)) {
	case 0:      // tetris�� ������ ��踦 �Ѿ�� ���
		while (true) {
			if (block->posX() < 0 || check_left(tetris, block)) {   //�������� �̵��� �Ұ����� ��� ȸ���� �Ұ����� ����� �Ǵ�
				block->setposX(block->posX() + num); // �������� �̵��Ѹ�ŭ �ٽ� ���������� �̵�
				count = false; 
				break;
			}
			if (CanIChange(tetris, block) == 2)
				break;
			block->move_Left();  // �������� ��ĭ�� �̵�
			num++;   
		}
		if (count)
			block->change();  // ��� ȸ��
		break;
	case 1:
		while (true) {   // ����� �����ʿ� ��ֹ��� �ִ� ���
			if (block->posX() < 0 || check_left(tetris, block)) {  // case 0�� ������ ������
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
	case 2:   // ȸ���� �����Ѱ��
		block->change();
		break;
	case 3:   // �ٴ��� ��ֹ��� �Ǵ°��� ȸ�� �Ұ���
		break;
	}
	return;
}

void save_load_Block(char tetris[][board_Y], Block*& originalblock, Block*& saveBlock) {
		Block* temp = originalblock;  // originalblock�� saveblock ��ü
		originalblock = saveBlock;
		saveBlock = temp;
		saveBlock->init_pos(); // �ٲ� ����� ��ġ������ ������ �����Ƿ� �ʱⰪ���� �ʱ�ȭ
}

void B_O_M_B_C(char tetris[][board_Y], Block*& block) {

	delete block;           
	block = new B_O_M_B;   // ����� ��ź ������� ��ü
}

void B_O_M_B_clear(char tetris[][board_Y], Block* block) {   // ��ź ������� ���� ȿ��
	int x = block->posX();    
	int y = block->posY();
	                                                     // ��ź ��� �������� �¿�� 4ĭ��, ���Ʒ��� 4ĭ�� ���Ҹ� ' '�� �ʱ�ȭ
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