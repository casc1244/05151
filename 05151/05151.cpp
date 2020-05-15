#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int gammaCorrection(cv::Mat srcMat, cv::Mat & dstMat, float gamma)
{

	//处理单通道图像
	if (srcMat.channels() != 1)return -1;
	//查询表
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		//，防止像素值溢出，如果值<0,则返回0，如果大于255，则返回255
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
		float inten = (float)i;
	}
   srcMat.copyTo(dstMat);

	MatIterator_<uchar> it, end;
	for (it = dstMat.begin<uchar>(), end = dstMat.end<uchar>(); it != end; it++) {
		*it = lut[(*it)];
	}

	return 0;
}
int gammaMain()
{

	cv::Mat srcMat = imread("D:\\360downloads\\21.jpg", 0);
	cv::Mat dstMat;

	if (srcMat.empty()) {
		cout << "fail" << endl;
		return -1;
	}
	float gamma = 0.5;
	gammaCorrection(srcMat, dstMat, gamma);

	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);

	destroyAllWindows();

	return 0;
}
int main()
{
	//计时
	double start = static_cast<double>(cvGetTickCount());
	//gamma矫正
	gammaMain();
   //结束计时
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//显示时间
	cout << "processing" << time / 1000 << "ms" << endl;

	//按任意键结束
	system("pause");
	return 0;
}