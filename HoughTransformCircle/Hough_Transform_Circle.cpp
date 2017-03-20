#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

//windows and trackbars name
const std::string windowName = "Hough Circle Detection Demo";
const std::string cannyThresholdTrackbarName = "Canny threshold";
const std::string accumulatorThresholdTrackbarName = "Accumulator Threshold";

//initial and max value of the parameters of interests
const int cannyThresholdInitialValue = 200;
const int accumulatorThresholdInitialValue = 50;
const int maxAccumulatorThreshold = 200;
const int maxCannyThreshold = 255;

void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
{
	// will hold the results of the detection
	std::vector<Vec3f> circles;

	HoughCircles(src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows / 8, cannyThreshold, accumulatorThreshold, 0, 0);


	//Clone the color, input image for displaying purposes
	Mat display = src_display.clone();
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		//circle center 
		circle(display, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(display, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	imshow(windowName, display);
}

int main(int argc, char** argv)
{
	Mat src, src_gray;
	src = imread("D:\\material\\Dataset\\stuff.jpg", IMREAD_COLOR);
	if (src.empty())
	{
		std::cerr << "Invalid input Image\n";
		return -1;
	}

	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	//declare and initialize both parameters that are subjects to change
	int cannyThreshold = cannyThresholdInitialValue;
	int accumulatorThreshold = accumulatorThresholdInitialValue;

	//create the main window, and attach the trackbars
	namedWindow(windowName, WINDOW_AUTOSIZE);
	createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold, maxCannyThreshold);
	createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);

	//infinite loop to display
	//and refresh the content of the output image
	//until the user presses q or Q
	char key = 0;
	while (key != 'q' && key != 'Q')
	{
		cannyThreshold = std::max(cannyThreshold, 1);
		accumulatorThreshold = std::max(accumulatorThreshold, 1);

		//runs the detection, and update the dispaly
		HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

		key = (char)waitKey(10);
	}
	return 0;

}