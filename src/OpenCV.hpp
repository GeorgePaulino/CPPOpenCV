#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>


cv::Mat adjust_gamma(cv::Mat image, double gamma)
{
    cv::Mat table(1, 256, CV_8UC1);
    for (int i = 0; i < 256; i++)
    {
        table.at<uchar>(i) = (uchar)((pow((i / 255.0), gamma) * 255.0));
    }
    cv::Mat result;
    cv::LUT(image, table, result);
    return result;
}

cv::Mat CleanLines(cv::Mat image)
{
    cv::Mat binary;
    cv::threshold(image, binary, 127, 255, cv::THRESH_BINARY);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat cleaned_image;
    cv::morphologyEx(binary, cleaned_image, cv::MORPH_OPEN, kernel, cv::Point(-1, -1), 1);

    cv::cvtColor(cleaned_image, cleaned_image, cv::COLOR_GRAY2BGR);

    cv::resize(cleaned_image, image, image.size());

    cv::Mat mask;
    cv::bitwise_and(image, cleaned_image, mask);

    return mask;
}

int **PixelByPixel(cv::Mat image)
{
    int **field = new int *[800];
    for (int y = 0; y < 800; y++)
    {
        field[y] = new int[800];
    }
    for (int y = 0; y < 800; y++)
    {
        for (int x = 0; x < 800; x++)
        {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            uchar blue = pixel[0];
            uchar green = pixel[1];
            uchar red = pixel[2];

            if (static_cast<int>(red) == 255 &&
                static_cast<int>(green) == 255 &&
                static_cast<int>(blue) == 255)
            {
                field[x][y] = 0;
            }
            else
            {
                field[x][y] = 1;
            }
        }
    }
    return field;
}

int **OpenCVCore(char *img_path)
{
    float gamma = 50.f;

    cv::Mat img = cv::imread(img_path);
    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
    cv::Mat img_invert;
    cv::bitwise_not(img_gray, img_invert);
    cv::Mat img_smoothing;
    cv::GaussianBlur(img_invert, img_smoothing, cv::Size(21, 21), 0, 0);

    cv::Mat final;
    cv::divide(img_gray, 255 - img_smoothing, final, 255);

    cv::Mat final_gamma = adjust_gamma(final, gamma);
    cv::Mat normalized_lines = CleanLines(final_gamma);
    cv::resize(normalized_lines, normalized_lines, cv::Size(800, 800));

    return PixelByPixel(normalized_lines);
}


bool savePhoto = false;

void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == cv::EVENT_LBUTTONDOWN) {
        savePhoto = true;  // Set the flag to indicate button press
    }
}

int CapturePhoto(const char *ip) {
    cv::VideoCapture cap(ip); // Replace with your camera's IP address or USB device index
    if (!cap.isOpened()) {
        std::cout << "Failed to open the camera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    cv::namedWindow("Camera");

    cv::setMouseCallback("Camera", onMouse);  // Register the mouse event callback

    while (true) {
        cap.read(frame);

        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            break;
        }
        
        cv::resizeWindow("Camera", 600, 600); // Set the desired window size
        cv::imshow("Camera", frame);

        if (savePhoto) {
            cv::imwrite("images/lines.jpeg", frame);
            std::cout << "Photo captured and saved." << std::endl;
            savePhoto = false;  // Reset the flag
        }

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
