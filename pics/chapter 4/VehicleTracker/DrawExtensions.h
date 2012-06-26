#pragma once
#include <opencv2/opencv.hpp>
#include "Blob.h"
#include "PTracker.h"

using namespace cv;

class DrawExtensions
{
public:
	DrawExtensions(){};
	~DrawExtensions(){};

	static void drawBlob(const carDetection* b, Mat& output);		
	static void drawBlobs(vector<blob>& blobs, Mat& output);
	static void drawTracks(vector<track>& tracks, Mat& image, Scalar color = Scalar(255,0,0));
	static void drawDetections(const vector<detection>& detections, Mat& image);	
};
