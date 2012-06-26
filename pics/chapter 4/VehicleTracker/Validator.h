#pragma once
class Validator
{
private:
	long totalScore;
	long successiveGoodFrames;
	long maxBadFrames;
	long succesiveBadFrames;
	bool consideredLost;

public:
	int minScore;

	Validator(long maxBadFrames = 50)
		:maxBadFrames(maxBadFrames),
		succesiveBadFrames(0),
		successiveGoodFrames(0),
		totalScore(0),
		consideredLost(false),
		minScore(150)		
	{};
	~Validator(){};
		
	long score() { return totalScore; }
	bool isLost() {return consideredLost;}
	void tick(bool detectionOccured);	
};

