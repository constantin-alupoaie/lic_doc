#pragma once
#include "TrackMatcher.h"
#include "PTracker.h"
#include <map>

using namespace std;

class Matcher2D: public TrackMatcher
{
public:
	Matcher2D(){}
	~Matcher2D(){}

	float match(track& tr, detection& dt, Mat& frame);
	void inferModel(track& tr, detection& dt, Mat& frame);
};