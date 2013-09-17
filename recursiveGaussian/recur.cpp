//
//  recur.cpp
//  recursiveGaussian
//
//  Created by Abhishek Kumar Thakur on 1/14/13.
//  Copyright (c) 2013 Abhishek Kumar Thakur. All rights reserved.
//

#include "recur.h"


// Calculate coffecients of Recursive Gaussian Filter
void calcCoeff(float sigma, float* ap, float* bp, float* an, float* bn)
{
    
    ap[0] = alpha1 + alpha2;
    ap[1] = exp(-gamma2/sigma)*(beta2*sin(omega2/sigma) - (alpha2 + 2*alpha1)*cos(omega2/sigma)) + \
    exp(-gamma1/sigma)*(beta1*sin(omega1/sigma) - (2*alpha2 + alpha1)*cos(omega1/sigma));
    ap[2] = 2*exp(-gamma1/sigma - gamma2/sigma)*((alpha1+alpha2)*cos(omega2/sigma)*cos(omega1/sigma) -\
                                                 beta1*cos(omega2/sigma)*sin(omega1/sigma) - cos(omega1/sigma)*beta2*sin(omega2/sigma))\
    + alpha2*exp(-2*gamma1/sigma) + alpha1*exp(-2*gamma2/sigma);
    ap[3] = exp(-gamma2/sigma - 2*gamma1/sigma)*(beta2*sin(omega2/sigma) - alpha2*cos(omega2/sigma)) +\
    exp(-gamma1/sigma - 2*gamma2/sigma)*(beta1*sin(omega1/sigma) - alpha1*cos(omega1/sigma));
    ap[4] = 0;
    
    bp[4] = exp(-2*gamma1/sigma - 2*gamma2/sigma);
    bp[3] = -2*cos(omega1/sigma)*exp(-gamma1/sigma-2*gamma2/sigma) - 2*cos(omega2/sigma)*exp(-gamma2/sigma-2*gamma1/sigma);
    bp[2] = 4*cos(omega2/sigma)*cos(omega1/sigma)*exp(-gamma1/sigma - gamma2/sigma) + exp(-2*gamma2/sigma) + exp(-2*gamma1/sigma);
    bp[1] = -2*exp(-gamma2/sigma)*cos(omega2/sigma) - 2*exp(-gamma1/sigma)*cos(omega1/sigma);
    
    
    bp[0] = 1;
    for (int i=0; i<4;i++)
    {
        bn[i] = bp[i];
        an[i] = ap[i] - bp[i]*ap[0];
    }
    bn[4] = bp[4];
    an[4] = - bp[4]*ap[0];
}

// Create a temporary vector for processing
vector<double> createHorizontalVec(Mat Img, int rowNum)
{
    vector<double> horzVec;
    for(int i = 0; i < Img.cols; i++)
    {
        horzVec.push_back((double)Img.at<float>(rowNum,i));
    }
    return horzVec;
}


// Causal Vector
void causalVec(vector<double> horzVec, vector<double> &causal, float ap[5], float bp[5])
{
    
    causal = horzVec;
    causal[0] = (ap[0] * horzVec[0]);
    causal[1] = (ap[0] * horzVec[1]) + (ap[1] * horzVec[0]) - (bp[1] * causal[0]);
    causal[2] = (ap[0] * horzVec[2]) + (ap[1] * horzVec[1]) + (ap[2] * horzVec[0]) - (bp[1] * causal[1]) - (bp[2] * causal[0]);
    causal[3] = (ap[0] * horzVec[3]) + (ap[1] * horzVec[2]) + (ap[2] * horzVec[1]) + (ap[3] * horzVec[0]) - (bp[1] * causal[2]) - (bp[2] * causal[1]) - (bp[3] * causal[0]);
    
    for(int i = 4; i <= horzVec.size(); i++)
    {
        causal[i] = (ap[0] * horzVec[i]) + (ap[1] * horzVec[i-1]) + (ap[2] * horzVec[i-2]) + (ap[3] * horzVec[i-3]) - (bp[1] * causal[i-1]) - (bp[2] * causal[i-2]) - (bp[3] * causal[i-3]) -(bp[4] * causal[i-4]);
    }
    
    //return causal;
    
}

// Non Causal Vector
void noncausalVec(vector<double> horzVec, vector<double> &noncausal, float an[5], float bn[5])
{
    noncausal = horzVec;
    int len = (int)horzVec.size();
    noncausal[len-1] = an[1] * horzVec[len];
    noncausal[len-2] = (an[1] * horzVec[len-1]) + (an[2] * horzVec[len]) - (bn[1] * noncausal[len-1]);
    noncausal[len-3] = (an[1] * horzVec[len-2]) + (an[2] * horzVec[len-1]) + (an[3] * horzVec[len]) - (bn[1] * noncausal[len-2]) - (bn[2] * noncausal[len-1]);
    noncausal[len-4] = (an[1] * horzVec[len-3]) + (an[2] * horzVec[len-2]) + (an[3] * horzVec[len-1]) + (an[4] * horzVec[len]) - (bn[1] * noncausal[len-3]) - (bn[2] * noncausal[len-2]) - (bn[3] * noncausal[len-1]);
    
    for(int i = len-5; i >= 0; i--)
    {
        noncausal[i] = (an[1] * horzVec[i+1]) + (an[2] * horzVec[i+2]) + (an[3] * horzVec[i+3]) + (an[4] * horzVec[i+4]) - (bn[1] * noncausal[i+1]) - (bn[2] * noncausal[i+2]) - (bn[3] * noncausal[i+3]) -(bn[4] * noncausal[i+4]);
    }
    
}

