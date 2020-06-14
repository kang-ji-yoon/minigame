//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//void gotoxy(int x, int y)
//{
//	COORD pos = { x,y };
//	SetConsoleCursorPosition(
//		GetStdHandle(STD_OUTPUT_HANDLE),
//		pos);
//}
//
//int mai55n()
//{
//	int a = 0, up = 0;
//	printf("UP:\nD:");
//	while (1)
//	{
//		if (GetAsyncKeyState(VK_UP) & 0x8000)
//		{
//			gotoxy(4, 0);
//			Sleep(20);
//			if (!(GetAsyncKeyState(VK_UP) & 0x8001)) {
//				gotoxy(4, 0);
//				printf("%3d", ++up);
//			}
//		}
//		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
//		{
//			gotoxy(3, 1);
//			Sleep(20);
//			if (!(GetAsyncKeyState(VK_DOWN) & 0x8001)) {
//				gotoxy(3, 1);
//				printf("%3d", ++a);
//			}
//		}
//		if (GetAsyncKeyState(0x1B) != 0)
//		{
//			break;
//		}
//	}
//	return 0;
//}
