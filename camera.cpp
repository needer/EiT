#include "camera.h"

// Initialize camera
Camera::Camera() : 
	cap(0), running(false)
{
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	cap.set(CV_CAP_PROP_FPS, 25);

	if (cap.isOpened())
		running = true;
	cv::namedWindow("CameraCalibration", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("LowH", "CameraCalibration", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "CameraCalibration", &iHighH, 179);
	cvCreateTrackbar("LowS", "CameraCalibration", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "CameraCalibration", &iHighS, 255);
	cvCreateTrackbar("LowV", "CameraCalibration", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "CameraCalibration", &iHighV, 255);
}

// Destructor, release camera
Camera::~Camera()
{
	cap.release();
}

// Threshold the captured image
void Camera::threshold()
{
	cvtColor(frame, imgHSV, cv::COLOR_BGR2HSV); // Convert the captured frame from BGR to HSV

	inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded); // Threshold the image

	// Open
	erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	// Close
	dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

}

// Track the current object on screen
Vec2 Camera::track()
{

	Vec2 result(-1,-1);

	cv::Moments oMoments = moments(imgThresholded);
	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;

	// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
	if (dArea > 10000)
	{
		result.x = dM10 / dArea;
		result.y = dM01 / dArea;
	}

	return result;
}

// Take a picture
void Camera::capture()
{
	cap >> frame;
}

void Camera::drawCircle(const Vec2& position)
{
	if (state == NORMAL)
		cv::circle(frame, cv::Point(position.x, position.y), 10, cv::Scalar(0, 255, 0), 20);
	if (state == THRESHOLDED)
		cv::circle(imgThresholded, cv::Point(position.x, position.y), 10, cv::Scalar(0, 255, 0), 20);
}

// Display a picture
void Camera::display()
{
	if (state == NORMAL)
		imshow("Preview", frame);
	if (state == THRESHOLDED)
		imshow("Preview", imgThresholded);

}

// Checks if the camera is working or not
bool Camera::isRunning()
{
	return running;
}