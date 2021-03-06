#include <Core\Core.h>

#include <stdio.h>
#include <stdlib.h>

#include <opencv2\opencv.hpp>


void loadImageFromHarddisk(char* path)
{
	bool errorTriggered = false;

	VisionCore::Core* visionCore = new VisionCore::Core(path);

	if (visionCore->load())
	{
		cv::Mat image = visionCore->getInput();

		if (image.rows > 1 && image.cols > 1)
		{
			cv::imshow("testImage", image);

			cv::waitKey(0);
		}
		else
			errorTriggered = true;
	}
	else
		errorTriggered = true;

	if (errorTriggered == true)
		printf("Something went wrong (maybe the file you specified was not found....)\n\n");

	delete(visionCore);
}

void liveImageFeed(int ID)
{
	VisionCore::VCStruct::VideoSettings videoSettings = VisionCore::VCStruct::VideoSettings();
	videoSettings.frame_width = 1920;
	videoSettings.frame_height = 1080;
	videoSettings.fps = 30;

	VisionCore::Core* visionCore = new VisionCore::Core(ID, videoSettings);

	visionCore->setSaveVideoToHDD(true);

	visionCore->addOperator(VisionCore::VCEnum::Operation::FILTER_GAUSSIAN_BLUR);
	//visionCore->addOperator(VisionCore::VCEnum::Operation::FILTER_AVERAGE);
	//visionCore->addOperator(VisionCore::VCEnum::Operation::FILTER_MEDIAN_BLUR);
	//visionCore->addOperator(VisionCore::VCEnum::Operation::FILTER_BILATERLAL);

	visionCore->run();

	delete(visionCore);
}

void notSoLiveImageFeed(char *path)
{
	VisionCore::Core* visionCore = new VisionCore::Core(path);

	visionCore->addOperator(VisionCore::VCEnum::Operation::FILTER_GAUSSIAN_BLUR);

	visionCore->run();

	delete(visionCore);
}

int main(int argc, char** argv)
{
	//loadImageFromHarddisk("test1.jpg");
	liveImageFeed(0);
	//notSoLiveImageFeed("video.avi");




 	system("pause");
	return 0;
}