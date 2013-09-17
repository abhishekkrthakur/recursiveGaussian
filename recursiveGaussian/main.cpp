//
//  main.cpp
//  recursiveGaussian
//
//  Created by Abhishek Kumar Thakur on 1/7/13.
//  Copyright (c) 2013 Abhishek Kumar Thakur. All rights reserved.
//

#include <iostream>
#include "math.h"
#include "vector"
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sys/time.h>
#include <ctime>
#include "recur.h"


using namespace cv;
using namespace std;


int main(int argc, const char * argv[])
{
    
    // Input image
    Mat input = imread("/Users/abhishek/Documents/image\ processing/bauckhage.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    
    float ap[5],bp[5],an[5], bn[5];
    
    // Adjust Sigma
    float sigma = 10.0f;
    Mat resImg, resYp, resYn;
    
    // Coefficients for recirsive gaussian
    calcCoeff(sigma, ap, bp, an, bn);
    
    // output Image
    Mat output;
    output = Mat(input.rows, input.cols, CV_32FC1);
    vector<double> horizontalVec, causal,noncausal, sumvec, normvector,causal1, noncausal1;
    copyMakeBorder(input, output, 3, 3, 3, 3, BORDER_REPLICATE); // Create Border
    
    // Final Output Image
    Mat final_output;
    
    output.convertTo(final_output, CV_32FC1);
    
    int height = final_output.rows;
    int width = final_output.cols;
    
    clock_t recur_time = clock();
    // Processing Starts Here:-
    for(int i = 0; i < height; i++)
    {
        horizontalVec = createHorizontalVec(final_output, i);
        causalVec(horizontalVec,causal1, ap, bp);
        noncausalVec(horizontalVec,noncausal1, an, bn);
        for(int j = 0; j < width; j++)
        {
            final_output.at<float>(i,j) = (causal1[j] + noncausal1[j]);
        }
    }
    
    final_output = final_output.t();
    
    height = final_output.rows;
    width = final_output.cols;
    
    for(int i = 0; i < height; i++)
    {
        horizontalVec = createHorizontalVec(final_output, i);
        causalVec(horizontalVec,causal1, ap, bp);
        noncausalVec(horizontalVec,noncausal1, an, bn);
        for(int j = 0; j < width; j++)
        {
            final_output.at<float>(i,j) = (causal1[j] + noncausal1[j]);
        }
    }
    
    final_output = final_output.t();
    // Processing Ends Here
    printf("Time taken: %.4fs\n", (double)(clock() - recur_time)/CLOCKS_PER_SEC);
    // Normalize Image
    normalize(final_output, final_output,0,255,NORM_MINMAX,CV_8UC1);
    
    
    Mat output_cropped;
    
    // Cropping the output Image
    output_cropped = Mat(input.rows, input.cols, CV_8UC1);
    
    for(int j = 3; j < final_output.rows-3; j++)
        for(int i = 3; i < final_output.cols-3; i++)
            output_cropped.at<uchar>(j-4,i-4) = final_output.at<uchar>(j,i);
    
    imshow("input", input);             // Show input
    imshow("output", output_cropped);   // Show Output Image
    
    waitKey();
    return 0;
}

