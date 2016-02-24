#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "vec2.h"

// The camera that takes pictures of your soul
class Camera
{
private:

public:
	Camera();
	void start();
	Vec2 stop();

};
