#pragma once
#include <map>
#include "TrackMatcher.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class NccMatcher:public TrackMatcher
{
public:
	NccMatcher(){TrackMatcher::goodMaxDist = 3000;};
	~NccMatcher(){};
	
	float match( track& tr, detection& dt, Mat& frame );

	float distance( track& tr, Mat& region );

	float distance( track& tr, Mat& region, Mat& descriptor );

	void inferModel( track& tr, detection& dt, Mat& frame );
};

