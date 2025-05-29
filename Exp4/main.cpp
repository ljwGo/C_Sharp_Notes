#include <iostream>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main(void) {

	Mat src = imread("lenaColor.jpg", IMREAD_COLOR);

	if (src.empty()) {
		cout << "图片读取错误!" << endl;
		return -1;
	}

	imshow("src", src);

	// 分离出R、G、B三个通道图像，分别采用直方图均衡化处理，分别显示，然后再合并为一张图像保存
	//vector<Mat> bgr;
	//split(src, bgr);

	//Mat equalizeR, equalizeG, equalizeB;
	//equalizeHist(bgr[0], equalizeB);
	//equalizeHist(bgr[1], equalizeG);
	//equalizeHist(bgr[2], equalizeR);

	//imshow("b", bgr[0]);
	//imshow("g", bgr[1]);
	//imshow("r", bgr[2]);

	//imshow("equalizeB", equalizeB);
	//imshow("equalizeG", equalizeG);
	//imshow("equalizeR", equalizeR);

	//const Mat channels[]{ equalizeB, equalizeG, equalizeR };
	//Mat mergeImg;
	//merge(channels, 3, mergeImg);

	//imshow("mergeImg", mergeImg);

	// 分离为H、S、V三个通道图像，分别采用平滑滤波处理，分别显示，且合并为一张图像保存
	/*Mat hsvImg;
	cvtColor(src, hsvImg, COLOR_BGR2HSV);

	vector<Mat> hsv;
	split(hsvImg, hsv);

	Mat blurH, blurS, blurV;
	blur(hsv[0], blurH, Size(5, 5));
	blur(hsv[1], blurS, Size(5, 5));
	blur(hsv[2], blurV, Size(5, 5));

	imshow("h", hsv[0]);
	imshow("s", hsv[1]);
	imshow("v", hsv[2]);

	imshow("blurH", blurH);
	imshow("blurS", blurS);
	imshow("blurV", blurV);

	const Mat hsvChannels[]{ blurH, blurS, blurV };
	Mat hsvMergeImg;
	merge(hsvChannels, 3, hsvMergeImg);

	Mat blurHsv2BgrImg;
	cvtColor(hsvMergeImg, blurHsv2BgrImg, COLOR_HSV2BGR);
	
	imshow("hsvMergeImg", hsvMergeImg);
	imshow("hsv2bgr", blurHsv2BgrImg);*/
	
	// 伪彩色图片
	Mat graySrc = imread("lenagray.jpg", IMREAD_GRAYSCALE);
	
	if (graySrc.empty()) {
		cout << "灰度图片读取错误!" << endl;
		return -1;
	}

	imshow("graySrc", graySrc);

	// 构建RGB图片
	Mat imgPseudocolor(graySrc.rows, graySrc.cols, CV_8UC3);
	for (int x = 0; x < graySrc.rows; ++x) {
		for (int y = 0; y < graySrc.cols; ++y) {
			int grayValue = graySrc.at<uchar>(x, y);

			imgPseudocolor.at<Vec3b>(x, y)[0] = abs(255 - grayValue);
			imgPseudocolor.at<Vec3b>(x, y)[1] = abs(177 - grayValue);
			imgPseudocolor.at<Vec3b>(x, y)[2] = abs(grayValue);
		}
	}

	imshow("imgPseudocolor", imgPseudocolor);

	waitKey();
	return 0;
}
