﻿
// MFC_plus_YoloDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_plus_Yolo.h"
#include "MFC_plus_YoloDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

extern "C" int start_main(int argc, char **argv);

// CMFCplusYoloDlg 대화 상자



CMFCplusYoloDlg::CMFCplusYoloDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_PLUS_YOLO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCplusYoloDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCplusYoloDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

DWORD WINAPI MLThread(void* ap_data)
{
	int argc = 12;
	char* argv[12];

	argv[0] = "darknet.exe";
	argv[1] = "detector";
	argv[2] = "test";
	argv[3] = "cfg/coco.data";
	argv[4] = "yolov3.cfg";
	argv[5] = "yolov3.weights";
	argv[6] = "dog.jpg";
	argv[7] = "-ext_output";
	argv[8] = "-i";
	argv[9] = "0";
	argv[10] = "-thresh";
	argv[11] = "0.25";
	

	start_main(argc, argv);

	return 0;
}

// CMFCplusYoloDlg 메시지 처리기

BOOL CMFCplusYoloDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	HANDLE h_thread;
	h_thread = CreateThread(NULL, 0, MLThread, this, 0, NULL);

	if (h_thread != NULL) {
		// Thread 생성

	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}



// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCplusYoloDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCplusYoloDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

