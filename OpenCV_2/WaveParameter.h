#pragma once
class WaveParameter
{
public:
	WaveParameter(float amplitude, float velocity, float alpha, float beta, float N1, float N2);
	~WaveParameter();
	void clone(WaveParameter* wp);

	float amplitude;
	float velocity;
	float alpha;
	float beta;

	float N1;
	float N2;
};

