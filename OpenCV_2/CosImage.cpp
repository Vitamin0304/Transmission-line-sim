#include "CosImage.h"



CosImage::CosImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2)
	: FunctionImage(w,h,s,a,v,alpha,b,N1,N2)
{
}
CosImage::CosImage(int w, int h, int s, WaveParameter* wp)
	: FunctionImage(w, h, s, wp)
{

}

CosImage::~CosImage()
{
}

float CosImage::calculateFunction(float t) {
	return amplitude * cos(beta * velocity * t);
}

std::vector<cv::Point*> CosImage::generatePoints(float t) {
	return FunctionImage::generatePoints(t);
}