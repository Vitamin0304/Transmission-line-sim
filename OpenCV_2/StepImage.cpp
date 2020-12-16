#include "StepImage.h"



StepImage::StepImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2)
	: FunctionImage(w, h, s, a, v, alpha, b, N1, N2)
{
}
StepImage::StepImage(int w, int h, int s, WaveParameter* wp)
	: FunctionImage(w, h, s, wp)
{

}

StepImage::~StepImage()
{
}

float StepImage::calculateFunction(float t) {
	if (t >= 0) {
		return amplitude;
	}
	else {
		return 0;
	}
}

std::vector<cv::Point*> StepImage::generatePoints(float t) {
	return FunctionImage::generatePoints(t);
}