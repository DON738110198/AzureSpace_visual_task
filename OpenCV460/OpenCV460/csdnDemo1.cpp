//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace std;
//using namespace cv;
//
//int main(void)
//{
//	Mat srcImg, dstImg;
//	srcImg = imread("C:/Users/wh/Pictures/Saved Pictures/641ec3a574e9cc538c9fd1df08337c35bf43ce73.jpg@518w.jpg");
//	if (!srcImg.data)
//	{
//		cout << "can not load image.." << endl;
//		return -1;
//	}
//	namedWindow("����", WINDOW_NORMAL);
//	imshow("����", srcImg);
//
//	/************************ʾ��һ*************************/
//	/*
//	// ������һ����Դͼ���С��ͼ������һ����Mat���󣬵���û��ֵ
//	//dstImg = Mat(srcImg.size(), srcImg.type());
//	dstImg.create(srcImg.size(), srcImg.type());
//	// ��Mat��������һ����ɫֵ
//	dstImg = Scalar(125, 125, 125);
//	*/
//
//	/************************ʾ����*************************/
//	/*
//	// ����һ��3ͨ����100*100���ص�Mat����ÿ�����ص��BGR��(0, 0, 255)
//	// ����һ������
//	// ������������
//	// ��������CV_8UC3��8��ʾÿ��ͨ��ռ8λ��U��ʾ�޷��š�C��ʾchar���͡�3��ʾͨ����Ŀ��3
//	// �����ģ���������ʾ��ʼ��ÿ������ֵ�Ƕ��٣��������ȶ�Ӧͨ����Ŀ
//	//Mat mat(100, 100, CV_8UC1, Scalar(255));
//	Mat mat(100, 100, CV_8UC3, Scalar(0, 0, 255));
//	namedWindow("�������");
//	imshow("�������", mat);
//	*/
//
//	/************************ʾ����*************************/
//	/*
//	// ��¡һ��Mat����������ȫ����
//	dstImg = srcImg.clone();
//	*/
//
//	/************************ʾ����*************************/
//	/*
//	// ����һ��Mat����
//	srcImg.copyTo(dstImg);
//	*/
//
//	/************************ʾ����*************************/
//	// ��ͼ��ת��Ϊ��ɫͼ��
//	cvtColor(srcImg, dstImg, COLOR_BGR2GRAY);
//
//	/************************ʾ����*************************/
//	// ��ȡͼ��ͨ����
//	cout << "srcImg channels��" << srcImg.channels() << endl;
//	cout << "dstImg channels��" << dstImg.channels() << endl;
//
//	/************************ʾ����*************************/
//	// ��ȡͼ���һ�е�����ֵ
//	const uchar* pFirstRow = dstImg.ptr<uchar>(0);
//	cout << "dstImg first pixel value��" << *pFirstRow << endl;
//
//	/************************ʾ����*************************/
//	// ��ȡͼ�������������
//	cout << "dstImg rows��" << srcImg.rows << endl;
//	cout << "dstImg clos��" << srcImg.cols << endl;
//
//	/************************ʾ����*************************/
//	// ����һ��3*3��Mat����
//	Mat kernel = (Mat_<uchar>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//	cout << endl << kernel << endl;
//
//	/************************ʾ��ʮ*************************/
//	// ��ʼ��һ����Դͼ���С������һ�µĴ���ɫ����
//	Mat mat = Mat::zeros(srcImg.size(), srcImg.type());
//
//	/************************ʾ��ʮһ*************************/
//	// ��ʼ��һ����ͨ����2*2�Ĵ���ɫ����
//	//Mat mat2 = Mat::zeros(2, 2, CV_8UC1);
//	// ��ʼ��һ����ͨ����2*2���۾�����
//	Mat mat2 = Mat::eye(2, 2, CV_8UC1);
//	cout << endl << mat2 << endl;
//
//
//	namedWindow("�������", WINDOW_AUTOSIZE);
//	imshow("�������", dstImg);
//	waitKey(0);
//
//	return 0;
//}
