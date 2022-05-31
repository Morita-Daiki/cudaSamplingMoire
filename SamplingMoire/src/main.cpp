#include <getopt.h>

#include <stdio.h>
#include <iostream>
#include <numeric>

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/structured_light.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

void print_progress(int current, int size)
{
    std::cout << "\n"
              << std::setw(4) << current + 1
              << " / " << size
              << " =" << std::setw(4) << int(100.0 * current / (size - 1))
              << " % "
              << "complete";
}

int main(int argc, char **argv)
{
    std::string source_file = "default_source_file.mp4",
                output_file = "default_output_file.mp4";
    int num = 2, direction = 0;

    struct option longopts[] = {
        {"sourceFile", required_argument, NULL, 's'},
        {"outFile", required_argument, NULL, 'o'},
        {"numSampling", required_argument, NULL, 'n'},
        {"direction", required_argument, NULL, 'd'},
        {0, 0, 0, 0}};
    int opt, longindex;
    while ((opt = getopt_long(argc, argv, "s:o:n:d", longopts, &longindex)) != -1)
    {
        printf("opt info %d %s <-- %s\n", longindex, longopts[longindex].name, optarg);
        switch (opt)
        {
        case 's':
            source_file = std::string(optarg);
            break;
        case 'o':
            output_file = std::string(optarg);
            break;
        case 'n':
            num = std::stoi(optarg);
            break;
        case 'd':
            direction = std::stoi(optarg);
            break;
        case 'h':
        case '?':
            std::cout << "help menu";
            return 1;
        default:
            abort();
        }
    }
    std::cout << "\n";
    std::cout << "Source File Name  :" << source_file << std::endl;
    std::cout << "Output File Name  :" << output_file << std::endl;
    std::cout << "Sampling Size[px] :" << num << std::endl;
    std::cout << "Sampling Direction:" << direction << std::endl;

    cv::Mat frame;
    cv::VideoCapture video;
    video.open(source_file);
    std::cout << "\nOpening the Source File" << std::endl;

    if (!video.isOpened())
    {
        std::cout << "Can't open the Source File" << std::endl;
        return 0;
    }

    cv::VideoWriter writer;
    int width, height, fourcc, frame_length;
    double fps;
    fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
    height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
    fps = video.get(cv::CAP_PROP_FPS);
    frame_length = video.get(cv::CAP_PROP_FRAME_COUNT);
    // fps = 1;
    writer.open(output_file, fourcc, fps, cv::Size(width, height), false);

    std::cout << "frame width :" << width << std::endl;
    std::cout << "frame height:" << height << std::endl;
    std::cout << "frame length:" << frame_length << std::endl;
    std::cout << "frame / sec :" << fps << std::endl;

    cv::Mat image, gray, gray32;
    cv::cuda::GpuMat index_image_on_gpu[num * 2];
    cv::cuda::GpuMat gray_on_gpu, scaled_on_gpu, filterd_on_gpu32, gray_on_gpu32, filterd_on_gpu;

    cv::Mat kernel_re, kernel_im;
    int kernel_size = num * 2 - 1;
    kernel_re = cv::Mat::ones(1, kernel_size, CV_32FC1);
    kernel_im = cv::Mat::ones(1, kernel_size, CV_32FC1);

    for (int i = 0; i < kernel_size; i++)
    {
        float x = i - num + 1;
        float weight = (num - abs(x)) / num / num;

        kernel_re.at<_Float32>(0, i) = weight * cos(float(x) / num * 2 * M_PI);
        kernel_im.at<_Float32>(0, i) = weight * sin(float(x) / num * 2 * M_PI);
    }
    std::cout << kernel_re << std::endl;
    std::cout << kernel_im << std::endl;

    std::cout << "start loop";

    for (int counter = 0; counter < frame_length; counter++)
    {
        video >> image;

        cv::cuda::GpuMat image_on_gpu(image);
        cv::cuda::cvtColor(image_on_gpu, gray_on_gpu, cv::COLOR_BGR2GRAY);
        gray_on_gpu.convertTo(gray_on_gpu32, CV_32FC1);
        cv::Ptr<cv::cuda::Filter> filter =
            cv::cuda::createLinearFilter(CV_32FC1, CV_32FC1, kernel_re, cv::Point(-1, -1), cv::BORDER_CONSTANT);
        filter->apply(gray_on_gpu32, filterd_on_gpu32);

        // cv::cuda::createBoxFilter(gray_on_gpu,filterd_on_gpu,cv::Size(num*2,1))
        // cv::cuda::

        // if (counter == 0)
        // for (int i = 0; i < 2 * num; i++)
        // {
        //     index_image_on_gpu[i] = cv::cuda::GpuMat(gray_on_gpu, cv::Rect(i, 0, width - i, height)).clone();
        //     index_image_on_gpu[i].download(gray);
        //     cv::imshow("gray", gray);
        //     cv::waitKey(10);
        // }

        // cv::cuda::resize(gray_on_gpu, scaled_on_gpu, cv::Size(1000, 1000));
        filterd_on_gpu32.download(gray32);
        gray32.convertTo(gray, CV_8U);

        cv::imshow("gray", gray);
        cv::waitKey(1);

        if (counter % 10 == 9 || counter == (frame_length - 1))
            print_progress(counter, frame_length);

        writer << gray;
    }
    std::cout << "\nend loop" << std::endl;

    return 0;
}
