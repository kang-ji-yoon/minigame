//#include <stdio.h>
//#include <Windows.h>
//#include <mmsystem.h>
//#include "Digitalv.h"
//#pragma comment(lib, "winmm.lib")
//int dwID;
//MCI_OPEN_PARMS m_mciOpenParms;
//MCI_PLAY_PARMS m_mciPlayParms;
//DWORD m_dwDeviceID;
//MCI_OPEN_PARMS mciOpen;
//MCI_PLAY_PARMS mciPlay;
//
//int main(void) {
//	mciOpen.lpstrElementName = "aaa.mp3";
//	mciOpen.lpstrDeviceType = "mpegvideo";
//	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);
//	dwID = mciOpen.wDeviceID;
//	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay); //MCI_NOTIFY: �⺻, MCI_DGV_PLAY_REPEAT: �ݺ�
//																			
//	//mciSendCommandW(dwID, MCI_PAUSE, MCI_NOTIFY, (DWORD)(LPVOID)&m_mciPlayParms);     // �Ͻ����� Ŀ�ǵ�
//	//mciSendCommandW(dwID, MCI_RESUME, 0, NULL);       // ����ϱ�
//	//mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);        // ����
//	getchar();
//}