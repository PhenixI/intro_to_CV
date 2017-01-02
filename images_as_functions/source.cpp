#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
using namespace std;
using namespace cv;

void generateGaussianNoise(Mat input) {
	Mat my_noise;
	my_noise = Mat(input.size(), input.type());

	randn(my_noise, 0, 5);

	input += my_noise;

	imshow("Gaussian Noise",input);
}
int main()
{
	Mat im = imread("D:\\1.jpg",IMREAD_GRAYSCALE);
	Mat im2 = imread("D:\\2.jpg", IMREAD_GRAYSCALE);

	float alpha = 0.7;

	//Mat dst;
	//addWeighted(im, alpha, im2, 1.0 - alpha, 0.0, dst);
	//imshow("blend",dst);
	imshow("sample", im);

	generateGaussianNoise(im);

	printf("width:%d,height:%d\n", im.cols, im.rows);
	cout << typeid(im).name() << endl;

	//for (int i = 101; i <= 103; i++)
	//	for (int j = 201; j <= 203; j++)
	//		cout << (int)im.at<uchar>(i, j) << endl;

	waitKey(0);

	Mat im_color = imread("D:\\1.jpg");
	imshow("sample color", im_color);
	cout << size(im) << endl;

	vector<cv::Mat> lab_channels;
	split(im_color, lab_channels);

	Mat im_green = lab_channels[1];
	imshow("green channel", im_green);

	waitKey(0);

}