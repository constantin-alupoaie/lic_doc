#pragma once
#include <agents.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace Concurrency;

class PVideoReader: public agent
{
private:
	char* _videoPath;
	ISource<int>& _syncBuffer;
	ITarget<Mat>& _subtractorBuffer;
	ITarget<Mat>& _classifierBuffer;

public:
	PVideoReader(char* path, ITarget<Mat>& outBuffer0, ITarget<Mat>& outBuffer1 ,ISource<int>& syncBuffer)
		:_videoPath(path),
		_syncBuffer(syncBuffer),
		_subtractorBuffer(outBuffer0),
		_classifierBuffer(outBuffer1)
	{}	

	virtual void run();
};

