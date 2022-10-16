#include <iostream>
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// ���HSVͼ��ҪΪȫ�ֱ���
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

// ����ͨ��TrackBar����HSVֵ��Ļص�����
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
	Mat imgOriginal = imread("C:/Users/wh/Desktop/Vision_Group_Guidelines-main/ɫ��ʶ��/tag.png");

	if (imgOriginal.empty())  // if not success, exit program
	{
		cout << "��ȡͼƬʧ��" << endl;
		return -1;
	}

	vector<Mat> hsvSplit;
	cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //��ͼƬ��BGR��ʽת��ΪHSV��ʽ

	//��Ϊ���Ƕ�ȡ���ǲ�ɫͼ��ֱ��ͼ���⻯��Ҫ��HSV�ռ���
	split(imgHSV, hsvSplit); // ����ͨ������õ�������ͨ����ͼ�����
	equalizeHist(hsvSplit[2], hsvSplit[2]);
	merge(hsvSplit, imgHSV);

	//��Ҫ����һ����̬����HSVֵ�Ŀ���̨������HSVֵ���ҵ�Ч����õ�ֵ,���������Ѿ��ҳ�����Ϊ���ʵ�HSV������ֵ�ˣ�����������ܾͱ����ţ�����û��̫����ô���
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

	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(iHighH1, iHighS1, iHighV1), imgThresholded1); //��ֵ��ͼ��
	inRange(imgHSV, Scalar(iLowH2, iLowS2, iLowV2), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded2);

	medianBlur(imgThresholded1, imgThresholded1, 7);    //��ֵ�˲�
	medianBlur(imgThresholded2, imgThresholded2, 7);    //��ֵ�˲�

	//������ (ȥ��һЩ���)
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded1, imgThresholded1, MORPH_OPEN, element);
	morphologyEx(imgThresholded2, imgThresholded2, MORPH_OPEN, element);

	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded1, imgThresholded1, MORPH_CLOSE, element);
	morphologyEx(imgThresholded2, imgThresholded2, MORPH_CLOSE, element);
	////��ֵ�˲�
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

	// ��ɫɫ�������Ļ���
	vector<Moments> mu1(contours1.size());    //����������  
	for (int i = 0; i < contours1.size(); i++)
	{
		mu1[i] = moments(contours1[i], false);
	}
	vector<Point2f>  mc1(contours1.size());    //������������
	for (int i = 0; i < contours1.size(); i++)
	{
		mc1[i] = Point2f(mu1[i].m10 / mu1[i].m00, mu1[i].m01 / mu1[i].m00);
	}
	//�������������Ĳ���ʾ  
	for (int i = 0; i < contours1.size(); i++)
	{
		drawContours(imgOriginal, contours1, i, Scalar(0, 0, 255), 2, 8, hierarchy1, 0, Point());      //��������
		//circle(imgOriginal, mc1[i], 15, Scalar(255, 255, 255), -1, 6, 0);      //������Բ
	}

	// ��ɫɫ�������Ļ���
	vector<Moments> mu2(contours2.size());    //����������  
	for (int i = 0; i < contours2.size(); i++)
	{
		mu1[i] = moments(contours2[i], false);
	}
	vector<Point2f>  mc2(contours2.size());    //������������
	for (int i = 0; i < contours2.size(); i++)
	{
		mc2[i] = Point2f(mu2[i].m10 / mu2[i].m00, mu2[i].m01 / mu2[i].m00);
	}
	//�������������Ĳ���ʾ  
	for (int i = 0; i < contours2.size(); i++)
	{
		drawContours(imgOriginal, contours2, i, Scalar(0, 0, 255), 2, 8, hierarchy2, 0, Point());      //��������
		//circle(imgOriginal, mc2[i], 15, Scalar(255, 255, 255), -1, 6, 0);      //������Բ
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
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track2(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, value, iLowV1), Scalar(iHighH1, iHighS1, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track3(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, value), Scalar(iHighH1, iHighS1, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track4(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(value, iHighS1, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track5(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(iHighH1, value, iHighV1), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track6(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS1, iLowV1), Scalar(iHighH1, iHighS1, value), imgThresholded);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track7(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(value, iLowS2, iLowV2), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track8(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, value, iLowV2), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track9(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, value), Scalar(iHighH2, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track10(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, iLowV2), Scalar(value, iHighS2, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track11(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, iLowV2), Scalar(iHighH2, value, iHighV2), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}
void on_track12(int value, void* userdata) {
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH1, iLowS2, iLowV2), Scalar(iHighH2, iHighS2, value), imgThresholded); //
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(imgThresholded, imgThresholded, MORPH_OPEN, element);
	//�ղ��� (����һЩ��ͨ��)
	morphologyEx(imgThresholded, imgThresholded, MORPH_CLOSE, element);
	imshow("�仯�е���ɫɫ��ʶ��", imgThresholded);
}