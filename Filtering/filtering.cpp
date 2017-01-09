#include "opencv2\imgcodecs.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
using namespace std;
using namespace cv;

int main()
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