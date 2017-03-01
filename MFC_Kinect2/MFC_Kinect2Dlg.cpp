
// MFC_Kinect2Dlg.cpp : ��@��
//

#include "stdafx.h"
#include "MFC_Kinect2.h"
#include "MFC_Kinect2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFC_Kinect2Dlg ��ܤ��
Kinect2Capture CMFC_Kinect2Dlg::kinect;
IplImage* CMFC_Kinect2Dlg::static_img_Rgb=nullptr;
IplImage* CMFC_Kinect2Dlg::static_img_Depth = nullptr;

CMFC_Kinect2Dlg::CMFC_Kinect2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_KINECT2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_Kinect2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Img_RGB, m_Img_RGB);
	DDX_Control(pDX, IDC_Img_Depth, m_Img_Depth);
}

BEGIN_MESSAGE_MAP(CMFC_Kinect2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Test, &CMFC_Kinect2Dlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CMFC_Kinect2Dlg �T���B�z�`��

BOOL CMFC_Kinect2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	m_Img_RGB.SetWindowPos(NULL, 10, 10, 320, 240, SWP_SHOWWINDOW);
	m_Img_Depth.SetWindowPos(NULL, 10, 10+240, 320, 240, SWP_SHOWWINDOW);

	for (int i = 0; i < 2; i++)
	{
		m_threadPara.m_case = i;
		m_threadPara.hWnd = m_hWnd;
		m_lpThread = AfxBeginThread(&CMFC_Kinect2Dlg::MythreadFun, (LPVOID)&m_threadPara);
		Sleep(1);
	}

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CMFC_Kinect2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CMFC_Kinect2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_Kinect2Dlg::ShowImage(IplImage* Image, CWnd* pWnd, int channels, CvSize size)
{
	CDC	*dc = pWnd->GetWindowDC();
	IplImage *Temp = NULL;
	if (channels != 4) {
		Temp = cvCreateImage(size, IPL_DEPTH_8U, channels);
		cvResize(Image, Temp, CV_INTER_LINEAR);
	}
	if (channels == 4)
	{
		Temp = cvCreateImage(size, IPL_DEPTH_8U, 3);
		IplImage *Temp_transfer = cvCreateImage(size, IPL_DEPTH_8U, 4);
		cvResize(Image, Temp_transfer, CV_INTER_LINEAR);
		cvCvtColor(Temp_transfer, Temp, CV_BGRA2BGR);
		cvReleaseImage(&Temp_transfer);
	}

	CvvImage Temp2;
	Temp2.CopyOf(Temp);
	Temp2.Show(*dc, 0, 0, Temp->width, Temp->height);
	cvReleaseImage(&Temp);
	ReleaseDC(dc);
}
UINT CMFC_Kinect2Dlg::MythreadFun(LPVOID LParam)
{
	CthreadParam* para = (CthreadParam*)LParam;
	CMFC_Kinect2Dlg* lpview = (CMFC_Kinect2Dlg*)(para->m_lpPara);
	para->m_blthreading = TRUE;

	switch (para->m_case)
	{
	case 0:
		lpview->Thread_Image_RGB(LParam);
		break;
	case 1:
		lpview->Thread_Image_Depth(LParam);
		break;
	default:
		break;
	}

	para->m_blthreading = FALSE;
	para->m_case = 0xFF;
	return 0;

}

void CMFC_Kinect2Dlg::Thread_Image_RGB(LPVOID lParam)
{
	CthreadParam * Thread_Info = (CthreadParam *)lParam;
	CMFC_Kinect2Dlg * hWnd = (CMFC_Kinect2Dlg *)CWnd::FromHandle((HWND)Thread_Info->hWnd);
	

	kinect.Open(1, 0, 0);
	while (1)
	{
		static_img_Rgb = kinect.RGBAImage();
		if (static_img_Rgb != NULL) {
			hWnd->ShowImage(static_img_Rgb, hWnd->GetDlgItem(IDC_Img_RGB), 4, cvSize(320, 240));
			cvReleaseImage(&static_img_Rgb);
		}
	}

}

void CMFC_Kinect2Dlg::Thread_Image_Depth(LPVOID lParam)
{
	CthreadParam * Thread_Info = (CthreadParam *)lParam;
	CMFC_Kinect2Dlg * hWnd = (CMFC_Kinect2Dlg *)CWnd::FromHandle((HWND)Thread_Info->hWnd);
	kinect.Open(0, 1, 1);

	while (1)
	{
		static_img_Depth = kinect.DepthImage();
		if (static_img_Depth != NULL)
		{
			hWnd->ShowImage(static_img_Depth, hWnd->GetDlgItem(IDC_Img_Depth),1,cvSize(320,240));
			cvReleaseImage(&static_img_Depth);
		}
	}
}

void CMFC_Kinect2Dlg::OnBnClickedButtonTest()
{
	CvPoint3D32f D2C = {0};
	CvPoint gg;
	CvPoint RGBPoint=cvPoint(500, 250);
	kinect.Color2DepthSpace(RGBPoint,&gg);
	CString str;
	str.Format(_T("%d,%d"), gg.x, gg.y);
	SetDlgItemText(IDC_Point_Show, str);
}
