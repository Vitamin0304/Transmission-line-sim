#include "FunctionImage.h"



FunctionImage::FunctionImage(int w, int h, int s, float a, float v, float alpha, float b, float N1, float N2)
	: width(w),height(h),step(s), amplitude(a),velocity(v), alpha(alpha),beta(b),N1(N1),N2(N2)
{
	points.push_back(new cv::Point[width / step]);
	points.push_back(new cv::Point[width / step]);
	points.push_back(new cv::Point[width / step]);
}
FunctionImage::FunctionImage(int w, int h, int s, WaveParameter* wp) 
	: width(w), height(h), step(s)
{
	amplitude = wp->amplitude;
	velocity = wp->velocity;
	alpha = wp->alpha;
	beta = wp->beta;
	N1 = wp->N1;
	N2 = wp->N2;

	points.push_back(new cv::Point[width / step]);
	points.push_back(new cv::Point[width / step]);
	points.push_back(new cv::Point[width / step]);
}

FunctionImage::~FunctionImage()
{
	delete points[0];
	delete points[1];
	delete points[2];
}

int FunctionImage::unitStep(float x) {
	if (x >= 0) {
		return 1;
	}
	else {
		return 0;
	}
}

double FunctionImage::Power(double base, int exponent) {
	int n = exponent;
	double result = 1;
	if (fabs(base) <= 0.00001) {
		if (n == 0)
			return 1;
		else
			return 0;
	}
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		if ((n & 1) == 1)
			result = result * base;
		base *= base;
		n >>= 1;

	}
	return exponent < 0 ? (1 / result) : result;
}

std::vector<cv::Point*> FunctionImage::generatePoints(float t) {
	//行波的反射次数 x = i * step
	int reflectTimes = (int)(velocity * t / width);
	//遍历所有x
	for (int i = 0; i < width / step; ++i) {
		float y1 = 0;
		float y2 = 0;

		//完整的正向行波
		for (int j = 0; j < (reflectTimes + 1) / 2; j++) {
			y1 += Power(N1, j) * Power(N2, j)
				* exp(-alpha * (i * step + j * 2 * width))
				* calculateFunction(t - (i * step + j * 2 * width) / velocity);
		}
		//完整的反向行波
		for (int j = 0; j < reflectTimes / 2; j++) {
			y2 += Power(N1, j) * Power(N2, j + 1)
				* exp(alpha * (i * step - (j + 1) * 2 * width))
				* calculateFunction(t + (i * step - (j + 1) * 2 * width) / velocity);
		}

		////单位阶跃函数和电源函数的自变量 t-x/v
		//float forwardFlag = t - (i * step + reflectTimes * width) / velocity;
		//float reverseFlag = t + (i * step - (reflectTimes + 1) * width) / velocity;

		//未到达端点的行波
		if (reflectTimes % 2 == 0) { //正向
			if (unitStep(t - (i * step + reflectTimes * width) / velocity) == 1) {
				y1 += Power(N1, reflectTimes / 2) * Power(N2, reflectTimes / 2)
					* exp(-alpha * (i * step + reflectTimes * width))
					* calculateFunction(t - (i * step + reflectTimes * width) / velocity);
			}
		}
		else { //反向
			if (unitStep(t + (i * step - (reflectTimes + 1) * width) / velocity) == 1) {
				y2 += Power(N1, reflectTimes / 2) * Power(N2, reflectTimes / 2 + 1)
					* exp(alpha * (i * step - (reflectTimes + 1) * width))
					* calculateFunction(t + (i * step - (reflectTimes + 1) * width) / velocity);
			}
		}
		//points[i] = cv::Point(i * step + 20, height / 2 - 100 * y);
		points[0][i] = cv::Point(i * step + 20, height / 2 - 100 * y1); 
		points[1][i] = cv::Point(i * step + 20, height / 2 - 100 * y2);
		points[2][i] = cv::Point(i * step + 20, height / 2 - 100 * (y1+y2));
	}
	return points;
}

void FunctionImage::setWaveParameter(WaveParameter* wp) {
	amplitude = wp->amplitude;
	velocity = wp->velocity;
	alpha = wp->alpha;
	beta = wp->beta;
	N1 = wp->N1;
	N2 = wp->N2;
}

WaveParameter FunctionImage::getWaveParameter(void) {
	WaveParameter wp(amplitude, velocity, alpha, beta, N1, N2);
	return wp;
}