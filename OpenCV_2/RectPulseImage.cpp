#include "RectPulseImage.h"



RectPulseImage::RectPulseImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2)
	: FunctionImage(w, h, s, a, v,alpha, b, N1, N2)
{
}
RectPulseImage::RectPulseImage(int w, int h, int s, WaveParameter* wp)
	: FunctionImage(w, h, s, wp)
{

}

RectPulseImage::~RectPulseImage()
{
}

float RectPulseImage::calculateFunction(float t) {
	if (t >= 0 && t <= 0.5) {
		return amplitude;
	}
	else {
		return 0;
	}
}

//std::vector<cv::Point*> RectPulseImage::generatePoints(float t) {
//	return FunctionImage::generatePoints(t);
//}