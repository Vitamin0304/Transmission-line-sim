#include "WaveParameter.h"



WaveParameter::WaveParameter(float amplitude, float velocity, float alpha, float beta, float N1, float N2)
	:amplitude(amplitude), velocity(velocity), alpha(alpha), beta(beta), N1(N1), N2(N2)
{
}


WaveParameter::~WaveParameter()
{
}

void WaveParameter::clone(WaveParameter* wp) {
	amplitude = wp->amplitude;
	velocity = wp->velocity;
	alpha = wp->alpha;
	beta = wp->beta;
	N1 = wp->N1;
	N2 = wp->N2;
}