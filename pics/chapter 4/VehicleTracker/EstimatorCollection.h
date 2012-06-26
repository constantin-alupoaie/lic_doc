#pragma once
#include <map>
#include <memory>
#include "KalmanEstimator.h"

using namespace std;

class EstimatorCollection
{
public:
   map<int, shared_ptr<KalmanEstimator> > estimatorsMap;         
   EstimatorCollection(void);
   ~EstimatorCollection(void);

   shared_ptr<KalmanEstimator> get(int id);

   shared_ptr<KalmanEstimator> add(shared_ptr<carDetection> b);
   void remove(int id);
   bool contains(int id);

   void update(shared_ptr<carDetection> b);
};
