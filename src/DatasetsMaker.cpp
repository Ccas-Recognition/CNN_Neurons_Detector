#include "DatasetsMaker.h"

void DatasetsMaker::Make(path listPath, path labeledImagesDirectory, path outputDatasetDirectory)
{
	ifstream listStream(listPath.string());

	vector<string> imagesNames;
	while(!listStream.eof())
	{
		string imageName;
		listStream >> imageName;
		if(imageName == "" || listStream.eof())
			break;

		imagesNames.push_back(imageName);
	}

	for( int i=0; i<(int) imagesNames.size(); ++i )
	{
		Mat image = imread((labeledImagesDirectory/(imagesNames[i] + imagesExtension )).string() );
	}
}
