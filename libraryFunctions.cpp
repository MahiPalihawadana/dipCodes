#include "opencv2/opencv.hpp"
#include "opencv2//highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;



int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], 1);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;

	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();

	//// turn to gray image
	Mat gr(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gr, COLOR_BGR2GRAY);

	//get a copy of the gray image
	Mat output = gr.clone();

	//Average Filter
	Mat avgFilter = img.clone();
	blur(img, avgFilter, Size(3, 3), Point(-1, -1), 4);

	//Median Filter
	Mat medianFilter = gr.clone();
	medianBlur(gr, medianFilter, 3);

	//Gaussian FIlter
	Mat gaussianFilter = gr.clone();
	GaussianBlur(gr, gaussianFilter, Size(3,3), (0, 0), 4);


	//binary thresholding
	/*Mat bThreshold = gr.clone();
	threshold(gaussianFilter, bThreshold, 90, 255, CV_THRESH_BINARY);*/

	//otsu
	Mat oThreshold = gr.clone();
	threshold(gaussianFilter, oThreshold, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU );

	/*namedWindow("Image");
	imshow("Image", img);
	namedWindow("Average Filter");
	imshow("Average Filter", avgFilter);
	imwrite("AverageFilter.jpg", avgFilter);

	namedWindow("Medain Filter");
	imshow("Median Filter", medianFilter);
	imwrite("MedianFilter.jpg", medianFilter);

	namedWindow("Gaussian Filter");
	imshow("Gaussian Filter", gaussianFilter);
	imwrite("GaussianFilter.jpg", gaussianFilter);*/

	/*namedWindow("binary threshold");
	imshow("Binary Threshold", bThreshold);
	imwrite("binaryThreshold.jpg", bThreshold);*/

	namedWindow("otsu threshold");
	imshow("otsu Threshold", oThreshold);
	imwrite("otsuThreshold.jpg", oThreshold);

	waitKey(0);
	return 0;

}