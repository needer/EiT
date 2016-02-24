#include "image_processor.h"
/*
ImageProcessor::ImageProcessor()
{
	cv::namedWindow("CameraCalibration", CV_WINDOW_AUTOSIZE);

	cvCreateTrackbar("LowH", "CameraCalibration", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "CameraCalibration", &iHighH, 179);
	cvCreateTrackbar("LowS", "CameraCalibration", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "CameraCalibration", &iHighS, 255);
	cvCreateTrackbar("LowV", "CameraCalibration", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "CameraCalibration", &iHighV, 255);

	
}

void ImageProcessor::calibrate(const cv::Mat& frame)
{
	cv::Mat imgHSV;

	cvtColor(frame, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	cv::Mat imgThresholded;

	inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	imshow("Preview", imgThresholded);
}
*/