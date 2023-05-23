#include <opencv2/opencv.hpp>

using namespace cv;

int OpenCVTest()
{
    Mat image;
    image = imread("./images/t.jpg", IMREAD_GRAYSCALE);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}
