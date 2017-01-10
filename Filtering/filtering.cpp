#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
using namespace std;
using namespace cv;

int main_gaussianfilter()
{
	Mat im = imread("D:\\1.jpg", IMREAD_GRAYSCALE);
	imshow("Sample", im);

	//add noise
	Mat my_noise;
	my_noise = Mat(im.size(), im.type());
	randn(my_noise, 0, 21);
	im += my_noise;
	imshow("Sample with noise", im);

	//Gaussian Filter
	Mat dst;
	GaussianBlur(im, dst, Size(5,5), 3);

	imshow("Gaussian Filter", dst);
	waitKey(0);

	return 0;
}

//
int main_edge_filter()
{
	Mat im = imread("D:\\1.jpg", IMREAD_COLOR);
	imshow("Sample", im);

	//Gaussian Filter
	Mat dst;
	GaussianBlur(im, dst, Size(5, 5), 3, 3, BORDER_CONSTANT);

	imshow("Border_constant", dst);

	GaussianBlur(im, dst, Size(5, 5), 3, 3, BORDER_REFLECT);
	imshow("Border reflect", dst);

	GaussianBlur(im, dst, Size(5, 5), 3, 3, BORDER_REPLICATE);
	imshow("border replicate", dst);

	waitKey(0);

	return 0;
}

//median Filter
int main() {
	Mat im = imread("D:\\1.jpg", IMREAD_GRAYSCALE);
	imshow("Sample", im);

	//add salt & pepper noise
	Mat my_noise(im.size(), im.type());
	randu(my_noise, 0, 255);
	Mat black = my_noise < 30;
	Mat white = my_noise > 225;
	im.setTo(255, white);
	im.setTo(0, black);

	imshow("Salt && pepper noise", im);

	//Median Filter
	Mat dst;
	medianBlur(im, dst, 5);

	imshow("median filter", dst);

	waitKey(0);

	return 0;


}