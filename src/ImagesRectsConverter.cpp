#include "ImagesRectsConverter.h"

void ImagesRectsConverter::Convert(path imagesDirectory, path rectsDirectory, path outputDirectory)
{
	vector<path> v;

	copy(directory_iterator(rectsDirectory), directory_iterator(), back_inserter(v));
	sort(v.begin(), v.end());

	map< string, vector<Rect> > imageToRectsMapping;

	for (vector<path>::const_iterator it (v.begin()); it != v.end(); ++it)
	{
		if(it->extension() == ".jpg")
		{
			string rectName = it->stem().string();
			vector<string> rectNameParts;
			split(rectName, '_', rectNameParts);

			Rect rect;
			rect.x = stoi(rectNameParts[3]);
			rect.y = stoi(rectNameParts[4]);
			rect.width = stoi(rectNameParts[5]);
			rect.height = stoi(rectNameParts[6]);

			imageToRectsMapping[rectNameParts[0]].push_back(rect);
		}
	}

	int index = 1;
	for (map<string, vector<Rect> >::const_iterator it (imageToRectsMapping.begin()); it != imageToRectsMapping.end(); ++it)
	{
		string imageName = it->first;
		cout << imageName << "" << endl;
		const vector<Rect> &rects = it->second;

		Mat image = imread( (imagesDirectory / (imageName + ".jpg" )).string() );
		Mat imageWithRects = image.clone();

		string newImageName = boost::lexical_cast<string>(index);

		ofstream rectsStream( (outputDirectory / (newImageName + ".txt" )).string());
		rectsStream << rects.size() << endl;
		for(int i=0; i<(int) rects.size(); ++i)
		{
			Rect rect = rects[i];
			rectsStream << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << endl;
			rectangle( imageWithRects, rect, Scalar(0, 255, 0), 1 );
		}

		imwrite( (outputDirectory / (newImageName + ".png" )).string(), image);
		imwrite( (outputDirectory / (newImageName + "_rects.png" )).string(), imageWithRects);

		index += 1;
	}
	cout << "Convert is done.";
}
