#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void gaussianFilter(Mat& src, Mat& result, int besarKernel, double delta);
void gaussianKernelGenerator(Mat &result, int besarKernel, double delta);
Mat rgb2gray(Mat& src);

int main(int argc, char *argv[])
{
    Mat src = imread("D:\\Project\\C++\\CitraDigital\\lena.jpg");

    src = rgb2gray(src);

    Mat gausianFilter;

    gaussianFilter(src, gausianFilter, 7, 1);

    namedWindow("asli");
    imshow("asli", src);

    namedWindow("gaussian");
    imshow("gaussian", gausianFilter);

    waitKey(0);

}

void gaussianFilter(Mat& src, Mat& result, int besarKernel, double delta)
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

Mat rgb2gray(Mat& src)
{
    CV_Assert(src.depth() != sizeof(uchar)); //harus 8 bit

    Mat mc1(src.rows, src.cols, CV_8UC1); //buat matrik 1 chanel
    uchar data;

    if(src.channels() == 3){
        Mat_<Vec3b> _I = src;

        for( int i = 0; i < src.rows; ++i)
            for( int j = 0; j < src.cols; ++j )
            {
                data = (uchar)(_I(i,j)[0] * 0.0722 + _I(i,j)[1] * 0.7152 + _I(i,j)[2] * 0.2126);

                mc1.at<uchar>(i,j) = data;

            }

        src = _I;
        return mc1;

    }else{

        return src;
    }

}
