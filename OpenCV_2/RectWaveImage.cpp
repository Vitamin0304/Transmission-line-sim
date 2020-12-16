#include "RectWaveImage.h"



RectWaveImage::RectWaveImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2)
	: FunctionImage(w, h, s, a, v, alpha, b, N1, N2)
{
}
RectWaveImage::RectWaveImage(int w, int h, int s, WaveParameter* wp)
	: FunctionImage(w, h, s, wp)
{

}

RectWaveImage::~RectWaveImage()
{
}

float RectWaveImage::calculateFunction(float t) {
	if (t >= 0 && t < 1) {
		if (t < 0.5) {
			return amplitude;
		}
		else {
			return -amplitude;
		}
	}
	else if (t >= 1) {
		int n = (int)t;
		t -= n;
		if (t < 0.5) {
			return amplitude;
		}
		else {
			return -amplitude;
		}
	}
	else {
		return 0;
	}
}