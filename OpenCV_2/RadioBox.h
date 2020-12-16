#pragma once
class RadioBox
{
public:
	RadioBox(int total);
	~RadioBox();

	bool select(int n);

	bool* nowChecked;
private:
	int total;

	int lastIndex;
};

