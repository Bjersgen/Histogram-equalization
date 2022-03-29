#include <opencv.hpp>  
#include<iostream>  
#include"time.h"  
#include<vector>  
#include<map>  

using namespace std;
using namespace cv;

int main()
{

	Mat srcImage = imread("C://Users//60105//Desktop//opencv-3.4.9-vc14_vc15//hahaha.jpeg");
	imshow("原图", srcImage);
	CvScalar pixel;
	Mat src_gray;
	cvtColor(srcImage, src_gray, COLOR_BGR2GRAY);
	imshow("灰度图", src_gray);	
	Mat finalImg;
	equalizeHist(src_gray, finalImg);
	imshow("均衡后", finalImg);
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	uchar* pRow = 0;
  
	const int channels[1] = { 0 };
	float sum[256] = { 0 };
	float final[256] = { 0 };
 
	int histSize[] = { 256 };   
 
	float midRanges[] = { 0, 256 };
   
	const float* ranges[] = { midRanges };

	MatND dstHist_0;
	MatND dstHist_1;
	calcHist(&src_gray, 1, channels, Mat(), dstHist_0, 1, histSize, ranges, true, false);
	calcHist(&finalImg, 1, channels, Mat(), dstHist_1, 1, histSize, ranges, true, false);

	Mat drawImage1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat drawImage2 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat drawImage3 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat drawImage4 = Mat::zeros(Size(256, 256), CV_8UC3);

	double g_dHistMaxValue_0;
	double g_dHistMaxValue_1;
	minMaxLoc(dstHist_0, 0, &g_dHistMaxValue_0, 0, 0);
	minMaxLoc(dstHist_1, 0, &g_dHistMaxValue_1, 0, 0);

	//遍历直方图得到的数据    
	for (int i = 0; i < 256; i++)
	{
		int value = cvRound(256 * (dstHist_0.at<float>(i) / g_dHistMaxValue_0));

		line(drawImage1, Point(i, drawImage1.rows - 1), Point(i, drawImage1.rows - 1 - value), Scalar(255, 0, 0));
	}

	for (int i = 0; i < 256; i++)
	{
		int value = cvRound(256 * (dstHist_1.at<float>(i) / g_dHistMaxValue_1));

		line(drawImage4, Point(i, drawImage1.rows - 1), Point(i, drawImage1.rows - 1 - value), Scalar(255, 0, 0));
	}
	//printf("%lf", g_dHistMaxValue);
    float sum0 = 0;
	for (int i = 0; i < 256; i++)
	{
		int value = cvRound(256 * (dstHist_0.at<float>(i) / g_dHistMaxValue_0));
		sum[i] = dstHist_0.at<float>(i);
		sum0 = 0;
		for (int j = 0;  j <= i; j++) {

			sum0 += sum[j];
		}
		line(drawImage3, Point(i, drawImage2.rows - 1), Point(i, drawImage2.rows - 1 - 256*sum0 / (rows*cols)), Scalar(255, 0, 0));
	    //printf("%f///", sum0);
		int k = cvRound(256*sum0/(rows*cols));
		if (k == 256) k = 255;
		//printf("%d///", k);
		final[k] += dstHist_0.at<float>(i);
	}
	for (int j = 0; j <= 255; j++) {
		//printf("%f///", final[j]);
		line(drawImage2, Point(j, drawImage2.rows - 1), Point(j, drawImage2.rows - 1 - 256 * final[j] / g_dHistMaxValue_0), Scalar(255, 0, 0));
	}
	printf("%d",src_gray.ptr<uchar>(699)[699]);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			int gray = src_gray.ptr<uchar>(i)[j];
			int sum1 = 0;
			for (int p = 0; p <= gray; p++) {
				
				sum1 += sum[p];

			}
			int k = cvRound(256 * sum1 / (rows * cols));
			if (k == 256) k = 255;
			src_gray.ptr<uchar>(i)[j] = k;
			printf("%d//", src_gray.ptr<uchar>(i)[j]);
		}
	}
	imshow("自己均衡后", src_gray);
	imshow("直方图均衡前", drawImage1);
	imshow("直方图均衡后", drawImage2);
	imshow("PDF", drawImage3);
	imshow("系统自带", drawImage4);

	waitKey(0);

	return 0;
}