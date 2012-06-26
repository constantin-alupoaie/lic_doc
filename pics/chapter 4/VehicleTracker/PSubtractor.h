#pragma once
#include "BgSubtractorBase.h"
#include <agents.h>
#include <iostream>

using namespace Concurrency;
using namespace std;

struct SubFrame
{
   Mat frame;
   Mat foreground;
};

class PSubtractor : public agent
{
private:
	int _trainingFrames;
	BgSubtractorBase   *_subtractor;		
	ISource<Mat>& _vidInput;   
	ITarget<SubFrame>& _target;         

public:
   PSubtractor(BgSubtractorBase *subtractor,ISource<Mat>& videoInput, ITarget<SubFrame>& tbuffer, char *videoPath, int trainingFrames) 
	   :_target(tbuffer),
		_vidInput(videoInput),
		_subtractor(subtractor),
		_trainingFrames(trainingFrames)		
   {}
   ~PSubtractor() {}
   ITarget<int>* SyncBuffer;

protected:
   void run();
};
