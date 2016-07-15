#ifndef SRC_SCALESPACE_H_
#define SRC_SCALESPACE_H_

#include "common.h"

struct ScaleSpace
{
	vector<int> rectSizes = {24, 36, 48, 64};
	int rectSize = 36;
	int rectStride = 9;

	vector<Rect> GetRects(Rect imageSize);
};

#endif /* SRC_SCALESPACE_H_ */
