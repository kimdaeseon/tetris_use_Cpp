#include "header.h"
#include "ClientFunc.h"



int main() {

	PlaySound(TEXT("tetris.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);     // TETRIS BGM ��� (SND_LOOP : �ݺ����)
	system("COLOR F0");                       // �ܼ�â ���� ����
	system("mode con lines=28 cols=25");      // �ܼ�â ũ�� ����
	bool check1 = false;                      // true : ����� �ٴڱ��� ���� ������� ������ ��, false : ������� ����� �ٴڱ��� ���� ����
	bool Continue = true;                     // true : �������� , false : ���ӿ���
	int num = 100;                            // ����� ���¸� �˷��� 0 ~ 4, �ʱⰪ 100
	int Bomb_count = 3;                       // ��ź������ ���� �ʱⰪ, ���ӿ� 3�� ��밡��
	int score = 0;                            // ���ϳ� ���ﶧ���� socore += 100

	srand(time(nullptr));               
	char tetris[board_X][board_Y];            // board_X * board_Y ũ���� 2���� �迭, tetris�� �������� ��Ÿ����.
	for (int i = 0; i < board_Y; i++) {       
		for (int j = 0; j < board_X; j++) {
			if (i == board_Y-1)
				tetris[j][i] = 127;            // tetris�� ������ ���� 127�� �����Ѵ�. 
			else
				tetris[j][i] = ' ';            // ������ ���� ���� �� ��� ���� ' '�� �����Ѵ�.
		}
	}	
	bool savAble = true;                       // save/load�� ���������� �̷������ �ȵǹǷ� �ѹ����� �̷������ �ϴ� bool ����
	bool isBomb = false;                       // isBomb ���� ����� ��ź ���������� �˷��ִ� ����, ��ź �����۰� �Ϲ����� ����� �ٴڿ� ������� ����Ǵ� ����� �޶����
	Block* block;            // ���� ���
	Block* next;             // ���� ���
	Block* save;             // ����Ǿ��ִ� ���
	num = makeBlock(block, num);  // �ʱ� ���� ��� ����
	num = makeBlock(save, num);   // �ʱ� ���� ��� ����
	num = makeBlock(next, num);   // �ʱ� ���� �Ǿ��ִ� ��� ����
	cv::Mat image = cv::imread("interface.png", cv::IMREAD_COLOR);   // ���۹��� ��Ÿ���� interface.png�� �о��
	if (image.empty())
		cout << "empty";
	printTetris(tetris, save, next,score, Bomb_count);               // tetris���� ���� ���
	while (Continue) {
		
		if (check1) {
			delete block;
			if (tetris[board_X/2][0] == 127)      // ���� ���� ����
			{
				system("cls");
				gotoxy(5, 10);
				cout << "game over\n\n\n\n";
				Continue = false;
				continue;
			}
			block = next;     // ���� ����� ����������� �ٲ�
			num = makeBlock(next, num);  // ������� ����
			printTetris(tetris, save, next, score, Bomb_count);
			check1 = false;
		}
		block->print();    // ��� ���
		imshow("interface", image); // interface�� ��Ÿ���� interface.png ���
		int key = cv::waitKey(400); // 400ms���� Ű�Է��� ��ٸ�
		block->del();      // ��� ��� ����
		
		if (key == 'A' || key == 'a') {     // ���� �̵�
			if (!check_left(tetris, block))
				block->move_Left();	
		}
		else if (key == 'D' || key == 'd') { // ������ �̵�
			if (!check_right(tetris, block))
				block->move_Right();
		}
		else if (key == 'W' || key == 'w') { // ��� ȸ��
			
			change(tetris, block);
		}
		else if (key == 'Q' || key == 'q') { // ��� SAVE / LOAD
			if (savAble) {
				save_load_Block(tetris, block, save);
				system("cls");
				printTetris(tetris, save, next, score, Bomb_count);
				savAble = false;
			}
		}
		else if (key == 'S' || key == 's') { // ��� �ϰ�
			while (true) {
				if (!check(tetris, block))
					block->move_down();
				else if (check(tetris, block) && isBomb) {  // ����� ��ź�� ���
					B_O_M_B_clear(tetris, block);
					check1 = true;
					savAble = true;
					isBomb = false;
					system("cls");
				}
				else {          // ����� �Ϲݺ���� ���
					*block + tetris;
					lineClear(tetris, block, score);
					check1 = true;
					savAble = true;
					system("cls");
					break;
				}
			}
		}
		else if (key == 'E' || key == 'e') { // ��ź ������ ���
			if (!isBomb && Bomb_count >= 1) {
				B_O_M_B_C(tetris, block);
				isBomb = true;
				Bomb_count--;
				gotoxy(16, 15);
				cout << "Bomb : " << Bomb_count;
			}
		}
		else {                                
			if(!check(tetris, block))       // ����� �ٴڿ� ���� ������ �Ʒ� �̵�
				block->move_down();
			else if (check(tetris, block) && isBomb) {  // ����� �ٴڿ� ��Ҵµ� ����� ��ź�ϰ��
				B_O_M_B_clear(tetris, block);
				check1 = true;
				savAble = true;
				isBomb = false;
				system("cls");
			}
			else {                                      // ����� �ٴڿ� ��Ҵµ� ����� �Ϲ� ����� ���
				*block + tetris;
				lineClear(tetris, block, score);    
				check1 = true;
				savAble = true;
				system("cls");
			}
		}

	}
	
	return 0;
}
