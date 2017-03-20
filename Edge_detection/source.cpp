#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main_sobel(int, char**)
{
	Mat src, src_gray;
	Mat grad;

	const char* window_name = "Sobel Demo - Simple Edge Detector";
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	src = imread("D:\\material\\Dataset\\1.jpg", IMREAD_COLOR);
	if (src.empty())
	{	return -1;}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Scharr(src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT);
	Scharr(src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT);

	//Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	//Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);

	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	imshow(window_name, grad);
	waitKey(0);

	return 0;
}

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const char* window_name = "Edge Map";

static void CannyThreshold(int, void*) {
	blur(src_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);
}
int main(int, char** argv)
{
	src = imread("D:\\material\\Dataset\\2.jpg", IMREAD_COLOR);
    if(src.empty())
	{return -1;}

	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold: ", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	CannyThreshold(0, 0);
	waitKey(0);

	return 0;
}