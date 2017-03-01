
// MFC_Kinect2Dlg.h : 標頭檔
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

// CMFC_Kinect2Dlg 對話方塊
class CMFC_Kinect2Dlg : public CDialogEx
{
// 建構
public:
	CMFC_Kinect2Dlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_KINECT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
