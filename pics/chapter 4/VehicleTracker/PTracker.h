#pragma once
#include "Video.h"
#include "BgSubtractorBase.h"
#include "ClassifierBase.h"
#include "TrackMatcher.h"
#include "KalmanFilter2D.h"
#include "LbpMatcher.h"
#include "Validator.h"
#include "NccMatcher.h"
#include "PClassifier.h"
#include "PSubtractor.h"
#include <agents.h>

using namespace Concurrency;

struct trackEntry
{
	int begin;
	int end;
	int id;
};

class PTracker: public agent
{
private:
#pragma region fields
	bool debugPrint;
	long long carCount;
	Rect frameRect;
	int frameCount;
		
	TrackMatcher* matcher;
	TrackMatcher* secMatcher;

	vector<track> tracks;	
	std::map<int, shared_ptr<KalmanFilter2D> > kalmanFilters;
	std::map<int, Validator> validators;
#pragma endregion
	
#pragma region frame_buffers
	vector<Mat> frameBuffer;
	vector<Mat> grayFrameBuffer;
	vector<Mat> foregroundBuffer;
	vector<vector<detection>> detectionBuffer;

	bool shiftBuffers(SubFrame subResult, ClasifierFrame classifierResult);
#pragma endregion
	
#pragma region methods
	track createFromDetection(detection& d,IdGenerator& gen, Mat& frame);
	track createTrack(detection& det, IdGenerator& idGenerator, Mat& grayFrame);
	void deleteTrack(track& tr);
	void deleteExitedTracks();

	bool trackLucasKanade(track& tr, vector<Mat> frames, vector<Mat> grayFrames, vector<Mat> foregrounds,Rect& predictedRect, Mat& output);		
	bool getKalmanPrediction(track& tr, Rect& predictedRect);
	void forwardKalman(track& tr);
	Rect mergePredictions(bool lkSuccess, bool kalmanSuccess, track& tr,Rect& lkRect,Rect& kalmanRect,vector<Mat> frameBuffer, float& bestMatchDist);

	void correctKalman(track& tr);
	bool trackHasExited(track& tr);
	
	vector<Point2f> allRegisteredPoints;
	map<int, trackEntry> registeredTracks;
	map<int, bool> registeredStatuses;	
	map<int, float> xmedianForTracks;
	map<int, float> ymedianForTracks;
	map<int, float> scaleForTracks;
	int trackKey;
	
	void beginTracking();
	int registerForTracking(track& tr);
	void performTracking();
	bool getMedianFlowPrediction(track& tr, Rect& newRect);

#pragma endregion

	ISource<ClasifierFrame>& classifierBuffer;
	ISource<SubFrame>& subtractorBuffer;
	ITarget<int>& syncBuffer;

public:
	~PTracker(){}
	PTracker(ISource<SubFrame>& subBuffer, ISource<ClasifierFrame>& clsBuffer, TrackMatcher* mat, ITarget<int>& sync)
		:subtractorBuffer(subBuffer),
		classifierBuffer(clsBuffer),
		matcher(mat),
		syncBuffer(sync),
		carCount(0),
		debugPrint(false),
		secMatcher(new LbpMatcher())
	{}

	void run();
};