#include "PClassifier.h"
#include "ClassifierBase.h"
#include "Draw.h"
#include "DrawExtensions.h"

void PClassifier::run()
{   
		
	long long frameCount = 0;		 		 
	while (true)
	{		
		Mat frame = receive(frameBuffer);      

		if(frameCount < trainingFrames)
		{
			frameCount++;
			continue;
		}
			
		ClassifierParams param = {frame};	  
		auto detections  = classifier->detect(param);
		ClasifierFrame result = {detections};
	 
		send(targetBuffer, result);		
   }
}