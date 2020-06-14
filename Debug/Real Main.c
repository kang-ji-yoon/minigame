#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#pragma warning(disable:4996)
#define WIDTH 80
#define HEIGHT 40
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
#define FUNCTION_KEY -32
#define c_black 0
#define c_blue 1
#define c_green 2
#define c_cyan 3
#define c_red 4
#define c_purple 5
#define c_yellow 6
#define c_white 7
#define c_gray 8
#define cc_blue 9
#define cc_green 10
#define cc_cyan 11
#define cc_red 12
#define cc_purple 13
#define cc_yellow 14
#define cc_white 15
#define ESC 27
#define ENTER 13
#define MAZE_SIZE_X 18
#define MAZE_SIZE_Y 34
#define A 65
#define S 83
#define D 68
#define W 87
#define J 74
#define K 75
#define L 76
#define I 73
#define MCI_DGV_PLAY_REPEAT 0x00010000L

#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "Digitalv.h"
int dwID;
MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

char gm[20][50] = { "", "하노이 탑", "미로 찾기", "러브 찬스", "신호등 달리기", "색칠 놀이", "도둑이야", "별똥별이다", "등짝을 보자", "이긴 사람", "???", "???", "???", "???", "???", "???", "???","???", "???" };
char order[9] = { 'Z', 'X', 'C', 'V', 'B', 'N', 'M', 'F', 'G' };
int selme = 0;
int dir1 = -1, dir2 = -1;
int total1 = 0, total2 = 0;

/*
이 게임은 주로 게임 함수, 메뉴 함수, 기타 수행 함수로 구성되어 있다.
메뉴 함수에서 선택을 하면 여러 미니 게임을 고를 수 있고
게임 함수에서 각기 다른 미니 게임을 실행하며
수행 함수에서는 입력 처리, 화면 출력, 등등의 보조 역할을 한다.

총 게임 함수는 9개이고, 미니 게임 갯수도 총 9개이다.
*/

typedef struct {
	int posx, posy;
}chrpos;

void cls() { 
	system("cls");
} 
//화면 지우는 함수

HWND getConsoleWindowHandle() {
	WCHAR title[2048] = { 0 };
	GetConsoleTitle(title, 2048);
	HWND hWnd = FindWindow(NULL, title);
	SetConsoleTitle(title);
	return hWnd;
}

int GetDPI(HWND hWnd) {
	HANDLE user32 = GetModuleHandle(TEXT("user32"));
	FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
	if (func == NULL) return 96;
	return((UINT(__stdcall *)(HWND))func)(hWnd);
}
//DPI 얻어오기 (이미지 출력)

void GetBMP(HDC hdc, HDC memdc, HBITMAP image) {
	BITMAP bitmap;
	HDC bitmapDC = CreateCompatibleDC(hdc);
	GetObject(image, sizeof(bitmap), &bitmap);
	SelectObject(bitmapDC, image);
	BitBlt(memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, bitmapDC, 0, 0, SRCCOPY);
	DeleteDC(bitmapDC);
}
//BMP 얻어오기 (이미지 출력)

void paint(HWND hWnd, int dpi, HBITMAP image, int sizex, int sizey) {
	HDC hdc = GetDC(hWnd);
	HDC memdc = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, sizex, sizey);
	SelectObject(memdc, bitmap);
	GetBMP(hdc, memdc, image);
	StretchBlt(hdc, 0, 0, sizex, sizey, memdc, 0, 0, sizex, sizey, SRCCOPY);
	DeleteDC(memdc);
	DeleteObject(bitmap);
	ReleaseDC(hWnd, hdc);
}
//이미지 그려내기

void StopAllSounds(int dwID) {
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	PlaySound(NULL, 0, 0);
}
//소리 정지 함수

void Opening() {
	mciOpen.lpstrElementName = "Glacia1.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	dwID = mciOpen.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	system("color 0f");
	cls();
	Sleep(972);
	system("color 7f");
	Sleep(324);
	char open1[100], open2[100], open3[100], open4[100], open5[100];
	int dpi;
	HBITMAP o1, o2, o3, o4, o5;
	HWND hWnd = getConsoleWindowHandle();
	dpi = GetDPI(hWnd);
	sprintf(open1, "Open1.bmp");
	sprintf(open2, "Open2.bmp");
	sprintf(open3, "Open3.bmp");
	sprintf(open4, "Open4.bmp");
	sprintf(open5, "Open5.bmp");
	o1 = (HBITMAP)LoadImage(NULL, open1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o2 = (HBITMAP)LoadImage(NULL, open2, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o3 = (HBITMAP)LoadImage(NULL, open3, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o4 = (HBITMAP)LoadImage(NULL, open4, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	o5 = (HBITMAP)LoadImage(NULL, open5, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	paint(hWnd, dpi, o1, 800, 800);
	Sleep(2508);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o2, 800, 800);
	Sleep(2450);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o3, 800, 800);
	Sleep(2450);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o4, 800, 800);
	Sleep(2450);
	cls();
	Sleep(85);
	paint(hWnd, dpi, o5, 800, 800);
	Sleep(2240);
	cls();
	Sleep(325);
	system("color 0f");
}
//오프닝 함수

void Console() {
	char chtemp[50];
	sprintf(chtemp, "mode con cols=%d lines=%d", WIDTH, HEIGHT);
	system(chtemp);
	system("title Minigames Heaven");
}
//콘솔 조정 함수

void tc(int a) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
//문자 색깔 지정

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//커서 이동 함수

void print_score(int sc1, int sc2) {
	gotoxy(32, 37);
	tc(c_white);
	printf("%4d", sc1);
	gotoxy(44, 37);
	printf("%4d", sc2);
}
//점수 출력 함수

void normalbound(int a) {
	gotoxy(0, 0);
	int x, y;
	tc(a);
	for (x = 0; x < WIDTH; x += 2) {
		for (y = 0; y < HEIGHT; y++) {
			if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 2) {
				gotoxy(x, y);
				printf("■");
			}
		}
	}
}
//윤곽 출력 함수

void halfbound(int a, int type) {
	int i;
	tc(a);
	switch (type) {
	case 0: 
		for (i = 1; i <= 38; i++) {
			if (i != 35) {
				gotoxy(39, i);
				printf("||");
			}
		}
		break;
	case 1:
		for (i = 1; i <= 38; i++) {
			if (i != 35) {
				gotoxy(38, i);
				printf("■■");
			}
		}
		break;
	case 2:
		for (i = 36; i <= 38; i++) {
				gotoxy(39, i);
				printf("||");
		}
		break;
	case 3:
		gotoxy(2, 18);
		for (i = 0; i < 38; i++) printf("■");
		for (i = 36; i <= 38; i++) {
			gotoxy(39, i);
			printf("||");
		}
		break;
	default: break;
	}
	gotoxy(2, 35);
	printf("============================================================================");
}
//내부 선 출력 함수

void border(int y) {
	gotoxy(2, y);
	for (int i = 0; i < 38; i++) printf("〓");
}
//경계선 출력 함수

void clearCursor() {
	CONSOLE_CURSOR_INFO c = { 0 };
	c.dwSize = 1;
	c.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c);
}
//커서 삭제 함수

void BGM() {
	mciOpen.lpstrElementName = "Glacia1.mp3";
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	dwID = mciOpen.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	//MCI_NOTIFY: 기본, MCI_DGV_PLAY_REPEAT: 반복
	//mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms);     // Pause
	//mciSendCommandW(dwID, MCI_RESUME, 0, NULL);       // resume
	//mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);        // stop
}
//BGM 제어 함수

void mt_start(int a) {
	int i;
	tc(a);
	gotoxy(24, 22);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 23; i <= 25; i++) {
		gotoxy(24, i);
		printf("┃");
		gotoxy(54, i);
		printf("┃");
	}
	gotoxy(24, 26);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(36, 24);
	printf("시    작");
}
//시작 버튼 출력

void mt_quit(int a) {
	int i;
	tc(a);
	gotoxy(24, 29);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 30; i <= 32; i++) {
		gotoxy(24, i);
		printf("┃");
		gotoxy(54, i);
		printf("┃");
	}
	gotoxy(24, 33);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(36, 31);
	printf("종    료");
}
//나가기 버튼 출력

void sm_np(int a) {
	int i;
	tc(a);
	gotoxy(8, 4);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 5; i <= 33; i++) {
		gotoxy(8, i);
		printf("┃");
		gotoxy(30, i);
		printf("┃");
	}
	gotoxy(8, 34);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(16, 7);
	printf("노    멀");
}
//노멀 모드 출력

void sm_sp(int a) {
	int i;
	tc(a);
	gotoxy(48, 4);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	for (i = 5; i <= 33; i++) {
		gotoxy(48, i);
		printf("┃");
		gotoxy(70, i);
		printf("┃");
	}
	gotoxy(48, 34);
	printf("〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(56, 7);
	printf("선    택");
}
//선택 모드 출력

void maintitle(int selcheck) {
	char ch = 0;
	if (selcheck % 2) mt_start(cc_red);
	else mt_start(c_white);
	if (selcheck - 1 && selcheck > 0) mt_quit(cc_red);
	else mt_quit(c_white);
	gotoxy(53, 36);
	if (selcheck == 0) {
		tc(c_white);
		printf("※ ↑, ↓키로 이동합니다.");
		gotoxy(47, 38);
		printf("※ ENTER키로 항목을 선택합니다.");
	}
	tc(c_white);

	char filename[100];
	int dpi;
	HBITMAP bitmap;
	HWND hWnd = getConsoleWindowHandle();
	dpi = GetDPI(hWnd);
	sprintf(filename, "Title.bmp");
	bitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	paint(hWnd, dpi, bitmap, 800, 440);
	if (!selcheck) Sleep(800);
	if (selcheck) PlaySound(TEXT("tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch == FUNCTION_KEY) {
				ch = getch();
				if (ch == UP) {
					maintitle(1);
					return;
				}
				else if (ch == DOWN) {
					maintitle(2);
					return;
				}
			}
			else if (ch == ENTER) break;
		}
	}
	if (selcheck == 0) {
		maintitle(0);
		return;
	}
	if (selcheck == 2) {
		cls();
		exit(0);
	}
}
//메인 화면 출력 함수

void winner(int a, int b) {
	tc(cc_yellow);
	int win[4][7] = { {1,0,1,0,1,0,1}, {1,1,0,1,0,1,1}, {1,0,0,0,0,0,1}, {1,1,1,1,1,1,1} };
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 4; y++) {
			if (win[y][x]) {
				gotoxy(x * 2 + a, y + b);
				printf("■");
			}
			else {
				gotoxy(x * 2 + a, y + b);
				printf("  ");
			}
		}
	}
}
//승자 왕관 출력

void print_halfmoon(int a, int b) {
	int hm[5][10] = {
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0},
	{0,1,0,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1} };
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 5; y++) {
			if (hm[y][x]) {
				gotoxy(x * 2 + a, y + b);
				printf("■");
			}
			else {
				gotoxy(x * 2 + a, y + b);
				printf("  ");
			}
		}
	}
}
//사람 얼굴 출력

void print_Heart(int a) {
	int i, j;
	int heart[9][12] = {
	{2,2,1,1,2,2,2,2,1,1,2,2},
	{2,1,0,0,1,2,2,1,0,0,1,2},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,1},
	{2,1,0,0,0,0,0,0,1,0,1,2},
	{2,2,1,0,0,0,0,1,0,1,2,2},
	{2,2,2,1,0,0,0,0,1,2,2,2},
	{2,2,2,2,1,0,0,1,2,2,2,2},
	{2,2,2,2,2,1,1,2,2,2,2,2} };
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 9; j++) {
			gotoxy(2 * i + (28 - 24 * (a == 2) + 24 * (a == 3)), 11 - 8 * (!a) + 8 * (a == 1) + j);
			if (heart[j][i] == 1) {
				tc(c_red);
				printf("■");
			}
			else if (!heart[j][i]) {
				tc(cc_red);
				printf("■");
			}
			else printf("  ");
		}
	}
}
//하트 출력

void remove_Heart(int a) {
	int i, j;
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 9; j++) {
			gotoxy(2 * i + (28 - 24 * (a == 2) + 24 * (a == 3)), 11 - 8 * (!a) + 8 * (a == 1) + j);
		    printf("  ");
		}
	}
}
//하트 삭제

void p1_win() {
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("win.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(4, 37);
	tc(cc_yellow);
	printf("★ You Win! Please Wait...");
	gotoxy(62, 37);
	tc(cc_red);
	printf("☆ You Lose...");
	total1++;
}
//1P 승

void p2_win() {
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("win.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(50, 37);
	tc(cc_yellow);
	printf("★ You Win! Please Wait...");
	gotoxy(4, 37);
	tc(cc_red);
	printf("☆ You Lose...");
	total2++;
}
//2P 승

void tie() {
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	PlaySound(TEXT("tie.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(4, 37);
	tc(cc_green);
	printf("☆ Well done!!");
	gotoxy(62, 37);
	printf("☆ Well done!!");
}
//비김

int check_snake(chrpos* snake, chrpos* snake2, int len) {
	int i;
	if (snake[0].posx < 0 || snake[0].posy < 0 || snake[0].posx > 37 || snake[0].posy > 33)
		return 1;
	for (i = 1; i < len-1; i++) {
		if (snake[0].posx == snake[i].posx && snake[0].posy == snake[i].posy) 
			return 1;
		if (snake[0].posx == snake2[i].posx && snake[0].posy == snake2[i].posy)
			return 1;
	}
	return 0;
}
//뱀 충돌 확인

void move_snake(chrpos* p1_snake, chrpos* p2_snake, int len1, int len2) {
	int i, j;
	{
		if (GetAsyncKeyState(W) & 0x8000) dir1 = 0;
		if (GetAsyncKeyState(S) & 0x8000) dir1 = 1;
		if (GetAsyncKeyState(A) & 0x8000) dir1 = 2;
		if (GetAsyncKeyState(D) & 0x8000) dir1 = 3;
		if (GetAsyncKeyState(I) & 0x8000) dir2 = 0;
		if (GetAsyncKeyState(K) & 0x8000) dir2 = 1;
		if (GetAsyncKeyState(J) & 0x8000) dir2 = 2;
		if (GetAsyncKeyState(L) & 0x8000) dir2 = 3;
	}
	if (dir1 != -1) {
		int i;
		gotoxy(2 * p1_snake[len1 - 1].posx + 2, p1_snake[len1 - 1].posy + 1);
		printf("  ");
		for (i = len1 - 1; i > 0; i--) p1_snake[i] = p1_snake[i - 1];
		gotoxy(2 * p1_snake[1].posx + 2, p1_snake[1].posy + 1);
		tc(cc_cyan);
		printf("◎");
	}
	switch (dir1) {
	case 0: p1_snake[0].posy--; break;
	case 1: p1_snake[0].posy++; break;
	case 2: p1_snake[0].posx--; break;
	case 3: p1_snake[0].posx++; break;
	}
	gotoxy(2 * p1_snake[0].posx + 2, p1_snake[0].posy + 1);
	tc(cc_cyan);
	printf("●");
	if (dir2 != -1) {
		int i;
		gotoxy(2 * p2_snake[len2 - 1].posx + 2, p2_snake[len2 - 1].posy + 1);
		printf("  ");
		for (i = len2 - 1; i > 0; i--) p2_snake[i] = p2_snake[i - 1];
		gotoxy(2 * p2_snake[1].posx + 2, p2_snake[1].posy + 1);
		tc(cc_yellow);
		printf("◎");
	}
	switch (dir2) {
	case 0: p2_snake[0].posy--; break;
	case 1: p2_snake[0].posy++; break;
	case 2: p2_snake[0].posx--; break;
	case 3: p2_snake[0].posx++; break;
	}
	gotoxy(2 * p2_snake[0].posx + 2, p2_snake[0].posy + 1);
	tc(cc_yellow);
	printf("●");
}
//뱀 이동

void print_bike(int x, int y, int c) {
	int i, j;
	int bike[10][12] = {
	{0,0,0,0,-1,-1,0,0,1,0,0,0},
	{0,0,0,0,-1,-1,0,0,0,1,0,0},
	{0,0,0,1,1,1,1,0,1,0,1,0},
	{0,0,0,0,1,0,2,2,0,1,0,0},
	{0,0,0,0,2,2,0,2,2,1,0,0},
	{0,0,0,2,0,2,2,0,0,2,0,0},
	{0,0,2,0,0,2,0,0,0,2,0,0},
	{1,1,1,0,0,1,0,0,0,1,1,1},
	{1,0,1,0,0,1,1,0,0,1,0,1},
	{1,1,1,0,0,0,0,0,0,1,1,1} };
	tc(c_white);
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 10; j++) {
			if (bike[j][i] == 1) {
				gotoxy(2 * i + x, j + y);
				printf("■");
			}
		}
	}
	tc(cc_blue);
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 10; j++) {
			if (bike[j][i] == 2) {
				gotoxy(2 * i + x, j + y);
				printf("■");
			}
		}
	}
	if (c == cc_blue) tc(cc_cyan);
	else tc(cc_red);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 2; j++) {
			if (bike[j][i] == -1) {
				gotoxy(2 * i + x, j + y);
				printf("▣");
			}
		}
	}
}
//자전거 이동 함수

void print_line(int y, int* line, int move) { // 9, line1, 0
	int i;
	tc(cc_yellow);
	for (i = 0; i < 35; i++) {
		if (*(line+i)) {
			if (i != 4 && i != 5 && i != 7 && i != 8 && i != 9) {
				gotoxy(6 + 2 * i, y);
				printf("■");
			}
			if (i != 3 && i != 5 && i != 6 && i != 9) {
				gotoxy(6 + 2 * i, y + 1);
				printf("■");
			}
		}
		else {
			if (i != 4 && i != 5 && i != 7 && i != 8 && i != 9) {
				gotoxy(6 + 2 * i, y);
				printf("  ");
			}
			if (i != 3 && i != 5 && i != 6 && i != 9) {
				gotoxy(6 + 2 * i, y + 1);
				printf("  ");
			}
		}
	}
	if (!(move % 20)) {
		print_bike(6, 5, cc_blue);
		print_bike(6, 22, cc_red);
		*(line + 35) = *(line + 0);
		for (i = 1; i <= 35; i++) *(line + (i - 1)) = *(line + i);
	}
}
//선 출력

void print_hand(int x, int y, int rd) {
	int i, j;
	int h0[14][11] = {
		{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,1,0,1,0,1,0,1,0 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 0,1,2,2,2,2,2,2,2,1,0 },
	{ 0,0,1,1,1,1,1,1,1,0,0 } };
	int h2[14][11] = {
		{ 0,1,0,1,0,0,0,0,0,0,0 },
	{ 1,2,1,2,1,0,0,0,0,0,0 },
	{ 1,2,1,2,1,0,0,0,0,0,0 },
	{ 1,2,1,2,1,0,0,0,0,0,0 },
	{ 1,2,1,2,1,1,0,1,0,1,0 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 0,1,2,2,2,2,2,2,2,1,0 },
	{ 0,0,1,1,1,1,1,1,1,0,0 } };
	int h5[14][11] = {
		{ 0,1,0,1,0,1,0,1,0,1,0 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,1,2,1,2,1,2,1,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 1,2,2,2,2,2,2,2,2,2,1 },
	{ 0,1,2,2,2,2,2,2,2,1,0 },
	{ 0,0,1,1,1,1,1,1,1,0,0 } };
	for (i = 0; i < 11; i++) {
		for (j = 0; j < 14; j++) {
			gotoxy(2 * i + x, j + y);
			printf("  ");
		}
	}
	switch (rd) {
	case 0:
		if (y <= 18) tc(cc_blue);
		else tc(cc_red);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h0[j][i] == 1) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
				if (h0[j][i] == 0) {
					gotoxy(2 * i + x, j + y);
					printf("  ");
				}
			}
		}
		/*tc(cc_white);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h0[j][i] == 2) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
			}
		}*/
		break;
	case 1:
		if (y <= 18) tc(cc_blue);
		else tc(cc_red);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h2[j][i] == 1) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
				if (h2[j][i] == 0) {
					gotoxy(2 * i + x, j + y);
					printf("  ");
				}
			}
		}
		/*tc(cc_white);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h2[j][i] == 2) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
			}
		}*/
		break;
	case 2:
		if (y <= 18) tc(cc_blue);
		else tc(cc_red);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h5[j][i] == 1) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
				if (h5[j][i] == 0) {
					gotoxy(2 * i + x, j + y);
					printf("  ");
				}
			}
		}
		/*tc(cc_white);
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 14; j++) {
				if (h5[j][i] == 2) {
					gotoxy(2 * i + x, j + y);
					printf("■");
				}
			}
		}*/
		break;
	}
}
//손 출력 함수

/*여기서부터 게임 함수*/
void click_n1() {
	cls();
	int i, j, sc1=0, sc2=0;
	{
		normalbound(c_gray);
		halfbound(c_gray, 0);
		for (i = 2; i <= 33; i++) {
			tc(c_white);
			gotoxy(18, i);
			printf("■■");
			gotoxy(58, i);
			printf("■■");
		}
	}
	while (sc1 < 40 && sc2 < 40) {
		if (sc1 >= 5 && !(sc1 % 5)) {
			switch (sc1 / 5) {
			case 1: tc(cc_purple); break;
			case 2: tc(cc_blue); break;
			case 3: tc(cc_cyan); break;
			case 4: tc(c_green); break;
			case 5: tc(cc_green); break;
			case 6: tc(cc_yellow); break;
			case 7: tc(cc_red); break;
			default: break;
			}
			for (i = 0; i < 18 - 2 * (sc1 / 5); i++) {
				for (j = 0; j < 3; j++) {
					if (!(j == 1 && i >= 8 - (sc1 / 5) && i <= 9 - (sc1 / 5))) {
						gotoxy(2 * (i + sc1 / 5) + 2, j + 35 - 4 * (sc1 / 5));
						printf("■");
					}
				}
			}
		}
		if (sc2 >= 5 && !(sc2 % 5)) {
			switch (sc2 / 5) {
			case 1: tc(cc_purple); break;
			case 2: tc(cc_blue); break;
			case 3: tc(cc_cyan); break;
			case 4: tc(c_green); break;
			case 5: tc(cc_green); break;
			case 6: tc(cc_yellow); break;
			case 7: tc(cc_red); break;
			default: break;
			}
			for (i = 0; i < 18 - 2 * (sc2 / 5); i++) {
				for (j = 0; j < 3; j++) {
					if (!(j == 1 && i >= 8 - (sc2 / 5) && i <= 9 - (sc2 / 5))) {
						gotoxy(2 * (i + sc2 / 5) + 42, j + 35 - 4 * (sc2 / 5));
						printf("■");
					}
				}
			}
		}
		print_score(sc1, sc2);
		if (GetAsyncKeyState(A) & 0x8000) {
			Sleep(40);
			if (!(GetAsyncKeyState(A) & 0x8001)) sc1++;
		}
		if (GetAsyncKeyState(J) & 0x8000) {
			Sleep(40);
			if (!(GetAsyncKeyState(J) & 0x8001)) sc2++;
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		winner(4, 2);
		p1_win();
	}
	else if (sc2 > sc1) {
		winner(62, 2);
		p2_win();
	}
	else tie();
	Sleep(3000);
}
//edit 

void maze_n2() {
	cls();
	int i, j, x = 0, y = 0, rt;
	chrpos p1 = { 0,0 };
	chrpos p2 = { 0,0 };
	int map[MAZE_SIZE_Y][MAZE_SIZE_X] = { 0 };
	{
		normalbound(c_gray);
		halfbound(c_gray, 1);
		map[x][y] = 1;
		for (i = 0; i < 10000; i++) {
			rt = rand() % 4 + 1;
			if (rt == 1) {
				if (y == 0) continue;
				if (map[y-2][x] == 0) {
					map[--y][x] = 1;
					map[--y][x] = 1;
				}
				else y -= 2;
			}
			if (rt == 2) {
				if (x == MAZE_SIZE_X - 2) continue;
				if (map[y][x+2] == 0) {
					map[y][++x] = 1;
					map[y][++x] = 1;
				}
				else x += 2;
			}
			if (rt == 3) {
				if (y == MAZE_SIZE_Y - 2) continue;
				if (map[y+2][x] == 0) {
					map[++y][x] = 1;
					map[++y][x] = 1;
				}
				else y += 2;
			}
			if (rt == 4) {
				if (x == 0) continue;
				if (map[y][x-2] == 0) {
					map[y][--x] = 1;
					map[y][--x] = 1;
				}
				else x -= 2;
			}
		}
		map[MAZE_SIZE_Y - 2][MAZE_SIZE_X - 1] = 1;
		tc(c_white);
		for (i = 0; i < MAZE_SIZE_X; i++) {
			for (j = 0; j < MAZE_SIZE_Y; j++) {
				if (!map[j][i]) {
					gotoxy(2 * i + 2, j + 1);
					printf("■");
					gotoxy(2 * i + 42, j + 1);
					printf("■");
				}
			}
		}
		tc(cc_yellow);
		gotoxy(36, 33);
		printf("☞");
		gotoxy(76, 33);
		printf("☞");
	}
	Sleep(1000);
	while (1) {
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_cyan);
		printf("◈");
		gotoxy(2 * p2.posx + 42, p2.posy + 1);
		tc(cc_red);
		printf("◈");
		Sleep(150);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			if (map[p1.posy][p1.posx - 1]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx--;
			}
		}
		if (GetAsyncKeyState(D) && p1.posx < MAZE_SIZE_X - 1) {
			if (map[p1.posy][p1.posx + 1]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx++;
			}
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			if (map[p1.posy - 1][p1.posx]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy--;
			}
		}
		if (GetAsyncKeyState(S) && p1.posy < MAZE_SIZE_Y - 1) {
			if (map[p1.posy + 1][p1.posx]) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy++;
			}
		}
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			if (map[p2.posy][p2.posx - 1]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posx--;
			}
		}
		if (GetAsyncKeyState(L) && p2.posx < MAZE_SIZE_X - 1) {
			if (map[p2.posy][p2.posx + 1]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posx++;
			}
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			if (map[p2.posy - 1][p2.posx]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posy--;
			}
		}
		if (GetAsyncKeyState(K) && p2.posy < MAZE_SIZE_Y - 1) {
			if (map[p2.posy + 1][p2.posx]) {
				gotoxy(2 * p2.posx + 42, p2.posy + 1);
				printf("  ");
				p2.posy++;
			}
		}
		if ((p1.posx == MAZE_SIZE_X - 1 && p1.posy == MAZE_SIZE_Y - 2) || (p2.posx == MAZE_SIZE_X - 1 && p2.posy == MAZE_SIZE_Y - 2))  break;
	}
	if (p1.posx == MAZE_SIZE_X - 1 && p1.posy == MAZE_SIZE_Y - 2) {
		if (p2.posx == MAZE_SIZE_X - 1 && p2.posy == MAZE_SIZE_Y - 2) tie();
		else {
			for (i = 12; i < 30; i++) {
				for (j = 15; j < 21; j++) {
					gotoxy(i, j);
					printf("  ");
				}
			}
			winner(14, 16);
			p1_win();
		}
	}
	else if (p2.posx == MAZE_SIZE_X - 1 && p2.posy == MAZE_SIZE_Y - 2) {
		for (i = 52; i < 70; i++) {
			for (j = 15; j < 21; j++) {
				gotoxy(i, j);
				printf("  ");
			}
		}
		winner(54, 16);
		p2_win();
	}	
	Sleep(3000);
}

void heart_n3() {
	cls();
	int i, rd, sc1 = 0, sc2 = 0, print_c = 0;
	char ch;
	normalbound(c_gray);
	halfbound(c_gray, 2);
	tc(c_white);
	print_halfmoon(10, 30);
	print_halfmoon(50, 30);
	clock_t start = clock();
	while (print_c <= 40) {
		float tt;
		print_score(sc1, sc2);
		rd = rand() % 4;
		print_Heart(rd);
		print_c++;
		if (print_c <= 10) tt = 1.5;
		else if (print_c <= 20) tt = 1.0;
		else if (print_c <= 30) tt = 0.7;
		else tt = 0.4;
		start = clock();
		while (1) {
			if (rd == 0) {
				if (GetAsyncKeyState(W) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(W) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(I) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(I) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if (rd == 1) {
				if (GetAsyncKeyState(S) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(S) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(K) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(K) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if (rd == 2) {
				if (GetAsyncKeyState(A) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(A) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(J) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(J) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if (rd == 3) {
				if (GetAsyncKeyState(D) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(D) & 0x8001)) {
						sc1++;
						start = clock();
						break;
					}
				}
				if (GetAsyncKeyState(L) & 0x8000) {
					Sleep(40);
					if (!(GetAsyncKeyState(L) & 0x8001)) {
						sc2++;
						start = clock();
						break;
					}
				}
			}
			if ((clock() - start) / CLOCKS_PER_SEC > (float)tt) break;
		}
		remove_Heart(rd);
		Sleep(200);
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		winner(16, 24);
		p1_win();
	}
	else if (sc2 > sc1) {
		winner(50, 24);
		p2_win();
	}
	else tie();
	Sleep(3000);
}

void run_n4() {
	cls();
	int i, j, rd, sc1 = 0, sc2 = 0;
	clock_t start = clock();
	int line1[36] = { 1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1 };
	int line2[36] = { 1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1 };
	normalbound(c_gray);
	halfbound(c_white, 3);
	tc(c_white);
	border(3);
	border(16);
	border(20);
	border(33);
	print_line(9, line1, 0);
	print_line(26, line2, 0);
	print_bike(6, 5, cc_blue);
	print_bike(6, 22, cc_red);
	tc(c_white);
	gotoxy(16, 17);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(16, 19);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	tc(c_black);
	gotoxy(18, 18);
	printf("■■■■■■■■■■■■■■■■■■■■■■");
	while (sc1 <= 1999 && sc2 <= 1999) {
		tc(cc_green);
		gotoxy(18, 18);
		printf("■■■■■■■■■■■■■■■■■■■■■■");
		start = clock();
		rd = rand() % 10 + 3;
		while (sc1 <= 1999 && sc2 <= 1999) {
			if (GetAsyncKeyState(D) & 0x8001) {
				sc1++;
				print_line(9, line1, sc1);
			}
			if (GetAsyncKeyState(L) & 0x8001) {
				sc2++;
				print_line(26, line2, sc2);
			}
			if ((clock() - start) / CLOCKS_PER_SEC > (float)rd) break;
			print_score(sc1, sc2);
		}
		tc(cc_red);
		gotoxy(18, 18);
		printf("■■■■■■■■■■■■■■■■■■■■■■");
		start = clock();
		rd = rand() % 5 + 2;
		while (sc1 <= 1999 && sc2 <= 1999) {
			if ((GetAsyncKeyState(D) & 0x8001) && sc1 > 0) {
				sc1--;
				Sleep(15);
			}
			if ((GetAsyncKeyState(L) & 0x8001) && sc2 > 0) {
				sc2--;
				Sleep(15);
			}
			if ((clock() - start) / CLOCKS_PER_SEC > (float)rd) break;
			print_score(sc1, sc2);
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		winner(62, 4);
		p1_win();
	}
	else if (sc2 > sc1) {
		winner(62, 21);
		p2_win();
	}
	else tie();
	Sleep(3000);
}

void color_n5() {
	int i, j, game = 2000; //100=1초;
	int map[34][38] = { 0 };
	cls();
	normalbound(c_gray);
	halfbound(c_gray, 2);
	chrpos p1 = { 0,18 };
	chrpos p2 = { 37,18 };
	map[18][0] = 1;
	map[18][37] = 2;
	while (game) {
		int map1 = 0, map2 = 0;
		for (i = 0; i < 38; i++) {
			for (j = 0; j < 34; j++) {
				if (map[j][i] == 1) map1++;
				if (map[j][i] == 2) map2++;
			}
		}
		print_score(map1, map2);
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_blue);
		printf("★");
		gotoxy(2 * p2.posx + 2, p2.posy + 1);
		tc(cc_red);
		printf("★");
		Sleep(20);
		tc(cc_yellow);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			if (p1.posx - 1 != p2.posx || p1.posy != p2.posy) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(D) && p1.posx < 37) {
			if (p1.posx + 1 != p2.posx || p1.posy != p2.posy) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posx++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			if (p1.posy - 1 != p2.posy || p1.posx != p2.posx) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(S) && p1.posy < 33) {
			if (p1.posy + 1 != p2.posy || p1.posx != p2.posx) {
				gotoxy(2 * p1.posx + 2, p1.posy + 1);
				printf("  ");
				p1.posy++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p1.posy + j >= 0 && p1.posx + i >= 0 && p1.posy + j <= 33 && p1.posx + i <= 37) {
						if ((p1.posy + j != p2.posy) || (p1.posx + i != p2.posx)) {
							map[p1.posy + j][p1.posx + i] = 1;
							gotoxy(2 * (p1.posx + i) + 2, p1.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		tc(cc_green);
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			if (p2.posx - 1 != p1.posx || p1.posy != p2.posy) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posx--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(L) && p2.posx < 37) {
			if (p2.posx + 1 != p1.posx || p1.posy != p2.posy) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posx++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			if (p2.posy - 1 != p1.posy || p1.posx != p2.posx) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posy--;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(K) && p2.posy < 33) {
			if (p2.posy + 1 != p1.posy || p1.posx != p2.posx) {
				gotoxy(2 * p2.posx + 2, p2.posy + 1);
				printf("  ");
				p2.posy++;
				for (i = -1; i <= 1; i++) for (j = -1; j <= 1; j++) {
					if (p2.posy + j >= 0 && p2.posx + i >= 0 && p2.posy + j <= 33 && p2.posx + i <= 37) {
						if ((p2.posy + j != p1.posy) || (p2.posx + i != p1.posx)) {
							map[p2.posy + j][p2.posx + i] = 2;
							gotoxy(2 * (p2.posx + i) + 2, p2.posy + j + 1);
							printf("■");
						}
					}
				}
			}
		}
		game -= 2;
		if (game >= 1000) tc(cc_cyan);
		else tc(cc_red);
		gotoxy(72, 37);
		printf("%4d", game);
	}
	int m1 = 0, m2 = 0;
	for (i = 0; i < 38; i++) {
		for (j = 0; j < 34; j++) {
			if (map[j][i] == 1) m1++;
			if (map[j][i] == 2) m2++;
		}
	}
	gotoxy(72, 37);
	printf("    ");
	if (m1 > m2) {
		p1_win();
		tc(cc_yellow);
	}
	else if (m1 < m2) tc(cc_red);
	else tc(cc_cyan);
	gotoxy(32, 37);
	printf("    ");
	gotoxy(32, 37);
	printf("%4d", m1);
	if (m1 < m2) {
		p2_win();
		tc(cc_yellow);
	}
	else if (m1 > m2) tc(cc_red);
	else {
		tie();
		tc(cc_cyan);
	}
	gotoxy(44, 37);
	printf("    ");
	gotoxy(44, 37);
	printf("%d", m2);
	Sleep(3000);
}

void thief_n6() {
	cls();
	int map[34][38] = { 0 };
	chrpos p1 = { 0,16 };
	chrpos p2 = { 37,16 };
	int sc1 = 0, sc2 = 0;
	int rd, i, j;
	for (i = 3; i <= 34; i++) {
		for (j = 3; j <= 30; j++) {
			rd = rand() % 3;
			if (!rd) map[j][i] = 1;
		}
	}
	normalbound(c_gray);
	halfbound(c_gray, 2);
	for (i = 0; i < 38; i++) {
		for (j = 0; j < 34; j++) {
			tc(cc_yellow);
			if (map[j][i] == 1) {
				gotoxy(2 * i + 2, j + 1);
				printf("▒");
			}
		}
	}
	while (p1.posx != p2.posx || p1.posy != p2.posy) {
		print_score(sc1, sc2);
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_cyan);
		printf("◈");
		gotoxy(2 * p2.posx + 2, p2.posy + 1);
		tc(cc_red);
		printf("◈");
		Sleep(50);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx--;
			if (map[p1.posy][p1.posx]) {
				sc1++;
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(D) && p1.posx < 37) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx++;
			if (map[p1.posy][p1.posx]) {
				sc1++;
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy--;
			if (map[p1.posy][p1.posx]) {
				sc1++;
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(S) && p1.posy < 33) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy++;
			if (map[p1.posy][p1.posx]) {
				sc1++;
				map[p1.posy][p1.posx] = 0;
			}
		}
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posx--;
			if (map[p2.posy][p2.posx]) {
				sc2++;
				map[p2.posy][p2.posx] = 0;
			}
		}
		if (GetAsyncKeyState(L) && p2.posx < 37) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posx++;
			if (map[p2.posy][p2.posx]) {
				sc2++;
				map[p2.posy][p2.posx] = 0;
			}
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posy--;
			if (map[p2.posy][p2.posx]) {
				sc2++;
				map[p2.posy][p2.posx] = 0;
			}
		}
		if (GetAsyncKeyState(K) && p2.posy < 33) {
			gotoxy(2 * p2.posx + 2, p2.posy + 1);
			printf("  ");
			p2.posy++;
			if (map[p2.posy][p2.posx]) {
				sc2++;
				map[p2.posy][p2.posx] = 0;
			}
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		tc(cc_cyan);
		p1_win();
	}
	else if (sc2 > sc1) {
		tc(cc_red);
		p2_win();
	}
	else {
		tc(cc_green);
		tie();
	}
	gotoxy(2 * p1.posx + 2, p1.posy + 1);
	printf("  ");
	gotoxy(2 * p1.posx + 2, p1.posy + 1);
	printf("◈");
	Sleep(3000);
}

void star_n7() {
	cls();
	int map1[34][19] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0 },
	{ 0,0,0,1,1,0,0,1,0,0,0,1,0,0,1,1,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	int map2[34][19] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0 },
	{ 0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0 },
	{ 0,0,0,1,1,0,0,1,0,0,0,1,0,0,1,1,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	chrpos p1 = { 9,0 };
	chrpos p2 = { 9,0 };
	int sc1 = 0, sc2 = 0;
	int rd, i, j;
	normalbound(c_gray);
	halfbound(c_gray, 2);
	for (i = 1; i < 18; i++) {
		for (j = 2; j < 25; j++) {
			tc(cc_yellow);
			if (map1[j][i] == 1) {
				gotoxy(2 * i + 2, j + 1);
				printf("■");
			}
			if (map2[j][i] == 1) {
				gotoxy(2 * i + 40, j + 1);
				printf("■");
			}
		}
	}
	while (sc1 <= 2 && sc2 <= 2) {
		print_score(sc1, sc2);
		for (i = 1; i < 18; i++) {
			for (j = 2; j < 25; j++) {
				if (map1[j][i]) {
					if (p1.posx != i || p1.posy != j) {
						switch (map1[j][i]) {
						case 1: case 4: tc(cc_yellow); break;
						case 2: tc(cc_green); break;
						case 3: tc(cc_blue); break;
						}
						gotoxy(2 * i + 2, j + 1);
						printf("■");
					}
				}
				if (map2[j][i]) {
					if (p2.posx != i || p2.posy != j) {
						switch (map2[j][i]) {
						case 1: case 4: tc(cc_yellow); break;
						case 2: tc(cc_green); break;
						case 3: tc(cc_blue); break;
						}
						gotoxy(2 * i + 40, j + 1);
						printf("■");
					}
				}
			}
		}
		gotoxy(2 * p1.posx + 2, p1.posy + 1);
		tc(cc_cyan);
		printf("◈");
		gotoxy(2 * p2.posx + 40, p2.posy + 1);
		tc(cc_red);
		printf("◈");
		Sleep(50);
		if (GetAsyncKeyState(A) && p1.posx > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx--;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(D) && p1.posx < 18) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posx++;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(W) && p1.posy > 0) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy--;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(S) && p1.posy < 33) {
			gotoxy(2 * p1.posx + 2, p1.posy + 1);
			printf("  ");
			p1.posy++;
			if (map1[p1.posy][p1.posx] == sc1 + 1) map1[p1.posy][p1.posx]++;
		}
		if (GetAsyncKeyState(J) && p2.posx > 0) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posx--;
			if (map2[p2.posy+1][p2.posx-19] == sc2 + 1) map2[p2.posy+1][p2.posx-19]++;
		}
		if (GetAsyncKeyState(L) && p2.posx < 18) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posx++;
			if (map2[p2.posy+1][p2.posx-19] == sc2 + 1) map2[p2.posy+1][p2.posx-19]++;
		}
		if (GetAsyncKeyState(I) && p2.posy > 0) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posy--;
			if (map2[p2.posy+1][p2.posx-19] == sc2 + 1) map2[p2.posy+1][p2.posx-19]++;
		}
		if (GetAsyncKeyState(K) && p2.posy < 33) {
			gotoxy(2 * p2.posx + 40, p2.posy + 1);
			printf("  ");
			p2.posy++;
			if (map2[p2.posy+1][p2.posx-19] == sc2 + 1) map2[p2.posy+1][p2.posx-19]++;
		}
		int ct1 = 0, ct2 = 0;
		for (i = 1; i < 18; i++) {
			for (j = 9; j < 25; j++) {
				if (map1[j][i] == sc1 + 2) ct1++;
				if (map2[j][i] == sc2 + 2) ct2++;
			}
		}
		if (ct1 == 63) sc1++;
		if (ct2 == 63) sc2++;
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) {
		tc(cc_cyan);
		p1_win();
	}
	else if (sc2 > sc1) {
		tc(cc_red);
		p2_win();
	}
	else {
		tc(cc_green);
		tie();
	}
	gotoxy(2 * p1.posx + 2, p1.posy + 1);
	printf("  ");
	gotoxy(2 * p1.posx + 2, p1.posy + 1);
	printf("◈");
	Sleep(3000);
}

void tail_n8() {
	cls();
	normalbound(c_gray);
	halfbound(c_gray, 2);
	chrpos p1_snake[300], p2_snake[300], item;
	int i, len1 = 10, len2 = 10;
	dir1 = -1;
	dir2 = -1;
	int speed = 150, win = -1;
	for (i = 0; i < 10; i++) {
		p1_snake[i].posx = 9 - i;
		p1_snake[i].posy = 18;
		gotoxy(2 * p1_snake[i].posx + 2, p1_snake[i].posy + 1);
		tc(cc_cyan);
		printf("◎");
		p2_snake[i].posx = 28 + i;
		p2_snake[i].posy = 18;
		gotoxy(2 * p2_snake[i].posx + 2, p2_snake[i].posy + 1);
		tc(cc_yellow);
		printf("◎");
	}
	gotoxy(2 * p1_snake[0].posx + 2, p1_snake[0].posy + 1);
	tc(cc_cyan);
	printf("●");
	gotoxy(2 * p2_snake[0].posx + 2, p2_snake[0].posy + 1);
	tc(cc_yellow);
	printf("●");
	item.posx = rand() % 36 + 1;
	item.posy = rand() % 32 + 1;
	if (item.posy == 18) item.posy = rand() % 17 + 1;
	gotoxy(2 * item.posx + 2, item.posy + 1);
	tc(cc_red);
	printf("♥");
	while (1) {
		print_score(len1, len2);
		if (check_snake(p1_snake, p2_snake, len1)) {
			if (check_snake(p2_snake, p1_snake, len2)) {
				win = 0;
				break;
			}
			else win = 2;
			break;
		}
		else if (check_snake(p2_snake, p1_snake, len2)) {
			win = 1;
			break;
		}
		if (p1_snake[0].posx == item.posx && p1_snake[0].posy == item.posy) {
			item.posx = rand() % 36 + 1;
			item.posy = rand() % 32 + 1;
			if (len1 < 300) {
				for (i = 0; i < 5; i++) {
					p1_snake[len1] = p1_snake[len1 - 1];
					len1++;
				}
			}
		}
		if (p2_snake[0].posx == item.posx && p2_snake[0].posy == item.posy) {
			item.posx = rand() % 36 + 1;
			item.posy = rand() % 32 + 1;
			if (len2 < 300) {
				for (i = 0; i < 5; i++) {
					p2_snake[len2] = p2_snake[len2 - 1];
					len2++;
				}
			}
		}
		gotoxy(2 * item.posx + 2, item.posy + 1);
		tc(cc_red);
		printf("♥");
		move_snake(p1_snake, p2_snake, len1, len2);
		speed = 100 - 5 * (len1 > len2) - 5 * (len1 <= len2);
		if (speed <= 20) speed = 20;
		Sleep(speed);
	}
	switch (win) {
	case -1: break;
	case 0: tie(); break;
	case 1: p1_win(); break;
	case 2: p2_win(); break;
	}
	Sleep(3000);
}
//edit 

void guess_n9() {
	cls();
	normalbound(c_gray);
	halfbound(c_gray, 3);
	int sc1 = 0, sc2 = 0, rd1 = 0, rd2 = 0, rd3 = 0, rd4 = 0;
	{
		tc(cc_yellow);
		gotoxy(32, 7);
		printf("■  ■    ■■■");
		gotoxy(32, 8);
		printf("■  ■    ■    ");
		gotoxy(32, 9);
		printf("■  ■    ■■■");
		gotoxy(32, 10);
		printf("■  ■        ■");
		gotoxy(32, 11);
		printf("  ■      ■■■");
		tc(cc_green);
		gotoxy(32, 24);
		printf("■  ■    ■■■");
		gotoxy(32, 25);
		printf("■  ■    ■    ");
		gotoxy(32, 26);
		printf("■  ■    ■■■");
		gotoxy(32, 27);
		printf("■  ■        ■");
		gotoxy(32, 28);
		printf("  ■      ■■■");
	}
	rd1 = rand() % 3;
	rd2 = (rand() / 2) % 3;
	rd3 = (rand() / 3) % 3;
	rd4 = (rand() / 4) % 3;
	print_hand(6, 3, rd1);
	print_hand(52, 3, rd2);
	print_hand(6, 20, rd3);
	print_hand(52, 20, rd4);
	//clock_t c1 = clock();
	//clock_t c2 = clock();
	print_score(sc1, sc2);
	while (sc1 < 20 && sc2 < 20) {
		if (rd1 == (rd2 + 2) % 3) {
			if (GetAsyncKeyState(A) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(A) & 0x8001)) {
					sc1++;
					rd1 = rand() % 3;
					rd2 = (rand() / 2) % 3;
					print_hand(6, 3, rd1);
					print_hand(52, 3, rd2);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd1 == rd2) {
			if (GetAsyncKeyState(W) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(W) & 0x8001)) {
					sc1++;
					rd1 = rand() % 3;
					rd2 = (rand() / 2) % 3;
					print_hand(6, 3, rd1);
					print_hand(52, 3, rd2);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd1 == (rd2 + 1) % 3) {
			if (GetAsyncKeyState(D) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(D) & 0x8001)) {
					sc1++;
					rd1 = rand() % 3;
					rd2 = (rand() / 2) % 3;
					print_hand(6, 3, rd1);
					print_hand(52, 3, rd2);
					print_score(sc1, sc2);
				}
			}
		}
		if (rd3 == (rd4 + 2) % 3) {
			if (GetAsyncKeyState(J) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(J) & 0x8001)) {
					sc2++;
					rd3 = (rand() / 3) % 3;
					rd4 = (rand() / 4) % 3;
					print_hand(6, 20, rd3);
					print_hand(52, 20, rd4);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd3 == rd4) {
			if (GetAsyncKeyState(I) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(I) & 0x8001)) {
					sc2++;
					rd3 = (rand() / 3) % 3;
					rd4 = (rand() / 4) % 3;
					print_hand(6, 20, rd3);
					print_hand(52, 20, rd4);
					print_score(sc1, sc2);
				}
			}
		}
		else if (rd3 == (rd4 + 1) % 3) {
			if (GetAsyncKeyState(L) & 0x8000) {
				Sleep(100);
				if (!(GetAsyncKeyState(L) & 0x8001)) {
					sc2++;
					rd3 = (rand() / 3) % 3;
					rd4 = (rand() / 4) % 3;
					print_hand(6, 20, rd3);
					print_hand(52, 20, rd4);
					print_score(sc1, sc2);
				}
			}
		}
	}
	print_score(sc1, sc2);
	if (sc1 > sc2) p1_win();
	else if (sc2 > sc1) p2_win();
	else tie();
	Sleep(3000);
}

void selectmenu(int selcheck) {
	char ch = 0;
	if (selcheck) PlaySound(TEXT("tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
	if (selcheck % 2) sm_np(cc_green);
	else sm_np(c_white);
	if (selcheck - 1 && selcheck > 0) sm_sp(cc_purple);
	else sm_sp(c_white);
	if (selcheck == 0) {
		tc(c_white);
		gotoxy(53, 36);
		printf("※ ←, →키로 이동합니다.");
		gotoxy(47, 38);
		printf("※ ENTER키로 항목을 선택합니다.");
	}
	if (!selcheck) Sleep(1200);
	tc(c_white);
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch == FUNCTION_KEY) {
				ch = getch();
				if (ch == LEFT) {
					selectmenu(1);
					return;
				}
				else if (ch == RIGHT) {
					selectmenu(2);
					return;
				}
			}
			else if (ch == ENTER) break;
		}
	}
	if (selcheck == 0) selcheck = 1;
	selme = selcheck - 1;
	return;
}

void spin_number(int a) {
	tc(c_gray);
	gotoxy(7, 21);
	printf("%1d", (a + 5) % 9 + 1);
	gotoxy(19, 21);
	printf("%1d", (a + 6) % 9 + 1);
	gotoxy(31, 21);
	printf("%1d", (a + 7) % 9 + 1);
	gotoxy(49, 21);
	printf("%1d", a % 9 + 1);
	gotoxy(61, 21);
	printf("%1d", (a + 1) % 9 + 1);
	gotoxy(73, 21);
	printf("%1d", (a + 2) % 9 + 1);
	tc(cc_white);
	gotoxy(40, 21);
	printf("%1d", a);
}

void spin(int a) {
	int i;
	{
		tc(cc_yellow);
		gotoxy(32, 9);
		printf("■■■■■■■■");
		gotoxy(32, 10);
		printf("■            ■");
		gotoxy(34, 11);
		printf("■        ■");
		gotoxy(34, 12);
		printf("■        ■");
		gotoxy(36, 13);
		printf("■    ■");
		gotoxy(36, 14);
		printf("■    ■");
		gotoxy(38, 15);
		printf("■■");
		gotoxy(38, 16);
		printf("■■");
		tc(cc_cyan);
		for (i = 18; i <= 24; i++) {
			gotoxy(36, i);
			if (i == 18 || i == 24) printf("■■■■");
			else printf("■    ■");
		}
		tc(c_gray);
		gotoxy(2, 18);
		printf("■■■■■■■■■■■■■■■■■");
		gotoxy(44, 18);
		printf("■■■■■■■■■■■■■■■■■");
		gotoxy(2, 24);
		printf("■■■■■■■■■■■■■■■■■");
		gotoxy(44, 24);
		printf("■■■■■■■■■■■■■■■■■");
		for (i = 19; i <= 23; i++) {
			gotoxy(12, i);
			printf("■");
			gotoxy(24, i);
			printf("■");
			gotoxy(54, i);
			printf("■");
			gotoxy(66, i);
			printf("■");
		}
	}
	PlaySound(TEXT("spin.wav"), 0, SND_FILENAME | SND_ASYNC);
	for (i = 1; i <= 41; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(50);
	}
	for (i = 42; i <= 81; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(95);
	}
	for (i = 82; i <= 87; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(280);
	}
	for (i = 88; i <= 90; i++) {
		spin_number((a + i + 8) % 9 + 1);
		Sleep(340);
	}
	spin_number(a);
	gotoxy(24, 30);
	tc(cc_yellow);
	printf("\"%s\"", gm[a]);
	tc(c_white);
	printf(" 게임을 시작합니다!");
	Sleep(2000);
}

void explain(int a) {
	char name[100], explain[100], howto[100], ready[100], go[100];
	int dpi;
	HBITMAP nm, ex, ht, rd, g;
	HWND hWnd = getConsoleWindowHandle();
	dpi = GetDPI(hWnd);
	sprintf(explain, "explain.bmp");
	sprintf(ready, "ready.bmp");
	sprintf(go, "go.bmp");
	switch (a) {
	case 1: sprintf(name, "1.bmp"); break;
	case 2: sprintf(name, "2.bmp"); break;
	case 3: sprintf(name, "3.bmp"); break;
	case 4: sprintf(name, "4.bmp"); break;
	case 5: sprintf(name, "5.bmp"); break;
	case 6: sprintf(name, "6.bmp"); break;
	case 7: sprintf(name, "7.bmp"); break;
	case 8: sprintf(name, "8.bmp"); break;
	case 9: sprintf(name, "9.bmp"); break;
	}
	switch (a) {
	case 1: sprintf(howto, "h1.bmp"); break;
	case 2: sprintf(howto, "h2.bmp"); break;
	case 3: sprintf(howto, "h3.bmp"); break;
	case 4: sprintf(howto, "h4.bmp"); break;
	case 5: sprintf(howto, "h5.bmp"); break;
	case 6: sprintf(howto, "h6.bmp"); break;
	case 7: sprintf(howto, "h7.bmp"); break;
	case 8: sprintf(howto, "h8.bmp"); break;
	case 9: sprintf(howto, "h9.bmp"); break;
	}
	nm = (HBITMAP)LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ex = (HBITMAP)LoadImage(NULL, explain, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	ht = (HBITMAP)LoadImage(NULL, howto, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	rd = (HBITMAP)LoadImage(NULL, ready, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	g = (HBITMAP)LoadImage(NULL, go, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	paint(hWnd, dpi, nm, 800, 800);
	switch (a) {
	case 1: PlaySound(TEXT("1.wav"), 0, SND_FILENAME); break;
	case 2: PlaySound(TEXT("2.wav"), 0, SND_FILENAME); break;
	case 3: PlaySound(TEXT("3.wav"), 0, SND_FILENAME); break;
	case 4: PlaySound(TEXT("4.wav"), 0, SND_FILENAME); break;
	case 5: PlaySound(TEXT("5.wav"), 0, SND_FILENAME); break;
	case 6: PlaySound(TEXT("6.wav"), 0, SND_FILENAME); break;
	case 7: PlaySound(TEXT("7.wav"), 0, SND_FILENAME); break;
	case 8: PlaySound(TEXT("8.wav"), 0, SND_FILENAME); break;
	case 9: PlaySound(TEXT("9.wav"), 0, SND_FILENAME); break;
	}
	paint(hWnd, dpi, ex, 800, 800);
	PlaySound(TEXT("explain.wav"), 0, SND_FILENAME); 
	cls();
	Sleep(85);
	paint(hWnd, dpi, ht, 800, 800);
	PlaySound(TEXT("anticipation.wav"), 0, SND_FILENAME); 
	cls();
	Sleep(85);
	paint(hWnd, dpi, rd, 800, 800);
	PlaySound(TEXT("ready.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(2000);
	cls();
	Sleep(85);
	paint(hWnd, dpi, g, 800, 800);
	PlaySound(TEXT("go.wav"), 0, SND_FILENAME | SND_ASYNC);
	Sleep(1000);
	cls();
}

int again() {
	cls();
	int i, j;
	char ch;
	int p[5][3] = { { 1,1,1 },{ 1,0,1 },{ 1,1,1 },{ 1,0,0 },{ 1,0,0 } };
	normalbound(c_gray);
	{
		tc(cc_yellow);
		gotoxy(30, 5);
		printf("★ 최종 점수 체크 ★");
		tc(cc_cyan);
		for (i = 8; i <= 12; i++) {
			gotoxy(22, i);
			printf("■");
		}
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 5; j++) {
				if (p[j][i]) {
					gotoxy(2 * i + 28, j + 8);
					printf("■");
					gotoxy(2 * i + 56, j + 8);
					printf("■");
				}
			}
		}
		gotoxy(46, 8);
		printf("■■■");
		gotoxy(50, 9);
		printf("■");
		gotoxy(46, 10);
		printf("■■■");
		gotoxy(46, 11);
		printf("■");
		gotoxy(46, 12);
		printf("■■■");
	}
	tc(cc_cyan);
	gotoxy(27, 19);
	printf("%1d", total1);
	gotoxy(55, 19);
	printf("%1d", total2);
	tc(cc_white);
	if (total1 > total2) {
		gotoxy(21, 27);
		printf("★ 1P의 승리입니다! 다시 하시겠습니까?");
	}
	else if (total1 < total2) {
		gotoxy(21, 27);
		printf("★ 2P의 승리입니다! 다시 하시겠습니까?");
	}
	else {
			gotoxy(19, 27);
			printf("★ 비겼군요! 놀라워요! 다시 하시겠습니까?");
	}
	gotoxy(21, 29);
	printf("Y : Yes (선택 메뉴로 돌아갑니다)");
	gotoxy(21, 31);
	printf("N : No (종료합니다)");
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch == 121 || ch == 110 || ch == 89 || ch == 78) break;
		}
	}
	if (ch == 121 || ch == 89) return 1;
	else return 0;
}

void normalgame() {
	int arr[9];
	int i, j, rd, tmp;
	cls();
	normalbound(c_gray);
	total1 = 0;
	total2 = 0;
	for (i = 0; i < 9; i++) arr[i] = i + 1;
	for (i = 0; i < 8; i++) {
		rd = rand() % (9 - i) + i;
		tmp = arr[i];
		arr[i] = arr[rd];
		arr[rd] = tmp;
	}
	for (i = 0; i < 9; i++) {
		spin(arr[i]);
		explain(arr[i]);
		mciOpen.lpstrElementName = "dating_tense.mp3";
		mciOpen.lpstrDeviceType = "mpegvideo";
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
		switch (arr[i]) {
		case 1: click_n1(); break;
		case 2: maze_n2(); break;
		case 3: heart_n3(); break;
		case 4: run_n4(); break;
		case 5: color_n5(); break;
		case 6: thief_n6(); break;
		case 7: star_n7(); break;
		case 8: tail_n8(); break;
		case 9: guess_n9(); break;
		}
		StopAllSounds(dwID);
		cls();
		normalbound(c_gray);
	}
	if (again()) {
		{
			PlaySound(TEXT("select_mode.wav"), 0, SND_FILENAME | SND_ASYNC);
			Sleep(20);
			mciOpen.lpstrElementName = "sunburst.mp3";
			mciOpen.lpstrDeviceType = "mpegvideo";
			mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
			dwID = mciOpen.wDeviceID;
			mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
		}
		selectmenu(0);
	}
	else exit(0);
}

void selectgame(int sel) {
	int i;
	char ch;
	int rc = rand() % 6 + 9;
	tc(rc);
	if (sel >= 0) PlaySound(TEXT("tp_click.wav"), 0, SND_FILENAME | SND_ASYNC);
	gotoxy(14, 2);
	printf("★ 시작할 게임을 선택하여 주십시오.");
	gotoxy(66, 38);
	printf("SELECT MODE");
	tc(c_white);
	gotoxy(50, 2);
	printf("(ENTER로 결정)");
	for (i = 1; i <= 9; i++) {
			if (i == sel) {
				tc(c_yellow);
				gotoxy(10, 3 + 3 * i);
				printf("▶  ");
			}
			else {
				tc(c_white);
				gotoxy(10, 3 + 3 * i);
				printf("   ");
			}
			gotoxy(14, 3 + 3 * i);
			printf("%d. %s", i, gm[i]);
			if (sel >= 10 && sel - 9 == i) {
				tc(c_yellow);
				gotoxy(44, 3 + 3 * i);
				printf("▶  ");
			}
			else {
				tc(c_white);
				gotoxy(44, 3 + 3 * i);
				printf("    ");
			}
			gotoxy(48, 3 + 3 * i);
			printf("%c. %s", order[i-1], gm[i + 9]);
		}
	tc(cc_red);
	if (sel == 0) {
			gotoxy(10, 34);
			printf("▶  ");
		}
	else {
			gotoxy(10, 34);
			printf("    ");
		}
	gotoxy(14, 34);
	printf("0. 종료하기");
	while (1) {
		if (kbhit()) {
			ch = getch();
			if (ch >= '0' && ch <= '9') {
					selectgame(ch - 48);
					return;
				}
			else if (ch == ESC) {
					if (sel <= -1) {
						selectgame(-2);
						return;
					}
					else {
						selectgame(-1);
						return;
					}
				}
			else {
				for (i = 0; i < 9; i++) {
					if (ch == order[i] || ch == order[i] + 32) {
						selectgame(i + 10);
						return;
					}
				}
			}
			if (ch == ENTER) break;
		}
	}
	tc(c_white);
	if (sel == 0) {
			cls();
			exit(0);
			return;
		}
	switch (sel) {
	case 1: click_n1(); break;
	case 2: maze_n2(); break;
	case 3: heart_n3(); break;
	case 4: run_n4(); break;
	case 5: color_n5(); break;
	case 6: thief_n6(); break;
	case 7: star_n7(); break;
	case 8: tail_n8(); break;
	case 9: guess_n9(); break;
	default: cls(); /*printf("%d", sel);*/ Sleep(1000); break;
	}
	cls();
	normalbound(c_gray);
	selectgame(0);
	return;
}

void main() {
	srand(time(NULL)); //랜덤 난수 생성
	Console(); //콘솔 정보 변경
	clearCursor(); //커서 삭제
	Opening(); //오프닝
	PlaySound(TEXT("michun.wav"), 0, SND_FILENAME | SND_ASYNC); //미천합니다 Sound
	mciOpen.lpstrElementName = "Glacia2.mp3"; //배경음
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
	dwID = mciOpen.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay); //배경음 플레이
	maintitle(0); //메인 화면
	StopAllSounds(dwID); //끝날 시 소리 정지
	cls(); //비우기
	{
		PlaySound(TEXT("select_mode.wav"), 0, SND_FILENAME | SND_ASYNC);
		Sleep(20);
		mciOpen.lpstrElementName = "sunburst.mp3";
		mciOpen.lpstrDeviceType = "mpegvideo";
		mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
		dwID = mciOpen.wDeviceID;
		mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
	} //음악 재생
	selectmenu(0); //메뉴 고르기
	StopAllSounds(dwID); //소리 정지
	if (!selme) normalgame(); //노말
	else {
		cls();
		normalbound(c_gray);
		selectgame(0); //선택
	}
	exit(0);
	getchar(); //끝
}