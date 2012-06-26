#pragma once
#include <opencv2\opencv.hpp>

using namespace cv;

class Video
{
private:
	char* videoPath;	
	VideoCapture capture;
	
public:
	~Video(){};
	Video(char* pathToVideo):
		videoPath(pathToVideo),
		frameCount(0)
	{};

	long long frameCount;
	bool openCapture(int& fps, double& frameDelay);
	bool read(Mat& frame);	
};

