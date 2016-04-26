#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int i, width = 600, height = 480;
int lineType = LINE_8; 
//int thickness = 1;
int thickness = CV_FILLED;

void fillarea(Mat src, CvPoint seed, CvScalar color)
{
    Rect comp;

    floodFill(src, seed, color, &comp,
        cvScalarAll(10), // минимальная разность
        cvScalarAll(10), // максимальная разность
        CV_FLOODFILL_FIXED_RANGE + 8);
}


int main(int argc, char* argv[])
{
    //namedWindow("Source", WINDOW_AUTOSIZE);

    Mat image3С = Mat::zeros(height, width, CV_8UC3);

    CvRect rect1 = cvRect(0, 0, width, height / 3);
    CvScalar color1 = CV_RGB(255, 255, 255);
    rectangle(image3С, rect1, color1, thickness, lineType);

    CvRect rect2 = cvRect(0, height / 3, width, height / 3);
    CvScalar color2 = CV_RGB(127, 127, 127);
    rectangle(image3С, rect2, color2, thickness, lineType);

    CvRect rect3 = cvRect(0, height * 3 / 4, width, height / 3);
    CvScalar color3 = CV_RGB(0, 0, 0);
    rectangle(image3С, rect3, color3, thickness, lineType);

    CvRect rect4 = cvRect(width / 4, height / 6, width / 2, height / 3);
    CvScalar color4 = CV_RGB(0, 0, 0);
    rectangle(image3С, rect4, color4, thickness, lineType);

    CvRect rect5 = cvRect(width / 4, height / 2, width / 2, height / 3);
    CvScalar color5 = CV_RGB(255, 255, 255);
    rectangle(image3С, rect5, color5, thickness, lineType);

    imshow("SyntImage", image3С);

    waitKey(0);

    return 0;

}
