#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "puttextzh/puttextzh.h"

#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "CosImage.h"
#include "StepImage.h"
#include "WaveParameter.h"
#include "RadioBox.h"
#include "RectPulseImage.h"
#include "SawtoothImage.h"
#include "RectWaveImage.h"

#define WINDOW_NAME "均匀传输线上的行波"

using namespace cv;

const int width = 800;
const int height = 600;

bool gIsMouseDowm = false;
int gMouseX = 0;

Mat initImg(void);
void on_MouseHandle(int event, int x, int y, int flags, void* param);

int main() {
	Mat img = initImg();

	//Rect r(Point(100, 100), Point(250, 250));

	//rectangle(img, r, Scalar(0, 255, 0));

	//putText(img, "Hello World", Point(600, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 0), 1, 16);
	//putTextZH(img, "OpenCV欢迎你", Point(50, 100), Scalar(255, 0, 0), 30,"ss");
	
	//cv::namedWindow("Example Circle", cv::WINDOW_AUTOSIZE);

	cvui::init(WINDOW_NAME);

	int step = 1;//图像平滑程度

	WaveParameter* defaultParameter = new WaveParameter(1, 200, 0, 0.02, -0.3f, 1.0f);
	WaveParameter* nowParameter = new WaveParameter(*defaultParameter);

	std::vector<FunctionImage*> functionImages;
	//FunctionImage* functionImage = new CosImage(width, height, step, defaultParameter);
	//FunctionImage* functionImage = new StepImage(width, height, step, defaultParameter);
	
	
	functionImages.push_back(new CosImage(width, height, step, defaultParameter));
	functionImages.push_back(new StepImage(width, height, step, defaultParameter));
	functionImages.push_back(new RectPulseImage(width, height, step, defaultParameter));
	//functionImages.push_back(new SawtoothImage(width, height, step, defaultParameter));
	//functionImages.push_back(new RectWaveImage(width, height, step, defaultParameter));
	FunctionImage* nowFunctionImage = functionImages.at(0);
	
	double startTime = getTickCount();
	double time = (getTickCount() - startTime) / getTickFrequency();//循环开始到现在的秒数
	bool isPlaying = true;

	RadioBox* radioBox = new RadioBox(4);
	bool checked[3] = { false,false,true };

	

	for (;;) {
		Mat bg = img.clone();
		Mat overlay;
		

		if (isPlaying) {
			time = (getTickCount() - startTime) / getTickFrequency();//循环开始到现在的秒数
		}
		else {
			startTime += getTickCount() - startTime - time * getTickFrequency();
		}

		std::vector<cv::Point*> points;
		points = nowFunctionImage->generatePoints(time);
		int npts[] = { width / step };
		float alpha = 0.65;


		//反向行波
		if (cvui::checkbox(bg, width + 180, 365, " ", &checked[1], 0xffffff)) {
			bg.copyTo(overlay);
			const Point* ppt[] = { points[1] };
			polylines(overlay, ppt, npts, 1, false, Scalar(255, 0, 0), 2, 16);
			addWeighted(overlay, alpha, bg, 1 - alpha, 0, bg);
		}
		//正向行波
		if (cvui::checkbox(bg, width + 180, 325, " ", &checked[0], 0xffffff)) {
			bg.copyTo(overlay);
			const Point* ppt[] = { points[0] };
			polylines(overlay, ppt, npts, 1, false, Scalar(0, 0, 255), 2, 16);
			addWeighted(overlay, alpha, bg, 1 - alpha, 0, bg);
		}
		//全部行波
		if (cvui::checkbox(bg, width + 180, 405, " ", &checked[2], 0xffffff)) {
			bg.copyTo(overlay);
			const Point* ppt[] = { points[2] };
			polylines(overlay, ppt, npts, 1, false, Scalar(0, 0, 0), 2, 16);
			addWeighted(overlay, alpha, bg, 1 - alpha, 0, bg);
		}

		cvui::printf(bg, 26, 20, 0.5, 0x000000, "time: %.2lf s", time);

		if (cvui::trackbar<float>(bg, width + 80, 20, 250, &(nowParameter->amplitude), 0.1f, 2.0f)) {
			nowFunctionImage->setAmplitude(nowParameter->amplitude);
		}
		if (cvui::trackbar<float>(bg, width + 80, 70, 250, &(nowParameter->velocity), 10.0f, 400.0f)) {
			nowFunctionImage->setVelocity(nowParameter->velocity);
		}
		if (cvui::trackbar<float>(bg, width + 80, 120, 250, &(nowParameter->alpha), 0.0f, 0.006f, 1, "%.3f")) {
			nowFunctionImage->setAlpha(nowParameter->alpha);
		}
		if (cvui::trackbar<float>(bg, width + 80, 170, 250, &(nowParameter->beta), 0.01f, 0.1f, 1, "%.2f")) {
			nowFunctionImage->setBeta(nowParameter->beta);
		}
		if (cvui::trackbar<float>(bg, width + 80, 220, 250, &(nowParameter->N1), -1.0f, 1.0f)) {
			nowFunctionImage->setN1(nowParameter->N1);
		}
		if (cvui::trackbar<float>(bg, width + 80, 270, 250, &(nowParameter->N2), -1.0f, 1.0f)) {
			nowFunctionImage->setN2(nowParameter->N2);
		}

		if (cvui::radiobox(bg, width + 50, 325, " ", &radioBox->nowChecked[0],0xffffff)) {
			if (radioBox->select(0)) {
				nowFunctionImage = functionImages.at(0);
				nowParameter->clone(&nowFunctionImage->getWaveParameter());
				startTime = getTickCount();
			}
		}
		if (cvui::radiobox(bg, width + 50, 365, " ", &radioBox->nowChecked[1], 0xffffff)) {
			if (radioBox->select(1)) {
				nowFunctionImage = functionImages.at(1);
				nowParameter->clone(&nowFunctionImage->getWaveParameter());
				startTime = getTickCount();
			}
		}
		if (cvui::radiobox(bg, width + 50, 405, " ", &radioBox->nowChecked[2], 0xffffff)) {
			if (radioBox->select(2)) {
				nowFunctionImage = functionImages.at(2);
				nowParameter->clone(&nowFunctionImage->getWaveParameter());
				startTime = getTickCount();
			}
		}


		if (radioBox->nowChecked[2] == true) {
			float sum = 0;
			for (int i = 0; i < width / step; ++i) {
				for (int j = 0; j < 3; ++j) {
					sum += abs(points[j][i].y - 300);
				}
			}
			if (sum <= 1.0f * nowFunctionImage->getVelocity()) {
				startTime = getTickCount();
				isPlaying = true;
			}
		}

		//if (cvui::checkbox(bg, width + 50, 445, " ", &radioBox->nowChecked[3])) {
		//	if (radioBox->select(3)) {
		//		nowFunctionImage = functionImages.at(3);
		//		nowParameter->clone(&nowFunctionImage->getWaveParameter());
		//		startTime = getTickCount();
		//	}
		//}
		
		
		if (cvui::button(bg, width + 70, 530, 110, 40, " ")) {
			startTime = getTickCount();
			isPlaying = true;
		}
		if (cvui::button(bg, width + 200, 530, 110, 40, " ")) {
			nowParameter->clone(defaultParameter);
			nowFunctionImage->setWaveParameter(defaultParameter);
		}
		putTextZH(bg, "重新生成         恢复默认", Point(width + 92, 540), Scalar(255, 255, 255), 16, "黑体");

		if (cvui::button(bg, width + 70, 480, 110, 40, " ")) {
			isPlaying = !isPlaying;
		}
		if (isPlaying) {
			putTextZH(bg, "暂停", Point(width + 110, 490), Scalar(255, 255, 255), 16, "黑体");
		}
		else {
			putTextZH(bg, "播放", Point(width + 110, 490), Scalar(255, 255, 255), 16, "黑体");
		}

		//setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&gMouseX);

		////鼠标识别
		//if (!isPlaying && gIsMouseDowm && gMouseX <= width + 20 && gMouseX >= 20) {
		//	checked[2] = true;
		//	float functionY = points[2][(gMouseX - 20) / step].y;

		//	line(bg, Point(20, functionY), Point(gMouseX, functionY), Scalar(0, 0, 0), 1, 16);
		//	line(bg, Point(gMouseX, 300), Point(gMouseX, functionY), Scalar(0, 0, 0), 1, 16);
		//}

		cvui::update();
		cvui::imshow(WINDOW_NAME, bg);

		if (cv::waitKey(33) >= 0) break;
		if (getWindowProperty(WINDOW_NAME, WND_PROP_VISIBLE) < 1) {
			break;
		}
	}

	cv::destroyAllWindows();
	//waitKey(0);
	delete defaultParameter;
	delete nowParameter;
	delete radioBox;

	for (int i = 0; i < functionImages.size(); i++) {
		delete functionImages.at(i);
	}

	return 0;
}

Mat initImg(void) {
	Mat img(height, width + 360, CV_8UC3, Scalar(255, 255, 255));
	Point* rect = new Point[4];
	rect[0] = Point(width + 20, 0);
	rect[1] = Point(width + 360, 0);
	rect[2] = Point(width + 360, 600);
	rect[3] = Point(width + 20, 600);

	fillConvexPoly(img, rect, 4, Scalar(38, 37, 37), 16);
	delete[] rect;

	line(img, Point(0, 300), Point(819, 300), Scalar(0, 0, 0), 1, 16);
	line(img, Point(20, 0), Point(20, 600), Scalar(0, 0, 0), 1, 16);
	line(img, Point(20, 100), Point(30, 100), Scalar(0, 0, 0), 1, 16);
	line(img, Point(20, 200), Point(30, 200), Scalar(0, 0, 0), 1, 16);
	line(img, Point(20, 400), Point(30, 400), Scalar(0, 0, 0), 1, 16);
	line(img, Point(20, 500), Point(30, 500), Scalar(0, 0, 0), 1, 16);

	//cvui::printf(img, width + 25, 30, 0.8, 0xffffff, "A");
	//cvui::printf(img, width + 25, 80, 0.8, 0xffffff, "v");Times New Roman
	putTextZH(img, "振幅", Point(width + 30, 30), Scalar(255, 255, 255), 17, "黑体");
	putTextZH(img, "波速", Point(width + 30, 80), Scalar(255, 255, 255), 17, "黑体");
	putTextZH(img, "α", Point(width + 35, 130), Scalar(255, 255, 255), 24, "Euclid");
	putTextZH(img, "β", Point(width + 35, 180), Scalar(255, 255, 255), 24, "Euclid");
	putTextZH(img, "N1", Point(width + 35, 228), Scalar(255, 255, 255), 20, "Euclid");
	putTextZH(img, "N2", Point(width + 35, 278), Scalar(255, 255, 255), 20, "Euclid");

	putTextZH(img, "余弦波", Point(width + 72, 325), Scalar(255, 255, 255), 15, "黑体");
	putTextZH(img, "阶跃函数", Point(width + 72, 365), Scalar(255, 255, 255), 15, "黑体");
	putTextZH(img, "矩形脉冲", Point(width + 72, 405), Scalar(255, 255, 255), 15, "黑体");
	//putTextZH(img, "锯齿波", Point(width + 72, 445), Scalar(255, 255, 255), 13, "黑体");
	putTextZH(img, "正向行波 红", Point(width + 202, 325), Scalar(255, 255, 255), 15, "黑体");
	putTextZH(img, "反向行波 蓝", Point(width + 202, 365), Scalar(255, 255, 255), 15, "黑体");
	putTextZH(img, "全部行波 黑", Point(width + 202, 405), Scalar(255, 255, 255), 15, "黑体");

	putTextZH(img, "提示：增加α的值可以模拟有损线", Point(width + 50, 450), Scalar(0, 255, 255), 20, "黑体");
	
	return img;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
	switch (event)
	{
		//鼠标移动消息
	case EVENT_MOUSEMOVE:
	{
		gMouseX = x;
	}
	break;

	//左键按下消息
	case EVENT_LBUTTONDOWN:
	{
		gIsMouseDowm = true;
		gMouseX = x;
	}
	break;

	//左键抬起消息
	case EVENT_LBUTTONUP:
	{
		gIsMouseDowm = false;
	}
	break;

	}
}