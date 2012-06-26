#include "KalmanFilter2D.h"
#include "RectTool.h"
/*======================= KALMAN FILTER =========================*/
/* State vector is (x,y,w,h,dx,dy,dw,dh). */
/* Measurement is (x,y,w,h). */

#define F \
	1, 0, 0, 0, 1.15, 0, 0, 0, \
	0, 1, 0, 0, 0, 1.15, 0, 0, \
	0, 0, 1, 0, 0, 0, 1.15, 0, \
	0, 0, 0, 1, 0, 0, 0, 1.15, \
	0, 0, 0, 0, 1, 0, 0, 0,	\
	0, 0, 0, 0, 0, 1, 0, 0,	\
	0, 0, 0, 0, 0, 0, 1, 0,	\
	0, 0, 0, 0, 0, 0, 0, 1

/* Measurement matrix H: */
#define H \
	1, 0, 0, 0, 0, 0, 0, 0, \
	0, 1, 0, 0, 0, 0, 0, 0,	\
	0, 0, 1, 0, 0, 0, 0, 0,	\
	0, 0, 0, 1, 0, 0, 0, 0


KalmanFilter2D::KalmanFilter2D()
{
	filter = KalmanFilter(8,4);

	//setup error covariances
	setIdentity(filter.processNoiseCov, Scalar::all(1e-4));
	setIdentity(filter.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(filter.errorCovPost, Scalar::all(.1));

	//setup transition matrix with F
	filter.transitionMatrix = (Mat_<float>(8,8) << F );

	//setup measurement matrix with H
	filter.measurementMatrix = (Mat_<float>(4,8) << H);

	measurement = Mat_<float>(4,1);
}

void KalmanFilter2D::mapMatToResult(const Mat& m, KalmanResult2D& result)
{
	result.centerX = m.at<float>(0);
	result.centerY = m.at<float>(1);
	result.width   = this->width;//m.at<float>(2);
	result.height  = this->height;//m.at<float>(3);	
	result.vx	   = m.at<float>(4);
	result.vy	   = m.at<float>(5);
	result.wx	   = m.at<float>(6);
	result.wy	   = m.at<float>(7);
}

void KalmanFilter2D::init( KalmanInput2D& input )
{
	auto size = input.rect.size();
	auto center = RectTool::center(input.rect);

	this->width = size.width;
	this->height = size.height;

	filter.statePost.at<float>(0) = center.x;
	filter.statePost.at<float>(1) = center.y;
	filter.statePost.at<float>(2) = size.width;
	filter.statePost.at<float>(3) = size.width;
	filter.statePost.at<float>(4) = 0;//dx
	filter.statePost.at<float>(5) = 0;//dy
	filter.statePost.at<float>(6) = 0;//wx
	filter.statePost.at<float>(7) = 0;//wy
}

KalmanResult2D KalmanFilter2D::predict()
{
	Mat estimation = filter.predict();
	KalmanResult2D result;
	mapMatToResult(estimation, result);
	lastState = result;
	return result;
}

KalmanResult2D KalmanFilter2D::correct( KalmanInput2D& input )
{	
	auto size = input.rect.size();
	auto center = RectTool::center(input.rect);

	this->width = size.width;
	this->height = size.height;

	measurement(0) = center.x;
	measurement(1) = center.y;
	measurement(2) = size.width;
	measurement(3) = size.height;

	//apply measurement
	Mat estimation = filter.correct(measurement);
	KalmanResult2D result;
	mapMatToResult(estimation, result);
	return result;
}

KalmanResult2D KalmanFilter2D::update( KalmanInput2D& input )
{
	predict();
	auto estimation = correct(input);
	lastState = estimation;
	return estimation;
}