#include "opencv2/opencv.hpp"
#include "opencv2//highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

//to sort -insertion sort algo
void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

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


	Mat gray(height, width, CV_8UC1, Scalar(0));
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat output = gray.clone();

	//to get kernel size from command line
	int k = atoi(argv[2]);
	int adj= k/2;
	// put adj as  - ,+ in the loop sizes


	//needs for the below loop
	int size = k*k;
	int* arr = new int[size];
	int index;
	int middle;

	//looping image
	for (int i = adj; i < height - adj; i++) {
		for (int j = adj; j < width - adj; j++) {
			index = 0;
			// loop through kernel
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					
					arr[index] = (int)gray.at<uchar>(g, h);
					index++;
				}
			}
			
			//to sort the array - insertion sorting - code at the begininng
			//call sort function
			
			insertionSort(arr, size);

			//find middle value
			middle = size / 2;
			output.at<uchar>(i, j) = (uchar)arr[middle];
		}
	}

	


	namedWindow("Gray");
	imshow("Gray", gray);
	namedWindow("Output");
	imshow("Output", output);

	imwrite("medianFilter.jpg", output);
	waitKey(0);
	return 0;





}