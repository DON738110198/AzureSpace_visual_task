#include <quickOpencv.h>
void QuickDemo::colorSpace_Demo(Mat& image) {
	Mat gray, hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("HSV", hsv);
	imshow("�Ҷ�", gray);
	imwrite("D:/Project/photo/OpenCVPhotos/hsv1.png", hsv);
	imwrite("D:/Project/photo/OpenCVPhotos/gray1.png", gray);
}

void QuickDemo::mat_creation_demo(Mat& image) {
	// ����֮�⻹�о��ǣ�Mat�������ֻ����=����ֵ���Ͳ��ᴴ���µ����򣬾���˵������������ָ��ͬһ�����򣬵�����clone()��copyto()��Щ�����ƾͻᴴ��һ���µ�����
	Mat m1 = Mat::zeros(Size(4, 4), CV_8UC3);
	m1 += Scalar(40, 40, 40);
	std:: cout << m1;
	m1 += Scalar(555, 555, 555);
	std:: cout << m1;

	//�����������ӵ���ֵ��255�������ʱ�������Զ�ȡģ�����Ǿ�ͣ����255���������
	//��saturate_cast<uchar>(a + b)��������Ϳ����Զ���a+b�Ľ��ȡģ

}

void QuickDemo::pixel_visit_demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels(); // �ж�image�Ǽ���channel��
	for (int row = 0; row < h; row++) {
		uchar* current_row = image.ptr<uchar>(row); // ֱ�Ӿ�ͨ��ָ���ÿ�����ؽ����޸���
		for (int col = 0; col < w; col++) {
			if (dims == 1) { // �Ҷ�ͼ��
				*current_row++ = 255 - *current_row;
			}
			if (dims == 3) { // ��ɫͼ��
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("���ض�д��ʾ", image);
}

void QuickDemo::operators_demo(Mat& image) {
	Mat dst; // ����Ҫ��ʾ��
	Mat m = Mat::zeros(image.size(), image.type());
	//dst = image * 2; ������ֱ�ӡ��Ϳ�����
	// 
	//dst = image + 50; ������ֱ�Ӽ�Ҳ���ԣ���һ��Ҫ��Scalar
	// 
	//m = Scalar(2, 7, 5); // ��������д�ĺô����ǿ��Ե�����ͬchannelҪ���ı���
	//multiply(image, m, dst);// ǰ����������˵Ľ���ḳֵ������������

	dst = image + 244;
	imshow("�����������ͼ��", dst);
}

static void on_track(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b); // b��Ϊÿ�ε�������ص�����ʱimage������
	add(image, m, dst);
	imshow("���ȵ���", dst);
}

void QuickDemo:: tracking_bar_demo(Mat& image) {
	namedWindow("���ȵ���", WINDOW_AUTOSIZE);
	int max_value = 100;
	int lightness = 50;
	createTrackbar("Value Bar", "���ȵ���", &lightness, max_value, on_track, (void*)(&image)); // ÿ�ν���ʼ���ӵ�����lightness���룬�������ӵ����ȴ��룬�ص�������Ҫ�������ȵ�ͼ��
}

void QuickDemo::convertToDemo(Mat& image) {
	Mat m = Mat::zeros(image.size(), image.type());
	// depth ��ֵΪ0-6�������õ�Ԥ�������0-6���֣��������������ȣ�����˵8λ��16λ
	//#define CV_8U   0
	//#define CV_8S   1
	//#define CV_16U  2
	//#define CV_16S  3
	//#define CV_32S  4
	//#define CV_32F  5
	//#define CV_64F  6
	//#define CV_USRTYPE1 7
	//����Ӧ��type(),�����1ͨ��������depth��+0��2ͨ����depth+8��3ͨ����depth+16

	std::cout << m.type() << " " << m.depth() << " " << m.channels() << " " << m.dims << " " << m.elemSize() << std::endl;
	std::cout << image.type() << " " << image.depth() << " " << image.channels() << " " << image.dims << " " << image.elemSize() << std::endl;
	m.convertTo(image,CV_8UC1);
	std::cout << m.type() << " " << m.depth() << " " << m.channels() << " " << m.dims << " " << m.elemSize() << std::endl;
	std::cout << image.type() << " " << image.depth() << " " << image.channels() << " " << image.dims << " " << image.elemSize() << std::endl;

	//std::cout << m;
}