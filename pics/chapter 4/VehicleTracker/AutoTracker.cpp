#include "AutoTracker.h"
#include "Blob.h"
#include "DrawExtensions.h"
#include <algorithm>
#include "EstimatorCollection.h"
#include <agents.h>
#include "MogSubtractor.h"
#include "PSubtractor.h"
#include "AvgSubtractor.h"
#include "StableAvgSubtractor.h"
#include "PClassifier.h"
#include "HogClassifier.h"
#include "Video.h"
#include "PTracker.h"
#include "Matcher2D.h"
#include "PVideoReader.h"

using namespace Concurrency;

using namespace std;

AutoTracker::AutoTracker( AutoTrackerParam param )
{
	this->videoPath = param.videoPath;
	this->foregroungSegmentator = param.foregroundSegmentator;
	this->blobDetector = param.blobDetector;

	assert(this->videoPath);
	assert(this->foregroungSegmentator);
	assert(this->blobDetector);
}

void AutoTracker::start()
{
	int trainingFrames = 100;
	unbounded_buffer<int> syncBuffer;

	BgSubtractorBase* subtractor = new AvgSubtractor("avg");//new StableAvgSubtractor();		
	ClassifierBase* hogClassifier = new HogDetector();

	unbounded_buffer<Mat> vidOut0;
	unbounded_buffer<Mat> vidOut1;
	PVideoReader vidthread = PVideoReader(videoPath, vidOut0, vidOut1, syncBuffer);

	unbounded_buffer<SubFrame> subtractorOut;	
	PSubtractor psubtractor = PSubtractor(subtractor, vidOut0, subtractorOut, videoPath, trainingFrames);
	psubtractor.SyncBuffer = &syncBuffer;
	
	unbounded_buffer<ClasifierFrame> classifierOut;
	PClassifier parallelClassifier = PClassifier(hogClassifier, vidOut1, classifierOut, trainingFrames);
	
	PTracker tracker = PTracker(subtractorOut, classifierOut, new Matcher2D(), syncBuffer);

	for(int i = 0; i < 250; i++)
		send(syncBuffer, 1);

	vidthread.start();
	psubtractor.start();
	parallelClassifier.start();
	tracker.start();
	
	agent::wait(&vidthread);
	agent::wait(&psubtractor);
	agent::wait(&parallelClassifier);
	agent::wait(&tracker);
}
