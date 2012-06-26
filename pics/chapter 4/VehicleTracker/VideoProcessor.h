#pragma once
#include "opencv2/opencv.hpp"
#include "FrameProcessor.h"

class VideoProcessor
{
	private:
		char* videoPath;
		char* windowName;		
		cv::Mat in, out;
		cv::VideoCapture capture;

	public:
		VideoProcessor(char* videoPath);	
		~VideoProcessor(void);
	
		void run(FrameProcessor* frameProcessor);
};

