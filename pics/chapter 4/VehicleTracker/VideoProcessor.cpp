#include "VideoProcessor.h"


VideoProcessor::VideoProcessor(char* videoPath)
{
	this->videoPath = videoPath;
	this->windowName = "Video Processor";
}

VideoProcessor::~VideoProcessor(){}


void VideoProcessor::run(FrameProcessor* frameProcessor )
{	
	
	this->capture.open(this->videoPath);
	if(!capture.isOpened())
	{
		capture.release();
		return;
	}

	double fps = capture.get(CV_CAP_PROP_FPS);		
	int delay = 1000.0/120.0;

	cv::namedWindow(this->windowName);
	cv::namedWindow(frameProcessor->windowName);

	bool stop = false;
	while(!stop){
		if(!capture.read(this->in)){
			break;
		}
		cv::imshow(this->windowName, this->in);
		
		frameProcessor->process(this->in, &this->out);
		cv::imshow(frameProcessor->windowName, this->out);

		if(cv::waitKey(delay)>=0){
			stop = true;
		}
	}

	capture.release();
}