#pragma once
#include <opencv2\opencv.hpp>
#include <memory>
#include "Blob.h"

using namespace cv;
using namespace std;

struct EstimatorResult
{
   float centerX;
   float centerY;

   float width;
   float height;

   float vx;
   float vy;

   Rect toRect()
   {
      Rect r(centerX - width / 2, centerY - height / 2, width, height);
      return(r);
   }
};

class KalmanEstimator
{
private:
   unique_ptr<KalmanFilter> filter;
   cv::Mat_<float>          measurement;
   EstimatorResult          lastPrediction;

public:
   int vehicleId;

   KalmanEstimator(void);
   ~KalmanEstimator(void);

   void init(shared_ptr<carDetection> blob);
   EstimatorResult predict();
   EstimatorResult correct(shared_ptr<carDetection> b);
   EstimatorResult update(shared_ptr<carDetection> b);
   EstimatorResult getLastPrediction();
};
