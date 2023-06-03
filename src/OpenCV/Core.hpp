#pragma once

#include <opencv2/opencv.hpp>

int OpenCVCore(char *img_path){
    cv::Mat input = cv::imread(img_path);
    cv::Mat gray;
    cv::cvtColor(input, gray, COLOR_BGR2GRAY);
    cv::Ptr<cv::LineSegmentDetector> det;
    det = cv::createLineSegmentDetector();
    cv::Mat lines;
    det->detect(gray, lines);
    det->drawSegments(input, lines);
    cv::imshow("input", input);
    cv::waitKey(0);
    return 0;
}