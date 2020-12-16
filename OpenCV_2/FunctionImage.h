#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "WaveParameter.h"
class FunctionImage
{
public:
	FunctionImage(int w, int h, int s, float a, float v, float alpha,float b,float N1, float N2);
	FunctionImage(int w, int h, int s, WaveParameter* wp);
	~FunctionImage();
	virtual std::vector<cv::Point*> generatePoints(float t);
	int unitStep(float x);
	static double Power(double base, int exponent);
	virtual float calculateFunction(float t) = 0;

	float getAmplitude() { return amplitude; }
	void setAmplitude(float a) { amplitude = a; }
	float getVelocity() { return velocity; }
	void setVelocity(float v) { velocity = v; }
	float getAlpha() { return alpha; }
	void setAlpha(float a) { alpha = a; }
	float getBeta() { return beta; }
	void setBeta(float b) { beta = b; }

	float getN1() { return N1; }
	void setN1(float n1) { N1 = n1; }
	float getN2() { return N2; }
	void setN2(float n2) { N2 = n2; }

	void setWaveParameter(WaveParameter* wp);
	WaveParameter getWaveParameter(void);
protected:
	int step;
	int width;
	int height;

	std::vector<cv::Point*> points;
	
	float amplitude;
	float velocity;
	float alpha;
	float beta;

	float N1;
	float N2;
};

