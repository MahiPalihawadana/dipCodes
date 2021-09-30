#include "opencv2/opencv.hpp"
#include "opencv2//highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;



int main(int argc, char* argv[]) {

	Mat img = imread(argv[1], IMREAD_GRAYSCALE);

	if (!img.data) {
		cout << "Could not find the image!" << endl;
		return -1;

	}

	//allocate memory location
	int histogram[256];
	double prob[256];
	double cprob[256];

	//initialized to 0
	for (int x=0; x < 256; x++) {
		histogram[x] = 0;
		prob[x] = 0.0;
		cprob[x] = 0.0;
	}

	//calculate no of pixels for each gray level
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			histogram[(int)img.at<uchar>(i, j)] = histogram[(int)img.at<uchar>(i, j)] + 1;
		}
	}
	// total no of pixels
	int N = img.rows * img.cols;

	//calcultate the probsbility of each gray levels
	for (int i=0; i < 256; i++) {
		prob[i] = (double)histogram[i] / N;
	}


	//generate cumulative probaability
	cprob[0] = prob[0];
	for (int i=1; i < 256; i++) {
		cprob[i] = cprob[i - 1] + prob[i];
	}


	for (int i = 0; i < 256; i++) {
		printf("%f ", cprob[i]);
	}

	namedWindow("Image");
	imshow("Image", img);



	waitKey(0);
	return 0;





}