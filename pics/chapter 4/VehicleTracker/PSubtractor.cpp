#include "PSubtractor.h"
#include "PngSaver.h"

void PSubtractor::run()
{
	long long frameCount = 0;
	PngSaver::setBasePath("./Content/Images");
	while (true)
	{
		Mat frame = receive(_vidInput);
		if(frameCount < _trainingFrames)
		{
			_subtractor->learn(frame);
			frameCount++;
		}else
		{			
			Mat foregorund = _subtractor->segment(frame);	
			SubFrame result = {frame, foregorund.clone()};

			//PngSaver::save("sub-frame", frame);
			//PngSaver::save("sub-foreground", foregorund);
			//PngSaver::save("sub-bg_model", _subtractor->getBackground());
			//PngSaver::incrementCount();
			//imshow("frame", frame);
			//imshow("fg", foregorund);
			//waitKey();

			send(_target, result);			
		}				
	}
}

