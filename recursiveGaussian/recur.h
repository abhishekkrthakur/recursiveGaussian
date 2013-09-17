//
//  recur.h
//  recursiveGaussian
//
//  Created by Abhishek Kumar Thakur on 1/14/13.
//  Copyright (c) 2013 Abhishek Kumar Thakur. All rights reserved.
//

#ifndef __recursiveGaussian__recur__
#define __recursiveGaussian__recur__

#define alpha1 1.6800
#define alpha2 -0.6803
#define beta1 3.7350
#define beta2 -0.2598
#define gamma1 1.7830
#define gamma2 1.7230
#define omega1 0.6318
#define omega2 1.9970

#include <iostream>
#include "math.h"
#include "vector"
#include <iomanip>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sys/time.h>
#include <ctime>

using namespace cv;
using namespace std;

void calcCoeff(float sigma, float* ap, float* bp, float* an, float* bn);
vector<double> createHorizontalVec(Mat Img, int rowNum);
void causalVec(vector<double> horzVec, vector<double> &causal, float ap[5], float bp[5]);
void noncausalVec(vector<double> horzVec, vector<double> &noncausal, float an[5], float bn[5]);
#endif /* defined(__recursiveGaussian__recur__) */
