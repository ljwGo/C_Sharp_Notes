#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <string.h>
using namespace cv;
using namespace std;

void PrintRGBGrayPixelCount(const Mat& img, int grayCount) {
	int* counter = new int[grayCount]{0};

	for (int i = 0; i < img.rows; ++i) {
		const uchar* pRow = img.ptr<uchar>(i);
		for (int j = 0; j < img.cols; ++j) {
			counter[pRow[j]]++;
		}
	}

	int calcSum = 0;  // use to test

	cout << "开始统计各灰度值的像素数量" << endl;
	for (int k = 0; k < grayCount; ++k) {
		calcSum += counter[k]; 	// use to test
		cout << "灰度值为" << k << "，像素数量为：" << counter[k] << endl;
	}

	// use to test
	int sum = img.rows * img.cols;
	cout << "像素总数：" << calcSum << endl;
	cout << "结果总数和实际图片总数" << (calcSum == sum ? "符合" : "不符合");
}

Mat PowTransition(const Mat& img, float coefficient, float powCoe) {
	Mat newImg = img.clone();

	for (int i = 0; i < img.rows; ++i) {
		const uchar* pRow = img.ptr<uchar>(i);
		uchar* pNewRow = newImg.ptr<uchar>(i);

		for (int j = 0; j < img.cols; ++j) {
			pNewRow[j] = min(255.0, coefficient* pow(pRow[j], powCoe));
		}
	}

	return newImg;
}

void ShowHist(string imageName, const Mat & grayImg) {
	bool uniform = true, accumulate = false;
	
	Mat hist;
	int histSize = 256;
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };

	calcHist(&grayImg, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512, hist_h = 400;
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	int bin_w = cvRound(hist_w / (double)histSize);

	// normalize to limit value range
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 255, 255), 2, 8, 0);
	}

	imshow(imageName, histImage);
}

int main(void) {

	Mat img = imread("lenagray.jpg", IMREAD_GRAYSCALE);
	if (img.empty())
		return -1;
	///
	/// 实验3部分
	///

	// 计算灰度数量
	//PrintRGBGrayPixelCount(img, 256);

	// 图像幂变化
	//Mat newImg = PowTransition(img, 1, 1.05);
	//imshow("powImg", newImg);
	//imwrite("powImg.png", newImg);

	// 扩大和缩小图片
	//Mat bigImg = img.clone();
	//Mat smallImg = img.clone();
	//resize(img, smallImg, Size(0, 0), 0.8, 0.8);
	//resize(img, bigImg, Size(0, 0), 1.5, 1.5);

	//imshow("smallImg", smallImg);
	//imshow("bigImg", bigImg);

	// 均衡化equalize
	//Mat equalizeImg;
	//equalizeHist(img, equalizeImg);

	//imshow("srcImg", img);
	//imshow("equalizeImg", equalizeImg);

	//ShowHist("srcHistImg", img);
	//ShowHist("equalizeHistImg", equalizeImg);

	// 平均模糊
	//Mat dst3_3, dst7_7;
	//blur(img, dst3_3, Size(3, 3), Point(-1, -1));
	//blur(img, dst7_7, Size(7, 7), Point(-1, -1));
	//imshow("src", img);
	//imshow("3*3", dst3_3);
	//imshow("7*7", dst7_7);

	// 中值滤波
	Mat dstMedian3_3, dstMedian5_5;
	medianBlur(img, dstMedian3_3, 3);
	medianBlur(img, dstMedian5_5, 5);
	imshow("Median3*3", dstMedian3_3);
	imshow("Median5*5", dstMedian5_5);

	// 拉普拉斯锐化
	Mat laplacianDst;
	Laplacian(img, laplacianDst, CV_8U); //ddepth理解为单位像素需要的bit存储空间就好了

	imshow("laplacianDst", laplacianDst); // 图像边缘
	imshow("differentLaplacian", img - laplacianDst); // 锐化后的图像

	// Sobel梯度
	Mat sobelDst01, sobelDst02;
	Sobel(img, sobelDst01, CV_8U, 0, 1); //dx和dy不好理解
	Sobel(img, sobelDst02, CV_8U, 1, 0);

	imshow("sobelDst01", sobelDst01); // 图像边缘
	imshow("sobelDst02", sobelDst02); // 图像边缘
	imshow("differentSobel", img - sobelDst01); // 锐化后的图像

	waitKey();
	return 0;
}