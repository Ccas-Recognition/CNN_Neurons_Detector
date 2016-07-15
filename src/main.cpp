
#include "common.h"
#include "ImagesRectsConverter.h"
#include "DatasetsMaker.h"

int main(int argc, char **argv)
{
	bool CONVERT_LABELED_DATA = 0;
	bool MAKE_DATASET = 1;

	path labeledImagesPath = "/data/Neurons/TrainingImages-master/LabeledImages";
	path datasetsDirectory = "/data/Neurons/TrainingImages-master/Datasets";

	if(CONVERT_LABELED_DATA)
	{
		ImagesRectsConverter().Convert("/data/Neurons/TrainingImages-master/CurrentImages",
			"/data/Neurons/TrainingImages-master/total/fg",
			labeledImagesPath);
	}

	if( MAKE_DATASET )
	{
		DatasetsMaker dataset;
		dataset.Make(labeledImagesPath/("list.txt"), labeledImagesPath, datasetsDirectory);
	}

	return 0;
}
