#include "Matcher2D.h"
#include <opencv2/opencv.hpp>

using namespace cv;

float Matcher2D::match( track& tr, detection& dt, Mat& frame )
{

	cv::Rect rects[2] = {tr.asRecti(), dt.rect};	
	int min;
	if(tr.asRecti().area() < dt.rect.area())
		min = 0;
	else 
		min = 1;

	int minArea = 0.5 * rects[min].area();

	Rect intersection = tr.asRecti() & dt.rect;
	int area = intersection.area();

	if(area > minArea)
		return (float)area;

	return -1;
}

void Matcher2D::inferModel( track& tr, detection& dt, Mat& frame )
{
	tr.assign(dt.rect);
}
