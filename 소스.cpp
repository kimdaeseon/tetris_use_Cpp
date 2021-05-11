#include "header.h"
#include "ClientFunc.h"



int main() {

	PlaySound(TEXT("tetris.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);     // TETRIS BGM 재생 (SND_LOOP : 반복재생)
	system("COLOR F0");                       // 콘솔창 색상 조정
	system("mode con lines=28 cols=25");      // 콘솔창 크기 조정
	bool check1 = false;                      // true : 블록이 바닥까지 가서 새블록을 만들어야 함, false : 만들어진 블록이 바닥까지 가지 못함
	bool Continue = true;                     // true : 게임진행 , false : 게임오버
	int num = 100;                            // 블록의 형태를 알려줌 0 ~ 4, 초기값 100
	int Bomb_count = 3;                       // 폭탄아이템 갯수 초기값, 게임에 3번 사용가능
	int score = 0;                            // 줄하나 지울때마다 socore += 100

	srand(time(nullptr));               
	char tetris[board_X][board_Y];            // board_X * board_Y 크기의 2차원 배열, tetris의 보드판을 나타낸다.
	for (int i = 0; i < board_Y; i++) {       
		for (int j = 0; j < board_X; j++) {
			if (i == board_Y-1)
				tetris[j][i] = 127;            // tetris의 마지막 줄은 127로 설정한다. 
			else
				tetris[j][i] = ' ';            // 마지막 줄을 제외 한 모든 줄은 ' '로 설정한다.
		}
	}	
	bool savAble = true;                       // save/load가 연속적으로 이루어지면 안되므로 한번씩만 이루어지게 하는 bool 변수
	bool isBomb = false;                       // isBomb 현재 블록이 폭탄 아이템인지 알려주는 변수, 폭탄 아이템과 일반적인 블록은 바닥에 닿았을때 적용되는 방식이 달라야함
	Block* block;            // 현재 블록
	Block* next;             // 다음 블록
	Block* save;             // 저장되어있는 블록
	num = makeBlock(block, num);  // 초기 현재 블록 생성
	num = makeBlock(save, num);   // 초기 다음 블록 생성
	num = makeBlock(next, num);   // 초기 저장 되어있는 블록 생성
	cv::Mat image = cv::imread("interface.png", cv::IMREAD_COLOR);   // 조작법을 나타내는 interface.png를 읽어옴
	if (image.empty())
		cout << "empty";
	printTetris(tetris, save, next,score, Bomb_count);               // tetris보드 내용 출력
	while (Continue) {
		
		if (check1) {
			delete block;
			if (tetris[board_X/2][0] == 127)      // 게임 오버 조건
			{
				system("cls");
				gotoxy(5, 10);
				cout << "game over\n\n\n\n";
				Continue = false;
				continue;
			}
			block = next;     // 현재 블록을 다음블록으로 바꿈
			num = makeBlock(next, num);  // 다음블록 생성
			printTetris(tetris, save, next, score, Bomb_count);
			check1 = false;
		}
		block->print();    // 블록 출력
		imshow("interface", image); // interface를 나타내는 interface.png 출력
		int key = cv::waitKey(400); // 400ms동안 키입력을 기다림
		block->del();      // 블록 출력 해제
		
		if (key == 'A' || key == 'a') {     // 왼쪽 이동
			if (!check_left(tetris, block))
				block->move_Left();	
		}
		else if (key == 'D' || key == 'd') { // 오른쪽 이동
			if (!check_right(tetris, block))
				block->move_Right();
		}
		else if (key == 'W' || key == 'w') { // 블록 회전
			
			change(tetris, block);
		}
		else if (key == 'Q' || key == 'q') { // 블록 SAVE / LOAD
			if (savAble) {
				save_load_Block(tetris, block, save);
				system("cls");
				printTetris(tetris, save, next, score, Bomb_count);
				savAble = false;
			}
		}
		else if (key == 'S' || key == 's') { // 블록 하강
			while (true) {
				if (!check(tetris, block))
					block->move_down();
				else if (check(tetris, block) && isBomb) {  // 블록이 폭탄일 경우
					B_O_M_B_clear(tetris, block);
					check1 = true;
					savAble = true;
					isBomb = false;
					system("cls");
				}
				else {          // 블록이 일반블록일 경우
					*block + tetris;
					lineClear(tetris, block, score);
					check1 = true;
					savAble = true;
					system("cls");
					break;
				}
			}
		}
		else if (key == 'E' || key == 'e') { // 폭탄 아이템 사용
			if (!isBomb && Bomb_count >= 1) {
				B_O_M_B_C(tetris, block);
				isBomb = true;
				Bomb_count--;
				gotoxy(16, 15);
				cout << "Bomb : " << Bomb_count;
			}
		}
		else {                                
			if(!check(tetris, block))       // 블록이 바닥에 닿지 않으면 아래 이동
				block->move_down();
			else if (check(tetris, block) && isBomb) {  // 블록이 바닥에 닿았는데 블록이 폭탄일경우
				B_O_M_B_clear(tetris, block);
				check1 = true;
				savAble = true;
				isBomb = false;
				system("cls");
			}
			else {                                      // 블록이 바닥에 닿았는데 블록이 일반 블록일 경우
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
