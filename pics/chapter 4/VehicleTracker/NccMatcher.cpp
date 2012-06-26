#include "NccMatcher.h"

float NccMatcher::match( track& tr, detection& dt, Mat& frame )
{
	auto detectionImg = frame(dt.rect);
	auto trackImg = tr.model.nccModel;

	return distance(tr, detectionImg);	 
}

float NccMatcher::distance( track& tr, Mat& region )
{
	auto detectionImg = region.clone();
	auto trackImg = tr.model.nccModel.clone();

	Mat resizedDetection;
	Mat resizedTrack;

	if(detectionImg.size().area() > trackImg.size().area())
	{
		resizedTrack = trackImg;
		cv::resize(detectionImg, resizedDetection, trackImg.size(), 0,0);
	}else
	{
		resizedDetection = detectionImg;
		cv::resize(trackImg, resizedTrack, detectionImg.size(), 0,0);
	}

	//imshow("track bb", resizedTrack);
	//imshow("detection bb", resizedDetection);

	//GaussianBlur(resizedDetection, resizedDetection, Size(7,7), 5, 3, BORDER_CONSTANT); 
	//GaussianBlur(resizedTrack, resizedTrack, Size(7,7), 5, 3, BORDER_CONSTANT); 
	//imshow("track", resizedTrack);
	//imshow("detection", resizedDetection);
	//cv::waitKey();

	Mat_<float> result = Mat_<float>(1,1);
	cv::matchTemplate( resizedDetection, resizedTrack, result, CV_TM_CCOEFF_NORMED);
	double maxVal = result.at<float>(0,0);
	

	return (float)1000/maxVal;				 
}

float NccMatcher::distance( track& tr, Mat& region, Mat& descriptor )
{	
	auto trackImg = tr.model.nccModel;
	return distance(tr, region);	
}

void NccMatcher::inferModel( track& tr, detection& dt, Mat& frame )
{
	tr.model.nccModel = frame(dt.rect).clone();
}
