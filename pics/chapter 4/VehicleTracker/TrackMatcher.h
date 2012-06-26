#pragma once
#include "ClassifierBase.h"

struct model
{	
	Rect kalmanRect;
	Mat lbpHist;
	Mat elbp;
	Mat nccModel;
};

struct track
{
	int id;
	Rect_<float> rectf;	
	model model;
	int lkId;
	bool markedForDeletion;
	float predictionDist;

	void assign(Rect rect)
	{
		Point2f tl = rect.tl();
		rectf = Rect_<float>(tl.x, tl.y, rect.width, rect.height);
	}

	Rect asRecti()
	{
		return Rect(rectf.x, rectf.y, rectf.width, rectf.height);
	}
};

class TrackMatcher
{
public:
	TrackMatcher(){};
	~TrackMatcher(){};

	float goodMaxDist;
	float maxSimilarityDist;
	virtual void begin(){};	
	virtual float match(track& tr, detection& dt, Mat& frame) = 0;
	virtual float distance(track& tr, Mat& region) { return 0; };
	virtual float distance(track& tr, Mat& region, Mat& descriptor) { return 0; };

	virtual void inferModel(track& tr, detection& dt, Mat& frame) = 0;
};