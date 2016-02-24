#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "vec2.h"

// The camera that takes pictures of your soul
class Camera
{
private:
	bool running;
	cv::VideoCapture cap;
	cv::Mat frame;
	cv::Mat imgThresholded;
	cv::Mat imgHSV;



	// Calibration variables
	int iLowH = 0;
	int iHighH = 179;
	int iLowS = 0;
	int iHighS = 255;
	int iLowV = 0;
	int iHighV = 255;



public:
	enum DISPLAY_STATE
	{
		NORMAL,
		THRESHOLDED
	};
	
	DISPLAY_STATE state = NORMAL;
	Camera();
	~Camera();
	void threshold();
	Vec2 track();
	void capture();
	void drawCircle(const Vec2& position);
	void display();

	bool isRunning();
};
