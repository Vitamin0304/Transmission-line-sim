#include "RadioBox.h"



RadioBox::RadioBox(int total): total(total)
{
	nowChecked = new bool[total];
	lastIndex = 0;
	nowChecked[0] = true;
	for (int i = 1; i < total; i++) {
		nowChecked[i] = false;
	}
}

RadioBox::~RadioBox()
{
	delete[] nowChecked;
}

bool RadioBox::select(int n) {
	if (n >= total || n < 0) {
		return false;	
	}
	if (n != lastIndex) {
		nowChecked[lastIndex] = false;
		lastIndex = n;
		return true;
	}
	else {
		return false;
	}
}