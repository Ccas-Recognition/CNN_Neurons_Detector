#ifndef SRC_DATASETSMAKER_H_
#define SRC_DATASETSMAKER_H_

#include "common.h"

class DatasetsMaker
{
public:
	string imagesExtension = ".png";

	void Make(path listPath, path labeledImagesDirectory, path outputDatasetDirectory);
};

#endif /* SRC_DATASETSMAKER_H_ */
