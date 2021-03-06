#pragma once

#define board_X 10
#define board_Y 25

void printTetris(char[][board_Y], Block* block, Block* next, int &score, int &Bomb_count);      // tetris 左球毒 窒径
int makeBlock(Block*& block, int num);         // 鷺系 持失
bool check(char tetris[][board_Y], Block* block);  // 鷺系戚 郊韓拭 願紹澗走 毒舘
bool check_left(char tetris[][board_Y], Block* block);  // 鷺系戚 図楕生稽 戚疑 亜管廃走 毒舘
bool check_right(char tetris[][board_Y], Block* block); // 鷺系戚 神献楕生稽 戚疑 亜管廃走 毒舘
void lineClear(char tetris[][board_Y], Block* block, int &score);  // 廃 匝戚 亜究託檎 匝聖 走酔壱 繊呪 装亜
int CanIChange(char tetris[][board_Y], Block* block);   // 薄仙 鷺系戚 噺穿亜管廃 雌殿昔走 毒舘
void change(char tetris[][board_Y], Block* block);      // 鷺系 噺穿
void save_load_Block(char tetris[][board_Y], Block*& originalblock, Block*& saveBlock);  // 鷺系 煽舌
void B_O_M_B_C(char tetris[][board_Y], Block*& block); // 賑添焼戚奴生稽 鷺系 郊荷奄
void B_O_M_B_clear(char tetris[][board_Y], Block* block);  //賑添焼戚奴 反引 旋遂



void printTetris(char tetris[][board_Y], Block* block, Block* next, int &score, int &Bomb_count) {

	for (int i = 0; i < board_Y - 1; i++) {        // 左球 窒径
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
	gotoxy(2, board_Y + 1);                 // 繊呪 窒径
	cout << "繊呪 : " << score << endl;


	gotoxy(16, 3);
	cout << "-SAVE-";                // SAVE鞠嬢赤澗 鷺系 窒径
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
	cout << "-NEXT-";                // 陥製 鷺系戚 嬢恐 鷺系昔走 窒径
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
	cout << "Bomb : " << Bomb_count;  // 紫遂亜管廃 賑添焼戚奴 姐呪 窒径

}

int makeBlock(Block*& block, int num) {
	int rnd = rand() % 5;

	while (rnd == num) {     // 尻紗生稽 旭精 鷺系戚 蟹神走 省惟 馬奄 是敗
		rnd = rand() % 5;
	}

	switch (rnd) {
	case 0:
		block = new squareBlock;   // けけ
		break;                     // けけ
	case 1:
		block = new BlockType1;    //   け 
		break;                     // けけけ
	case 2:
		block = new BlockType2;    // けけけ
		break;                     //     け
	case 3:
		block = new BlockType3;    // け
		break;                     // けけ 
	case 4:                        //   け

		block = new BlockType4;    //  け
		break;                     //  け
	}                              //  け 
	                               //  け
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
				if (tetris[posX + j][posY + i + 1] == 127) // 鷺系税 焼掘亜 願紹聖凶 true 軒渡
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

	if (block->posX() == 0)  // 鷺系戚 左球研 角嬢亜檎 照鞠糠稽 
		return true;

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			if (block->getform(i,j) == 127) {
				if (tetris[posX + j - 1][posY + i] == 127)   // 鷺系 図楕戚 願紹聖凶 true 軒渡
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

	if (block->posX() + Y == board_X)      // 鷺系戚 左球研 角嬢亜檎 照鞠糠稽
		return true;

	for (int i = 0; i < X; i++) {
		for (int j = Y - 1; j >= 0; j--) {
			if (block->getform(i,j) == 127) {
				if (tetris[posX + j + 1][posY + i] == 127)   // 鷺系税 神献楕戚 願紹聖凶 true軒渡
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
	for (int j = Y; j > 0; j--) {            //郊韓拭 願精 鷺系聖 奄層生稽 鷺系税 株戚幻鏑 tetris 左球研 貼事敗
		for (int i = 0; i < board_X; i++) {
			if (tetris[i][j] == 127) { 
				count++;                      // tetris 左球税 据社亜 127 count ++
			}
			if (count == 10)                  // 廃匝拭 10鯵税 据社亜 赤生糠稽 10鯵税 据社亜 穿採 127析井酔
			{
				IsClear = true;               // IsClear = true;
				Y = j;
				check = true;                 // 廃匝戚虞亀 10鯵税 据社亜 穿採 127井酔 2掻 for庚聖 纏窒馬奄 是廃 bool 痕呪
				break;
			}
		}
		if (check)
			break;
		count = 0;

	}
	if (IsClear) {       // 乞窮 据社亜 127昔 匝戚 糎仙廃陥檎
		for (int i = 0; i < board_X; i++) {
			tetris[i][Y] = ' ';               // 匝 鎧遂 走酔奄
		}
		score += 100;
		check = true;
		for (int i = Y; i > 0; i--) {    // 廃匝梢 焼掘稽 雁奄奄
			for (int j = 0; j < board_X; j++) {
				tetris[j][i] = tetris[j][i - 1];
			}
		}
	}
	if (check)       // 暁陥献 匝戚 赤澗走 溌昔馬奄 是背 敗呪研 陥獣 硲窒
		lineClear(tetris, block, score);

	return;
}

int CanIChange(char tetris[][board_Y], Block* block) {  
	// 鷺系聖 噺穿敗生稽潤 鷺系戚 tetris毒聖 角嬢亜暗蟹 鷺系戚 陥献 鷺系聖 闇級戚澗 井酔研 厳奄是廃 敗呪
	for (int i = 0; i < block->blockSizeY(); i++) {    
		if (tetris[block->posX()][block->posY() + i] == 127)
			return 3;  // 鷺系 焼掘拭 舌蕉弘戚 赤製
	}
	if (block->posX() + block->blockSizeX() > board_X) {
		return 0;       // 鷺系戚 噺穿馬檎 tetris税 神献楕 井域研 角嬢亜澗 井酔
	}
	else {
		for (int i = 0; i < block->blockSizeY(); i++) {
			for (int j = 0; j < block->blockSizeX(); j++) {
				if (tetris[block->posX() + j][block->posY() + i] == 127) {
					return 1;   // 鷺系戚 噺穿馬澗汽拭 赤嬢辞 神献楕拭 舌蕉弘戚 赤澗井酔
				}
			}
		}                     // 鷺系税 是帖 奄層戚 図楕績生稽 神献楕引 焼掘幻 毒舘馬檎 喫
	}

	return 2; // 鷺系戚 噺穿馬食亀 喫
}

void change(char tetris[][board_Y], Block* block) {

	bool count = true;  // 噺穿 食採研 衣舛馬澗 bool 痕呪
	int num = 0; // 護牒 戚疑馬心澗走 煽舌馬澗 痕呪
	switch (CanIChange(tetris, block)) {
	case 0:      // tetris税 神献楕 井域研 角嬢亜澗 井酔
		while (true) {
			if (block->posX() < 0 || check_left(tetris, block)) {   //図楕生稽 戚疑戚 災亜管廃 井酔 噺穿戚 災亜管廃 井酔虞壱 毒舘
				block->setposX(block->posX() + num); // 図楕生稽 戚疑廃幻鏑 陥獣 神献楕生稽 戚疑
				count = false; 
				break;
			}
			if (CanIChange(tetris, block) == 2)
				break;
			block->move_Left();  // 図楕生稽 廃牒梢 戚疑
			num++;   
		}
		if (count)
			block->change();  // 鷺系 噺穿
		break;
	case 1:
		while (true) {   // 鷺系税 神献楕拭 舌蕉弘戚 赤澗 井酔
			if (block->posX() < 0 || check_left(tetris, block)) {  // case 0引 引舛精 疑析敗
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
	case 2:   // 噺穿戚 亜管廃井酔
		block->change();
		break;
	case 3:   // 郊韓戚 舌蕉弘戚 鞠澗井酔澗 噺穿 災亜管
		break;
	}
	return;
}

void save_load_Block(char tetris[][board_Y], Block*& originalblock, Block*& saveBlock) {
		Block* temp = originalblock;  // originalblock引 saveblock 嘘端
		originalblock = saveBlock;
		saveBlock = temp;
		saveBlock->init_pos(); // 郊駕 鷺系精 是帖舛左研 亜走壱 赤生糠稽 段奄葵生稽 段奄鉢
}

void B_O_M_B_C(char tetris[][board_Y], Block*& block) {

	delete block;           
	block = new B_O_M_B;   // 鷺系聖 賑添 鷺系生稽 嘘端
}

void B_O_M_B_clear(char tetris[][board_Y], Block* block) {   // 賑添 鷺系生稽 昔廃 反引
	int x = block->posX();    
	int y = block->posY();
	                                                     // 賑添 鷺系 奄層生稽 疎酔稽 4牒梢, 是焼掘稽 4牒梢 据社研 ' '稽 段奄鉢
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