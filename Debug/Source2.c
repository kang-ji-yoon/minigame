//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//#include<conio.h>
//#include<Windows.h>
//#pragma warning(disable:4996)
//#define WIDTH 50
//#define HEIGHT 26
//#define RIGHT 77
//#define LEFT 75
//#define c_black 0
//#define c_blue 1
//#define c_green 2
//#define c_cyan 3
//#define c_red 4
//#define c_purple 5
//#define c_yellow 6
//#define c_white 7
//#define c_gray 8
//#define cc_blue 9
//#define cc_green 10
//#define cc_cyan 11
//#define cc_red 12
//#define cc_purple 13
//#define cc_yellow 14
//#define cc_white 15
//#define ESC 27
//#define STAR_NUM 30
//#define MAX_SPEED 2
//
//typedef struct _Star {
//	int x;
//	int y;
//	int speed;
//}Star;
//
//void gotoxy(int x, int y)
//{
//	COORD pos = { x,y };
//	SetConsoleCursorPosition(
//		GetStdHandle(STD_OUTPUT_HANDLE),
//		pos);
//}
//void displayStart()
//{
//	while (1)
//	{
//		gotoxy(11, HEIGHT / 2);
//		printf("시작하려면 아무키나 누르세요");
//		Sleep(500);
//		if (kbhit())
//		{
//			getch();
//			break;
//		}
//		gotoxy(11, HEIGHT / 2);
//		printf("                                         ");
//		Sleep(500);
//	}
//}
//void resizeConsole()
//{
//	char chTemp[50];
//	sprintf(chTemp, "Mode con cols=%d lines=%d"
//		, WIDTH, HEIGHT);
//	system(chTemp);
//}
//void printBound()
//{
//	for (int y = 0; y < HEIGHT; y++)
//	{
//		for (int x = 0; x < WIDTH; x += 2)
//		{
//			if (y < 2)
//				printf("  ");
//			else if (x == 0 || y == 2 ||
//				x == WIDTH - 2 || y == HEIGHT - 1)
//				printf("■");
//			else
//				printf("  ");
//		}
//	}
//}
//void displayScore(int s)
//{
//	gotoxy(WIDTH / 2, 1);
//	printf("Score : %2d", s);
//}
//void clearCursor()
//{
//	CONSOLE_CURSOR_INFO c = { 0 };
//	c.dwSize = 1;
//	c.bVisible = FALSE;
//	SetConsoleCursorInfo(
//		GetStdHandle(STD_OUTPUT_HANDLE),
//		&c
//	);
//}
//void move(int x, int dir)
//{
//	if (dir == RIGHT)
//	{
//		gotoxy(x - 1, HEIGHT - 2);
//		printf(" ");
//	}
//	else if (dir == LEFT)
//	{
//		gotoxy(x + 1, HEIGHT - 2);
//		printf(" ");
//	}
//	gotoxy(x, HEIGHT - 2);
//	printf("▲");
//}
//void initStar(Star * s)
//{
//	for (int i = 0; i < STAR_NUM; i++)
//	{
//		s[i].x = rand() % 46 + 2;
//		s[i].y = 3;
//		s[i].speed = (rand() % MAX_SPEED + 10);
//	}
//}
//void displayStar(Star *s, int count)
//{
//	for (int i = 0; i < STAR_NUM; i++)
//	{
//		if (s[i].y - 1> 2 &&
//			(count % s[i].speed == 0 || s[i].y == HEIGHT - 1))
//		{
//			gotoxy(s[i].x, s[i].y - 1);
//			printf(" ");
//		}
//		if (s[i].y > HEIGHT - 2)
//		{
//			s[i].y = 3;
//			s[i].x = rand() % 46 + 2;
//			s[i].speed = rand() % MAX_SPEED + 10;
//		}
//		if (count % s[i].speed == 0)
//		{
//			gotoxy(s[i].x, s[i].y);
//			printf("*");
//			s[i].y++;
//		}
//	}
//}
//
//int checkCrush(int x, Star *s) {
//	int i;
//	for (i = 0; i < STAR_NUM; i++) {
//		if (s[i].y == HEIGHT - 2 && (s[i].x == x || s[i].x == x + 1)) return 1;
//	}
//	return 0;
//}
//
//int main()
//{
//	int score = 0;
//	char ch;
//	int xPosition = WIDTH / 2;
//	Star s[STAR_NUM];
//	int count = 0;
//
//	clearCursor();
//	resizeConsole();
//	displayStart();
//	system("cls");
//	printBound();
//
//	displayScore(score);
//	move(xPosition, RIGHT);
//
//	initStar(s);
//
//	while (1)
//	{
//		if (count % 100 == 0)
//		{
//			score++;
//			displayScore(score);
//			count = 0;
//		}
//		displayStar(s, count);
//
//		if (kbhit())
//		{
//			ch = getch();
//			if (ch == RIGHT && xPosition < WIDTH - 4)
//			{
//				move(++xPosition, RIGHT);
//			}
//			else if (ch == LEFT && xPosition > 2)
//				move(--xPosition, LEFT);
//		}
//		if (checkCrush(xPosition, s)) {
//			system("cls");
//			gotoxy(WIDTH / 2 - 5, HEIGHT / 2);
//			printf("게임 끝.");
//			gotoxy(WIDTH / 2 - 5, HEIGHT / 2 + 1);
//			printf("점수: %d", score);
//			break;
//		}
//		Sleep(5);
//		count++;
//	}
//
//	getchar();
//}