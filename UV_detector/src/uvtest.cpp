#include <opencv2/opencv.hpp>
#include <math.h>
#include <vector>
#include <time.h>
#include <UV_detector.h>
#include <kalman_filter.h>
#include <Eigen/Dense>

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main()
{

    // detector
    UVdetector my_detector;

    // fixed 1134 and move 1435
    // for(int file_index = 1; file_index < 1350; file_index++)
    // {
        // read file from dataset
    // ostringstream temp;
    // temp << file_index;
    // string filenamergb = "../../dataset/fixed/rgb" + temp.str() + ".png";
    // Mat rgb = imread(filenamergb, -1);
    // imshow("RGB", rgb);
    // string filenamedep = "../../dataset/cyberzoo_move/dep" + temp.str() + ".png";
    string filenamedep = "dataset/depth.png";
    Mat depth(480, 640, CV_16UC1); // should be 3 channels?
    // Mat depth(480, 640, CV_16UC1);

    // start timer
    clock_t startTime = clock();

    depth = imread(filenamedep, IMREAD_GRAYSCALE); //-1);
    imshow("Depth", depth);
    waitKey(0);

    // read depth map
    my_detector.readdata(depth);

    // process
    my_detector.detect();

    // tracking
    // my_detector.track();

    // stop timer
    clock_t endTime = clock();
    clock_t clockTicksTaken = endTime - startTime;
    double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
    printf("Time taken: %0.2f s \n", timeInSeconds);

    // visualization
    my_detector.display_depth();
    // printf("No issues with displaying depth!\n");
    my_detector.display_U_map();
    // printf("No issues with displaying u-depth map!\n");
    my_detector.display_bird_view();
    // printf("No issues with displaying bird view!\n");

    // for segmentation
    uint8_t histSize = my_detector.depth.rows / my_detector.row_downsample;
    uint8_t bin_width = ceil((my_detector.max_dist - my_detector.min_dist) / float(histSize));
    for(int d = 0; d < my_detector.bounding_box_U.size(); d++)
    {
        
    }
    // waitKey(15);
    // }
}