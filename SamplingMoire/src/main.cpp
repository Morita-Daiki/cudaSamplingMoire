#include <getopt.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

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
    std::cout << "source:" << source_file << std::endl;
    std::cout << "out:" << output_file << std::endl;
    std::cout << "num:" << num << std::endl;
    std::cout << "direction:" << direction << std::endl;
    return 0;
    // if ((argc - 1) % 2 != 0)
    // {
    //     printf("usage: SamplingMoire.out <Video_Path>\n");
    //     return -1;
    // }
    // cv::Mat frame;
    // cv::VideoCapture video;
    // video.open(argv[1]);
    // if (!video.isOpened())
    //     return 0;

    // cv::VideoWriter writer;
    // int w, h, fourcc;
    // double fps;
    // fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    // w = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
    // h = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
    // fps = video.get(cv::CAP_PROP_FPS);
    // writer.open(argv[2], fourcc, fps, cv::Size(w, h));

    // cv::Mat image;
    // while (true)
    // {
    //     video >> image;
    // }
}