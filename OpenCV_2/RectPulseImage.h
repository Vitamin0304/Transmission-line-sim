#pragma once
#include "FunctionImage.h"
class RectPulseImage :
	public FunctionImage
{
public:
	RectPulseImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2);
	RectPulseImage(int w, int h, int s, WaveParameter* wp);
	~RectPulseImage();
	//std::vector<cv::Point*> generatePoints(float t) override;
	float calculateFunction(float t) override;
};

