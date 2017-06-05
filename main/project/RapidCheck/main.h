#ifndef MAIN_H
#define MAIN_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <time.h>
#include "App.h"
#include "target.h"
#include "frame.h"
#include "config.h"
#include "database.h"
#include "RCTrajectory.h"

using cv::VideoCapture;
using cv::Scalar;
using cv::RNG;

// set basic colors
#define WHITE Scalar(255,255,255)
#define BLACK Scalar(0,0,0)
#define BLUE Scalar(255,0,0)
#define GREEN Scalar(0,255,0)
#define RED Scalar(0,0,255)
#define CYAN Scalar(255,255,0)

void showDetection(App app);
void showTrackletClusters(App app);
void showTracklet(App app);
void buildAndShowTrajectory(App app);
void compareSimilarity(App app);
void showTrajectory();

// Database

static DB db;

#endif