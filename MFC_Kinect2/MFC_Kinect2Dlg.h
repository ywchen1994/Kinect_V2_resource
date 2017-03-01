
// MFC_Kinect2Dlg.h : ���Y��
//

#pragma once
#include"cv.h"
#include"highgui.h"
#include"CvvImage.h"
#include "afxwin.h"
#include"..//Kinect2Capture//Kinect2Capture.h"

struct CthreadParam
{
public:
	HWND hWnd;
	LPVOID m_lpPara;
	UINT   m_case;
	BOOL m_blthreading;
};

// CMFC_Kinect2Dlg ��ܤ��
class CMFC_Kinect2Dlg : public CDialogEx
{
// �غc
public:
	CMFC_Kinect2Dlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_KINECT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void ShowImage(IplImage * Image, CWnd * pWnd, int channels, CvSize size);
	DECLARE_MESSAGE_MAP()
public:
	static Kinect2Capture kinect;
	CStatic m_Img_RGB;
	static UINT MythreadFun(LPVOID LParam);
	void Thread_Image_Depth(LPVOID lParam);
	void Thread_Image_RGB(LPVOID lParam);
	CthreadParam m_threadPara;
	CWinThread*  m_lpThread;
	CStatic m_Img_Depth;
	static IplImage* static_img_Rgb;
	static IplImage* static_img_Depth;
	afx_msg void OnBnClickedButtonTest();
};
