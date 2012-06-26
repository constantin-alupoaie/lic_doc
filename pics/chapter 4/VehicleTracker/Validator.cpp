#include "Validator.h"

void Validator::tick( bool detectionOccured )
{
	if(!consideredLost)
		if(!detectionOccured)
		{		
			succesiveBadFrames++;
			successiveGoodFrames = 0;
			totalScore--;
		}else
		{
			succesiveBadFrames = 0;
			successiveGoodFrames++;
			totalScore += successiveGoodFrames;
		}

	if(succesiveBadFrames > maxBadFrames)	
		consideredLost = true;	
}
