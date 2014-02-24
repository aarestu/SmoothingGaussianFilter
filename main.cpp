#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void gaussianFilter(const Mat& src, Mat& result, int besarKernel, double delta);
void gaussianKernelGenerator(Mat &result, int besarKernel, double delta);
void rgb2gray(const Mat src, Mat &result);

int main(int argc, char *argv[])
{
    Mat src = imread("D:\\Project\\C++\\CitraDigital\\lena.jpg");

    rgb2gray(src, src);

    Mat gausianFilter;

    gaussianFilter(src, gausianFilter, 7, 1);

    namedWindow("asli");
    imshow("asli", src);

    namedWindow("gaussian");
    imshow("gaussian", gausianFilter);

    waitKey(0);

}

void gaussianFilter(const Mat& src, Mat& result, int besarKernel, double delta)
{
    Mat kernel;

    //inisialisasi kernel gaussians
    gaussianKernelGenerator(kernel, besarKernel, delta);

    int filterOffset = besarKernel / 2;

    result = Mat::zeros(src.rows - filterOffset*2, src.cols - filterOffset*2, src.type());

    double sumKeabuan;

    for(int ysrc = filterOffset; ysrc < src.rows - filterOffset; ++ysrc){
        for(int xsrc = filterOffset; xsrc < src.cols - filterOffset; ++xsrc){

            sumKeabuan = 0;

            for(int ykernel = -filterOffset; ykernel <= filterOffset; ++ykernel){
                for(int xkernel = -filterOffset; xkernel <= filterOffset; ++xkernel){

                    sumKeabuan += src.at<uchar>(ysrc + ykernel, xsrc + xkernel) * kernel.at<double>(filterOffset + ykernel, filterOffset + xkernel);
                }
            }

            result.at<uchar>(ysrc - filterOffset, xsrc - filterOffset) = sumKeabuan;
        }
    }
}

void gaussianKernelGenerator(Mat &result, int besarKernel, double delta)
{
    int kernelRadius = besarKernel / 2;
    result = Mat_<double>(besarKernel, besarKernel);

    double pengali = 1 / (2 * (22 / 7) * delta * delta);
    for(int filterY = - kernelRadius; filterY <= kernelRadius; filterY++){
        for(int filterX = - kernelRadius; filterX <= kernelRadius; filterX++){

            result.at<double>
                    (filterY + kernelRadius, filterX + kernelRadius) =  exp(-( ( ( filterX * filterX ) + ( filterY * filterY )  ) / (delta * delta * 2) )) * pengali;

        }
    }
}

void rgb2gray(const Mat src, Mat &result)
{
    CV_Assert(src.depth() != sizeof(uchar)); //harus 8 bit

    result = Mat::zeros(src.rows, src.cols, CV_8UC1); //buat matrik 1 chanel
    uchar data;

    if(src.channels() == 3){

        for( int i = 0; i < src.rows; ++i)
            for( int j = 0; j < src.cols; ++j )
            {
                data = (uchar)(((Mat_<Vec3b>) src)(i,j)[0] * 0.0722 + ((Mat_<Vec3b>) src)(i,j)[1] * 0.7152 + ((Mat_<Vec3b>) src)(i,j)[2] * 0.2126);

                result.at<uchar>(i,j) = data;
            }


    }else{

        result = src;
    }

}
