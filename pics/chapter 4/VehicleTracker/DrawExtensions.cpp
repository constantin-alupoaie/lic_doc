#include "DrawExtensions.h"
#include "Draw.h"
#include <iostream>

using namespace std;

void DrawExtensions::drawBlob( const carDetection* b, Mat& output )
{
	Rect rect = b->rect;
	Scalar color = Scalar( 0, 0, 255 );
	rectangle( output, rect.tl(), rect.br(), color);
	
	unique_ptr<char> text = unique_ptr<char>(new char[50]);
	auto data = text.get();
	sprintf(data, "%d", b->id);
	Draw::text(data,b->rect.tl(), output);
}

void DrawExtensions::drawTracks(vector<track>& tracks, Mat& output, Scalar color )
{
	auto it = tracks.begin();
	auto end = tracks.end();
	for(;it != end; ++it)
	{
		auto rect = it->asRecti();
		Draw::rect(rect, output, color);

		char* text = new char[50];
		itoa(it->id, text, 10);		
		Draw::text(text, rect.tl(), output, color);
		delete[] text;
	}		
}

void DrawExtensions::drawDetections( const vector<detection>& detections, Mat& image )
{
	auto it = detections.begin();
	auto end = detections.end();
	for(;it != end; ++it)
		Draw::anotatedRect(it->id, it->rect, image);		
}

void DrawExtensions::drawBlobs( vector<blob>& blobs, Mat& output )
{
	auto it = blobs.begin();
	auto end = blobs.end();
	for(; it != end ; ++it)
		rectangle( output, it->rect.tl(), it->rect.br(), Scalar(255,0,0));		
}