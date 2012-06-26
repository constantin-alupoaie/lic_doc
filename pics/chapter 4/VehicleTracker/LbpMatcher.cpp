#include "LbpMatcher.h"
#include "histogram.h"
#include "lbp.h"
#include "PngSaver.h"

static const float INFINITE = 999999;
bool LbpMatcher::lbpHist( Mat& src , Mat& hist)
{
	if(src.rows < 16+3 || src.cols < 16+3)
		return false;

	auto processed = lbp::ELBP(src,8,8);
	//PngSaver::save("lbp", processed);
	hist = lbp::spatial_histogram(processed, 256, 3, 3);
	return true;
}

float LbpMatcher::match( track& tr, detection& dt, Mat& frame )
{
	if(detectionHists.find(dt.id) == detectionHists.end())
	{
		Mat detHist;
		bool success = lbpHist(frame(dt.rect),detHist);
		if(!success)
			return INFINITE;

		detectionHists[dt.id] = detHist;
	}

	auto dhist = detectionHists[dt.id];
	double dist = lbp::chi_square(tr.model.lbpHist, dhist);

	return (float)dist;
}

void LbpMatcher::inferModel( track& tr, detection& dt, Mat& frame )
{
	if(detectionHists.find(dt.id) == detectionHists.end())
	{
		Mat hist;
		if(!lbpHist(frame(dt.rect), hist))
			return;

		detectionHists[dt.id] = hist;		
	}
	
	tr.model.lbpHist = detectionHists[dt.id];		
}

float LbpMatcher::distance( track& tr, Mat& src )
{
	Mat desc;
	return distance(tr, src, desc);
}

float LbpMatcher::distance( track& tr, Mat& src, Mat& descriptor )
{	
	bool successfull = lbpHist(src, descriptor);	
	if(!successfull)
		return INFINITE;

	double lkDist = lbp::chi_square(tr.model.lbpHist, descriptor);
	return lkDist;	
}