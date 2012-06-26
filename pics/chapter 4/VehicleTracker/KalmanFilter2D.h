#pragma once

#include <opencv2\opencv.hpp>
#include <memory>
#include "Blob.h"
#include <math.h>

using namespace cv;
using namespace std;

struct KalmanInput2D
{
	Rect rect;
};

struct KalmanResult2D
{
	float centerX;
	float centerY;

	float width;
	float height;

	float vx;
	float vy;

	float wx;
	float wy;

	Rect asRect() const
	{		
		Rect r(centerX - width/2, centerY - height/2, width, height);
		return r;
	}
};

class KalmanFilter2D
{
private:
	KalmanFilter filter;
	cv::Mat_<float> measurement;
	int width;
	int height;
	void mapMatToResult(const Mat& m, KalmanResult2D& result);
public:
	KalmanFilter2D();
	~KalmanFilter2D(){}

	void init(KalmanInput2D& input);
	KalmanResult2D lastState;

	KalmanResult2D predict();
	KalmanResult2D correct(KalmanInput2D& input);
	KalmanResult2D update(KalmanInput2D& input);	
};

