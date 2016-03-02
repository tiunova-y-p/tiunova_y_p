#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

const int alpha_max = 5;
const int beta_max = 125;
int alpha; // �������� ���������
int beta;  // �������� �������

int channel = 3; // ����� ������
Mat chanImg;     // ��������� �������   
vector<Mat> chans;  // ������ ������� 

static void on_trackbar(int, void*)
{
    switch (channel)
    {
    case 0: chanImg = chans[0]; break;
    case 1: chanImg = chans[1]; break;
    case 2: chanImg = chans[2]; break;
    case 3:
        merge(chans, chanImg);
        for (int y = 0; y < chanImg.rows; y++)
            for (int x = 0; x < chanImg.cols; x++)
                for (int c = 0; c < 3; c++)
                    chanImg.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(chanImg.at<Vec3b>(y, x)[c]) + beta);
        break;
    }
    // ���������� ���������� ������� ��������
    imshow("original", chanImg);
}

int main(int argc, char* argv[])
{
    alpha = 1;
    beta = 0;

    // ��� �������� ������� ������ ����������
    char* filename = argc == 2 ? argv[1] : "Penguins.jpg";

    // �������� ��������
    Mat imgSrc(imread(filename));

    // ���� ��� ����������� ��������
    cvNamedWindow("original", CV_WINDOW_AUTOSIZE);

    vector<Mat> channels(imgSrc.channels());
    split(imgSrc, &channels.at(0));
    chans = channels;

    // ���������� ��������
    imshow("original", imgSrc);

    createTrackbar("ChanNum", "original", &channel, 3, on_trackbar);
    createTrackbar("Contrast", "original", &alpha, alpha_max, on_trackbar);
    createTrackbar("Brightness", "original", &beta, beta_max, on_trackbar);

    // ��� ������� �������
    cvWaitKey(0);

    // ������� ����
    cvDestroyWindow("original");

    return 0;
}