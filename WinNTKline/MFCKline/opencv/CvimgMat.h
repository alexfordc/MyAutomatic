#pragma once
#include <iostream>
#include <vector>
#ifdef REAL
#undef REAL
#endif
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct CvimgMat {
	cv::Mat g_srcImage(const cv::String& img);
	int g_roiImage(const cv::String& bkg, const cv::String& mask, int threshval = 0);
	int g_limImage(cv::Mat imgSrc, const cv::String alphapng, int threshold = 16);
	int g_mixImage(const cv::String& img1, const cv::String& img2, double alpha);
	int g_bilImage(cv::Mat imgSrc, int bilateralval = 8);
	int g_medImage(cv::Mat imgSrc, int ksize = 3);
	int g_aveImage(cv::Mat imgSrc, cv::Size ksize= cv::Size(3, 3));
	int saveMat2PNG(int w, int h, const cv::String& name);
	int cvmat_test();
};