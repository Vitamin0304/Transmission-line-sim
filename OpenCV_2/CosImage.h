#pragma once
#include "FunctionImage.h"
class CosImage :
	public FunctionImage
{
public:
	CosImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2);
	CosImage(int w, int h, int s, WaveParameter* wp);
	~CosImage();
	std::vector<cv::Point*> generatePoints(float t) override;
	float calculateFunction(float t) override;
};

