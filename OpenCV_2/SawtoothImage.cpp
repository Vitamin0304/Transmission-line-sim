#include "SawtoothImage.h"



SawtoothImage::SawtoothImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2)
	: FunctionImage(w, h, s, a, v, alpha, b, N1, N2)
{
}
SawtoothImage::SawtoothImage(int w, int h, int s, WaveParameter* wp)
	: FunctionImage(w, h, s, wp)
{

}

SawtoothImage::~SawtoothImage()
{
}

float SawtoothImage::calculateFunction(float t) {
	if (t >= 0 && t < 1) {
		return amplitude * (-2 * t + 1);
	}
	else if(t >= 1){
		for (;;) {
			t -= 1;
			if (t < 1) {
				break;
			}
		}
		return amplitude * (-2 * t + 1);
	}
	else {
		return 0;
	}
}

std::vector<cv::Point*> SawtoothImage::generatePoints(float t) {
	return FunctionImage::generatePoints(t);
}