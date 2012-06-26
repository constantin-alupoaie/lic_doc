#pragma once
#include <agents.h>
#include "ClassifierBase.h"

using namespace Concurrency;

struct ClasifierFrame 
{
	vector<detection> detections;
};

class PClassifier : public agent
{
	int trainingFrames;
	ClassifierBase *classifier;
	ISource<Mat>& frameBuffer;
	ITarget<ClasifierFrame>& targetBuffer;	
			
public:	
	PClassifier(ClassifierBase *cls, ISource<Mat>& frameBuff, ITarget<ClasifierFrame>& targetBuff, int tframes) 
		:classifier(cls),
		frameBuffer(frameBuff),
		targetBuffer(targetBuff),		
		trainingFrames(tframes)
	{}
	~PClassifier(){}

protected:
	void run();
};
