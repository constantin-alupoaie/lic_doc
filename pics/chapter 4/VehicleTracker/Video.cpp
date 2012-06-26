#include "Video.h"

bool Video::openCapture( int& fps, double& frameDelay )
{
	this->capture.open(this->videoPath);
	if (!capture.isOpened())
	{
		capture.release();
		return false;
	}

	fps        = capture.get(CV_CAP_PROP_FPS);
	frameDelay = 1000.0 / (double)(fps);
	return true;
}

static const Rect crop = Rect(0,105, 480, 268);
bool Video::read( Mat& frame )
{
	frameCount++;
	if(capture.read(frame))
	{
		frame = frame(crop);
		return true;
	}		
	return false;
}

