#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

Mat img_src, img_blur, img_gray, dst, detected_edges;

int lowBlurWin = 7;
int const max_BlurWin = 21;
int lowThreshold = 50;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;

static void BlurImage(int, void*)
{
    if (lowBlurWin < 1) lowBlurWin = 1;
    blur(img_gray, img_blur, Size(lowBlurWin, lowBlurWin));
    imshow("Blur", img_blur);
}

static void CannyThreshold(int, void*)
{
    blur(img_gray, detected_edges, Size(3, 3)); // Устраняем шум с помощью размытия
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
    dst = Scalar::all(0);
    img_src.copyTo(dst, detected_edges);
    imshow("Edges", dst);
}

int main(int argc, char* argv[])
{
    // имя картинки задаётся первым параметром
    char* filename = (argc == 2 ? argv[1] : "Penguins.jpg");

    img_src = imread(filename);
    if (img_src.empty())
    {
        return -1;
    }
    namedWindow("Source", WINDOW_AUTOSIZE);
    imshow("Source", img_src);

    dst.create(img_src.size(), img_src.type());

    // Конвертируем исходное цветное изображение в оттенки серого
    cvtColor(img_src, img_gray, COLOR_BGR2GRAY);
    namedWindow("Gray", WINDOW_AUTOSIZE);
    imshow("Gray", img_gray);

    // Создаем параметры для размытого изображения
    Mat img_blur(img_gray);
    namedWindow("Blur", WINDOW_AUTOSIZE);
    createTrackbar("Blur win.size:", "Blur", &lowBlurWin, max_BlurWin, BlurImage);
    BlurImage(0, 0);

    // Задаем параметры для выделения контуров
    namedWindow("Edges", WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", "Edges", &lowThreshold, max_lowThreshold, CannyThreshold);
    CannyThreshold(0, 0);

    waitKey(0);

    return 0;

}
