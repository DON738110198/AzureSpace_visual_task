#pragma once
# include <opencv2/opencv.hpp>
using namespace cv;
class QuickDemo {
public:
	void colorSpace_Demo(Mat& image);
	void mat_creation_demo(Mat& image);
	void pixel_visit_demo(Mat& image);// 对image这一Mat矩阵类型变量进行每一个像素的访问
	void operators_demo(Mat& image); // 对image进行运算操作
	void tracking_bar_demo(Mat& image); // 可视化调整图片亮度
	void convertToDemo(Mat& image); // convertTo 函数
};