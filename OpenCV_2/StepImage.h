#pragma once
#include "FunctionImage.h"
class StepImage :
	public FunctionImage
{
public:
	StepImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2);
	StepImage(int w, int h, int s, WaveParameter* wp);
	~StepImage();
	std::vector<cv::Point*> generatePoints(float t) override;
	float calculateFunction(float t) override;
};

