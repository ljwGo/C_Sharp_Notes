#include <iostream>
#include <string.h>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;

void HelloOpenCV(std::string path) {
	// 读入一张图片
	Mat img = imread(path);
	if (img.empty())
		return;
	// 在窗口中显示图片   	
	imshow("图片", img);
	// 等待6000ms后窗口自动关闭
	waitKey(6000);
}

void PrintResolutionInfo(const Mat& img){
	if (img.empty())
		return;
	cout << "图片通道数: " << img.channels() << endl;
	cout << "图片分辨率为: " << img.rows << "*" << img.cols << endl;
}

void PrintRegionPixelValue(const Mat& img, const Point2i pos, const Vec2i size) {
	if (img.empty())
		return;

	cout << "区域的像素值为: " << endl;
	for (int i = pos.x; i < pos.x + size[0]; ++i) {
		if (i >= img.rows)
			continue;
		const uchar* p = img.ptr<uchar>(i);

		for (int j = pos.y; j < pos.y + size[1]; ++j) {
			if (j >= img.cols)
				continue;
			cout << (int)p[j] << " ";
		}
		cout << endl;
	}
}

Mat Resize(const Mat& img, const Vec2d scale) {
	Size size(0, 0);
	Mat toImg;
	//Must include opencv.hpp and you can use resize
	resize(img, toImg, size, scale[0], scale[1]);
	return toImg;
}

Mat ModifyGrayLevel(const Mat& img, int originalLevel, int targetLevel, std::string path) {
	Mat newImg = img.clone();
	newImg.setTo(0);
	if (targetLevel >= originalLevel)
		return newImg;
	int originalColorCount = 1 << originalLevel;
	int targetColorCount = 1 << targetLevel;
	
	int regionSize = 1 << (originalLevel - targetLevel);
	int gradientSize = originalColorCount / (targetColorCount - 1);

	for (int i = 0; i < newImg.rows; ++i) {
		const uchar* p1 = img.ptr<uchar>(i);
		uchar* p2 = newImg.ptr<uchar>(i);

		//Please pay attention to the matrix of data has three channels(rgb).
		//So horizontal has thrid time cols lenth.(three elements represent one pixel)
		for (int j = 0; j < newImg.cols; ++j) {
			p2[j] = min(255, p1[j] / regionSize * gradientSize);
		}
	}

	imwrite(path, newImg);
	return newImg;
}

Mat DifferentImage(const Mat& leftMat, const Mat& rightMat) {
	Mat result;
	if (leftMat.empty() || rightMat.empty()) {
		return result;
	}
	
	result = leftMat - rightMat;
	return result;
}

int main() {
	//You need use IMREAD_GRAYSCALE flag to open gray image.
	//One value instead of three channels(rgb)
	//Mat img = imread("aaa.jpg", IMREAD_GRAYSCALE);

	//PrintResolutionInfo(img);
	//PrintRegionPixelValue(img, Point2i(300, 300), Vec2i(3, 3));
	//
	//Mat resizeImg;
	//resizeImg = std::move(Resize(img, Vec2d(0.5, 0.5)));
	//imshow("Origin Picture", img);
	//imshow("Resize Picture", resizeImg);

	//Mat gray_2 = ModifyGrayLevel(img, 8, 1, "gray_2.png");
	//Mat gray_4 = ModifyGrayLevel(img, 8, 2, "gray_4.png");
	//Mat gray_8 = ModifyGrayLevel(img, 8, 3, "gray_8.png");
	//Mat gray_16 = ModifyGrayLevel(img, 8, 4, "gray_16.png");
	//Mat gray_64 = ModifyGrayLevel(img, 8, 6, "gray_64.png");
	//Mat gray_128 = ModifyGrayLevel(img, 8, 7, "gray_128.png");

	Mat leftImg = imread("angiography_mask_image.tif", IMREAD_GRAYSCALE);
	Mat rightImg = imread("angiography_live_image.tif", IMREAD_GRAYSCALE);
	Mat result = DifferentImage(leftImg, rightImg);

	imshow("leftImg", leftImg);
	imshow("rightImg", rightImg);
	imshow("result", result);
	imwrite("angiography-difference.tif", result);

	waitKey(10000);
	return 0;
}