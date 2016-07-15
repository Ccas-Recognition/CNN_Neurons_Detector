/*
* Copyright (c) 2015 Accenture - All rights reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited.
* Proprietary and confidential.
*/
#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <boost/lexical_cast.hpp>

#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>

#include <map>
#include <sys/wait.h>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

#define GSULOG cout

using namespace std;
using namespace cv;
using namespace boost::filesystem;

vector<string> &split(const string &s, char delim, vector<string> &elems);

template<class TPoint, class TRect>
bool IsInsideRect(TPoint point, TRect rect)
{
	return point.x >= rect.x && point.x < (rect.x + rect.width) && point.y >= rect.y && point.y < (rect.y + rect.height);
}

void WriteTiff(const string& filename, const Mat& m);

#endif /* SRC_COMMON_H_ */
