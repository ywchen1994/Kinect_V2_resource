
#pragma once
#include "afxwin.h"
#include"Kinect.h"
#include "opencv.hpp"


class Kinect2Capture :public CWnd
{
public:
	Kinect2Capture();
	~Kinect2Capture();



	//Open(RGBImage, DepthImage, InfraredImage)
	void Open(bool rgb, bool depth, bool Infrared);

	void Close();
	IKinectSensor* pSensor;

	void setColorROISize(CvRect ROI, CvSize size);
	void setDepthROISize(CvRect ROI, CvSize size);

	IplImage* RGBAImage();
	bool fColorOpened;
	IColorFrameReader* pColorFrameReader;
	IColorFrame* pColorFrame;
	cv::Mat mColorImg;
	UINT uColorBufferSize;
	CvRect colorROI;
	CvSize colorSize;


	IplImage* DepthImage();
	cv::Mat DepthImageM();
	
	bool fDepthOpened;
	IDepthFrameReader* pDepthFrameReader;
	int iDepthWidth, iDepthHeight;
	UINT16 uDepthMax;
	cv::Mat mDepthImg;
	cv::Mat mDepthImg8bit;
	CvRect depthROI;
	CvSize depthSize;


	IplImage* InfraredImage();
	bool fInfraredOpened;
	IInfraredFrameReader* pInfraredFrameReader;
	int iInfraredWidth, iInfraredHeight;
	IDepthFrame* pDepthFrame;


	void Color2DepthSpace(CvPoint RGBpoint, CvPoint * Depthpoint);
	void Color2CameraSpace(CvPoint RGBpoint, CvPoint3D32f * CameraSpace);
	void Depth2CameraSpace(CvPoint Depthpoint,CvPoint3D32f * CameraSpace);
	void Depth2ColorSpace(CvPoint Depthpoint, CvPoint * RGBpoint);
	ICoordinateMapper* pCoordinateMapper;
	UINT uDepthPointNum;
	UINT uColorPointNum;
	UINT16*				pDepthPoints = new UINT16[uDepthPointNum];
	DepthSpacePoint*	pPointArray = new DepthSpacePoint[uColorPointNum];
	CameraSpacePoint* pCSPoints = nullptr;//�Ψ��x�s�m��v������v���y�Ъ�����
	CameraSpacePoint* pDSPoints = nullptr;//�Ψ��x�s�`�׼v������v���y�Ъ�����
	int iHeight;
	int iWidth;




};

