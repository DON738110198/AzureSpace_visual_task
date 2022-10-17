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
//	namedWindow("测试", WINDOW_NORMAL);
//	imshow("测试", srcImg);
//
//	/************************示例一*************************/
//	/*
//	// 创建了一个和源图像大小、图像类型一样的Mat对象，但是没有值
//	//dstImg = Mat(srcImg.size(), srcImg.type());
//	dstImg.create(srcImg.size(), srcImg.type());
//	// 给Mat对象设置一个颜色值
//	dstImg = Scalar(125, 125, 125);
//	*/
//
//	/************************示例二*************************/
//	/*
//	// 创建一个3通道的100*100像素的Mat对象，每个像素点的BGR是(0, 0, 255)
//	// 参数一：行数
//	// 参数二：列数
//	// 参数三：CV_8UC3中8表示每个通道占8位、U表示无符号、C表示char类型、3表示通道数目是3
//	// 参数四：向量，表示初始化每个像素值是多少，向量长度对应通道数目
//	//Mat mat(100, 100, CV_8UC1, Scalar(255));
//	Mat mat(100, 100, CV_8UC3, Scalar(0, 0, 255));
//	namedWindow("测试输出");
//	imshow("测试输出", mat);
//	*/
//
//	/************************示例三*************************/
//	/*
//	// 克隆一个Mat对象，数据完全拷贝
//	dstImg = srcImg.clone();
//	*/
//
//	/************************示例四*************************/
//	/*
//	// 拷贝一个Mat对象
//	srcImg.copyTo(dstImg);
//	*/
//
//	/************************示例五*************************/
//	// 将图像转换为灰色图像
//	cvtColor(srcImg, dstImg, COLOR_BGR2GRAY);
//
//	/************************示例六*************************/
//	// 获取图像通道数
//	cout << "srcImg channels：" << srcImg.channels() << endl;
//	cout << "dstImg channels：" << dstImg.channels() << endl;
//
//	/************************示例七*************************/
//	// 获取图像第一行的像素值
//	const uchar* pFirstRow = dstImg.ptr<uchar>(0);
//	cout << "dstImg first pixel value：" << *pFirstRow << endl;
//
//	/************************示例八*************************/
//	// 获取图像的行数和列数
//	cout << "dstImg rows：" << srcImg.rows << endl;
//	cout << "dstImg clos：" << srcImg.cols << endl;
//
//	/************************示例九*************************/
//	// 创建一个3*3的Mat数组
//	Mat kernel = (Mat_<uchar>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
//	cout << endl << kernel << endl;
//
//	/************************示例十*************************/
//	// 初始化一个和源图像大小、类型一致的纯黑色对象
//	Mat mat = Mat::zeros(srcImg.size(), srcImg.type());
//
//	/************************示例十一*************************/
//	// 初始化一个单通道的2*2的纯黑色对象
//	//Mat mat2 = Mat::zeros(2, 2, CV_8UC1);
//	// 初始化一个单通道的2*2的眼睛对象
//	Mat mat2 = Mat::eye(2, 2, CV_8UC1);
//	cout << endl << mat2 << endl;
//
//
//	namedWindow("测试输出", WINDOW_AUTOSIZE);
//	imshow("测试输出", dstImg);
//	waitKey(0);
//
//	return 0;
//}
