#pragma once
#include "FunctionImage.h"
class RectWaveImage :
	public FunctionImage
{
public:
	RectWaveImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2);
	RectWaveImage(int w, int h, int s, WaveParameter* wp);
	~RectWaveImage();
	
	float calculateFunction(float t) override;
};

