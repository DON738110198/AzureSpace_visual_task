#include <iostream>
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// 这个HSV图像要为全局变量
Mat imgHSV;
int iLowH1 = 100;
int iHighH1 = 124;

int iLowS1 = 90;
int iHighS1 = 255;

int iLowV1 = 90;
int iHighV1 = 255;


int iLowH2 = 52;
int iHighH2 = 90;

int iLowS2 = 43;
int iHighS2 = 255;

int iLowV2 = 35;
int iHighV2 = 255;

// 12个通过TrackBar调整HSV值后的回调函数
void on_track1(int value, void* userdata);
void on_track2(int value, void* userdata);
void on_track3(int value, void* userdata);
void on_track4(int value, void* userdata);
void on_track5(int value, void* userdata);
void on_track6(int value, void* userdata);
void on_track7(int value, void* userdata);
void on_track8(int value, void* userdata);
void on_track9(int value, void* userdata);
void on_track10(int value, void* userdata);
void on_track11(int value, void* userdata);
void on_track12(int value, void* userdata);

int main(int argc, char** argv)
{
	Mat imgOriginal = imread("../tag.png");

	if (imgOriginal.empty())  // if not success, exit program
	{
		cout << "读取图片失败" << endl;
		return -1;
	}

	vector<Mat> hsvSplit;
	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //将图片从BGR格式转换为HSV格式

	//因为我们读取的是彩色图，直方图均衡化需要在HSV空间做
	split(imgHSV, hsvSplit); // 分离通道，获得的是三个通道的图像矩阵
	equalizeHist(hsvSplit[2], hsvSplit[2]);
	merge(hsvSplit, imgHSV);

	//需要创建一个动态调节HSV值的控制台来调整HSV值，找到效果最好的值,但是现在已经找出来最为合适的HSV上下阈值了，所以这个功能就保留着，但是没有太大的用处了
	namedWindow("ControlBlue", WINDOW_AUTOSIZE);
	createTrackbar("LowH1", "ControlBlue", &iLowH1, 179, on_track1); //Hue (0 - 179)
	createTrackbar("HighH1", "ControlBlue", &iHighH1, 179, on_track2);

	createTrackbar("LowS1", "ControlBlue", &iLowS1, 255, on_track3); //Saturation (0 - 255)
	createTrackbar("HighS1", "ControlBlue", &iHighS1, 255, on_track4);

	createTrackbar("LowV1", "ControlBlue", &iLowV1, 255, on_track5); //Value (0 - 255)
	createTrackbar("HighV1", "ControlBlue", &iHighV1, 255, on_track6);

	namedWindow("ControlGreen", WINDOW_AUTOSIZE);
	createTrackbar("LowH2", "ControlGreen", &iLowH2, 179, on_track7); //Hue (0 - 179)
	createTrackbar("HighH2", "ControlGreen", &iHighH2, 179, on_track8);

	createTrackbar("LowS2", "ControlGreen", &iLowS2, 255, on_track9); //Saturation (0 - 255)
	createTrackbar("HighS2", "ControlGreen", &iHighS2, 255, on_track10);

	createTrackbar("LowV2", "ControlGreen", &iLowV2, 255, on_track11); //Value (0 - 255)
	createTrackbar("HighV2", "ControlGreen", &iHighV2, 255, on_track12);

	Mat imgThresholded1;
	Mat imgThresholded2;

	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(iHighH1, iHighS1, iHighV1), imgThresholded1); //二值化图像
	inRange(imgHSV, Scalar(iLowH2, iLowS2, iLowV2), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded2);

	medianBlur(imgThresholded1, imgThresholded1, 7);    //中值滤波
	medianBlur(imgThresholded2, imgThresholded2, 7);    //中值滤波

	//开操作 (去除一些噪点)
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded1, imgThresholded1, MORPH_OPEN, element);
	morphologyEx(imgThresholded2, imgThresholded2, MORPH_OPEN, element);

	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded1, imgThresholded1, MORPH_CLOSE, element);
	morphologyEx(imgThresholded2, imgThresholded2, MORPH_CLOSE, element);
	////均值滤波
	blur(imgThresholded1, imgThresholded1, Size(3, 3));
	blur(imgThresholded2, imgThresholded2, Size(3, 3));
	
	Mat canny1, canny2;
	Canny(imgThresholded1, canny1, 50, 150);
	imshow("Canny1", canny1);
	Canny(imgThresholded2, canny2, 50, 150);
	imshow("Canny2", canny2);

	vector<vector<Point>> contours1, contours2;
	vector<Vec4i> hierarchy1, hierarchy2;
	findContours(canny1, contours1, hierarchy1, RETR_TREE, CHAIN_APPROX_NONE, Point());
	findContours(canny2, contours2, hierarchy2, RETR_TREE, CHAIN_APPROX_NONE, Point());

	// 蓝色色块轮廓的绘制
	vector<Moments> mu1(contours1.size());    //计算轮廓矩  
	for (int i = 0; i < contours1.size(); i++)
	{
		mu1[i] = moments(contours1[i], false);
	}
	vector<Point2f>  mc1(contours1.size());    //计算轮廓中心
	for (int i = 0; i < contours1.size(); i++)
	{
		mc1[i] = Point2f(mu1[i].m10 / mu1[i].m00, mu1[i].m01 / mu1[i].m00);
	}
	//画轮廓及其质心并显示  
	for (int i = 0; i < contours1.size(); i++)
	{
		drawContours(imgOriginal, contours1, i, Scalar(0, 0, 255), 2, 8, hierarchy1, 0, Point());      //绘制轮廓
		//circle(imgOriginal, mc1[i], 15, Scalar(255, 255, 255), -1, 6, 0);      //画中心圆
	}

	// 绿色色块轮廓的绘制
	vector<Moments> mu2(contours2.size());    //计算轮廓矩  
	for (int i = 0; i < contours2.size(); i++)
	{
		mu1[i] = moments(contours2[i], false);
	}
	vector<Point2f>  mc2(contours2.size());    //计算轮廓中心
	for (int i = 0; i < contours2.size(); i++)
	{
		mc2[i] = Point2f(mu2[i].m10 / mu2[i].m00, mu2[i].m01 / mu2[i].m00);
	}
	//画轮廓及其质心并显示  
	for (int i = 0; i < contours2.size(); i++)
	{
		drawContours(imgOriginal, contours2, i, Scalar(0, 0, 255), 2, 8, hierarchy2, 0, Point());      //绘制轮廓
		//circle(imgOriginal, mc2[i], 15, Scalar(255, 255, 255), -1, 6, 0);      //画中心圆
	}


	imshow("Blue Thresholded1 Image", imgThresholded1); //show the thresholded image
	imshow("Green Thresholded2 Image", imgThresholded2);
	imshow("Original", imgOriginal); //show the original image

	waitKey(0);
	return 0;

}


void on_track1(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(value, iLowS1, iLowV1), Scalar(iHighH1, iHighS1, iHighV1), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的蓝色色块识别", imgThresholded);
}
void on_track2(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, value, iLowV1), Scalar(iHighH1, iHighS1, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的蓝色色块识别", imgThresholded);
}
void on_track3(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, value), Scalar(iHighH1, iHighS1, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的蓝色色块识别", imgThresholded);
}
void on_track4(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(value, iHighS1, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的蓝色色块识别", imgThresholded);
}
void on_track5(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(iHighH1, value, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的蓝色色块识别", imgThresholded);
}
void on_track6(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(iHighH1, iHighS1, value), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的蓝色色块识别", imgThresholded);
}
void on_track7(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(value, iLowS2, iLowV2), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的绿色色块识别", imgThresholded);
}
void on_track8(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, value, iLowV2), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的绿色色块识别", imgThresholded);
}
void on_track9(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, value), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的绿色色块识别", imgThresholded);
}
void on_track10(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, iLowV2), Scalar(value, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的绿色色块识别", imgThresholded);
}
void on_track11(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, iLowV2), Scalar(iHighH2, value, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的绿色色块识别", imgThresholded);
}
void on_track12(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, iLowV2), Scalar(iHighH2, iHighS2, value), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//闭操作 (连接一些连通域)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("变化中的绿色色块识别", imgThresholded);
}
