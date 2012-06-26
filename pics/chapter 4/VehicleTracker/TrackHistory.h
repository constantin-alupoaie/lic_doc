#pragma once
#include "opencv2\core\core.hpp"
#include <vector>
#include "Blob.h"

using namespace std;

typedef struct
{
   vector<blob *> newBlobs;
   vector<blob *> trackedBlobs;
   vector<blob *> prevLostBlobs;
} TrackParam;

typedef struct
{
   int                       id;
   vector<Point2f>           trackedPoints;
   vector<int>               frameNumber;
   bool                      isLost;

   vector<Mat>               images;
   vector<Mat>               sifts;
   vector<vector<KeyPoint> > keypoints;
} TrackInfo;

class TrackHistory
{
private:
   vector<blob>          history;
   int                   size;
   map<int, TrackInfo *> infos;

public:
   vector<blob *> previousBlobs;

   TrackHistory(int size);

   void append(blob b);

   void update(TrackParam *param);

   vector<TrackInfo *> getLost();
};
