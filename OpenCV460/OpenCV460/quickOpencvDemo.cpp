#include <quickOpencv.h>
void QuickDemo::colorSpace_Demo(Mat& image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("灰度", gray);
	imwrite("D:/Project/photo/OpenCVPhotos/hsv1.png", hsv);
	imwrite("D:/Project/photo/OpenCVPhotos/gray1.png", gray);
}

void QuickDemo::mat_creation_demo(Mat& image) {
	// 除此之外还有就是，Mat类型如果只是用=来赋值，就不会创建新的区域，就是说两个变量还是指向同一块区域，但是用clone()、copyto()这些来复制就会创建一块新的区域
	Mat m1 = Mat::zeros(Size(4, 4), CV_8UC3);
	m1 += Scalar(40, 40, 40);
	std:: cout << m1;
	m1 += Scalar(555, 555, 555);
	std:: cout << m1;

	//正常来讲，加到数值到255这个上限时，不会自动取模，而是就停留在255这个上限了
	//用saturate_cast<uchar>(a + b)这个函数就可以自动对a+b的结果取模

}

void QuickDemo::pixel_visit_demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels(); // 判断image是几个channel的
	for (int row = 0; row < h; row++) {
		uchar* current_row = image.ptr<uchar>(row); // 直接就通过指针对每个像素进行修改了
		for (int col = 0; col < w; col++) {
			if (dims == 1) { // 灰度图像
				*current_row++ = 255 - *current_row;
			}
			if (dims == 3) { // 彩色图像
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("像素读写演示", image);
}

void QuickDemo::operators_demo(Mat& image) {
	Mat dst; // 最终要显示的
	Mat m = Mat::zeros(image.size(), image.type());
	//dst = image * 2; 像这样直接×就可以了
	// 
	//dst = image + 50; 像这样直接加也可以，不一定要用Scalar
	// 
	//m = Scalar(2, 7, 5); // 但是这样写的好处就是可以调整不同channel要×的倍数
	//multiply(image, m, dst);// 前两个参数相乘的结果会赋值给第三个参数

	dst = image + 244;
	imshow("运算符运算后的图像", dst);
}

static void on_track(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b); // b即为每次调用这个回调函数时image的亮度
	add(image, m, dst);
	imshow("亮度调整", dst);
}

void QuickDemo:: tracking_bar_demo(Mat& image) {
	namedWindow("亮度调整", WINDOW_AUTOSIZE);
	int max_value = 100;
	int lightness = 50;
	createTrackbar("Value Bar", "亮度调整", &lightness, max_value, on_track, (void*)(&image)); // 每次将初始增加的亮度lightness传入，最大的增加的亮度传入，回调函数，要调整亮度的图像
}

void QuickDemo::convertToDemo(Mat& image) {
	Mat m = Mat::zeros(image.size(), image.type());
	// depth 的值为0-6，输出会得到预定义的这0-6数字，而不是你想的深度，比如说8位、16位
	//#define CV_8U   0
	//#define CV_8S   1
	//#define CV_16U  2
	//#define CV_16S  3
	//#define CV_32S  4
	//#define CV_32F  5
	//#define CV_64F  6
	//#define CV_USRTYPE1 7
	//而对应的type(),如果是1通道，则在depth上+0，2通道则depth+8，3通道则depth+16

	std::cout << m.type() << " " << m.depth() << " " << m.channels() << " " << m.dims << " " << m.elemSize() << std::endl;
	std::cout << image.type() << " " << image.depth() << " " << image.channels() << " " << image.dims << " " << image.elemSize() << std::endl;
	m.convertTo(image,CV_8UC1);
	std::cout << m.type() << " " << m.depth() << " " << m.channels() << " " << m.dims << " " << m.elemSize() << std::endl;
	std::cout << image.type() << " " << image.depth() << " " << image.channels() << " " << image.dims << " " << image.elemSize() << std::endl;

	//std::cout << m;
}