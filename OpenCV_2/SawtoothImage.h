#pragma once
#include "FunctionImage.h"
class SawtoothImage :
	public FunctionImage
{
public:
	SawtoothImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2);
	SawtoothImage(int w, int h, int s, WaveParameter* wp);
	~SawtoothImage();
	std::vector<cv::Point*> generatePoints(float t) override;
	float calculateFunction(float t) override;
};

