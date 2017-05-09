// This demo will show you how the Vista-core-API can be used. It was test code I left for demonstration purposes
// so it hasn't been properely managed in any way. You'll see a lot of unecessary redundancy.
// The absolutely addresses to videos on my local machines directory should be replaced with your own.
// If you are using your own videos then make sure the input params to run are
// properly choosen. Details on what the input params should be are available in the carCounter.h file.

#include "main.h"

// Wrapper methods for creating instances of car counter and calling the run function on them.
// These can be threaded to make multiple instances of carCounters run at the same time.
// Ideally you should make a single wrapper capable of handing multiple params instead of creating
// multiple ones and defining the inputs to run() locally.

namespace cv
{
  using std::vector;
}

int main(int argc, const char * argv[]){
	char fileName[100] = "Standard_SCU3IU_2014-08-18_0700.002.avi";
	char saveImgTo[200] = "/home/vanya/Repos/vista/Vista-cmd-example/images";
	char dataBase[200] = "/home/vanya/Repos/vista/Vista-core-API/car_count_db";
	int bufferSize = 2;
	int minObjectSizeDay = 5000;
	int minObjectSizeNight = 10;
	int skip = 3;
	int learningTime = 240;
	int fps = 30;
	int expectedDist = 20;
	int horizontalBandwidth = 50;
	int nmixtures = 5;
	double backgroundratio = .6;
	bool detectShadows = false;
	bool online = true;

	cv::Point Sp1(150,100);
	cv::Point Sp4(250,100);
	cv::Point Sp2(150,400);
	cv::Point Sp3(250,400);

	cv::vector<cv::Point> startRegion;
	startRegion.push_back(Sp1);
	startRegion.push_back(Sp2);
	startRegion.push_back(Sp3);
	startRegion.push_back(Sp4);

	cv::Point Ep1(300,80);
	cv::Point Ep4(450,80);
	cv::Point Ep2(300,180);
	cv::Point Ep3(450,180);

	cv::vector<cv::Point> endRegion;
	endRegion.push_back(Ep1);
	endRegion.push_back(Ep2);
	endRegion.push_back(Ep3);
	endRegion.push_back(Ep4);

	cv::Point overlay1[1][4];
	overlay1[0][0] = cv::Point( 0, 0 );
	overlay1[0][1] = cv::Point( 0, 180 );
	overlay1[0][2] = cv::Point( 580, 0 );
	overlay1[0][3] = cv::Point( 580, 0 );

	const cv::Point* ppt[1] = { overlay1[0] };
	int npt[] = { 4 };

	cv::Point overlay2[1][4];
	overlay2[0][0] = cv::Point( 0, 320 );
	overlay2[0][1] = cv::Point( 0, 480 );
	overlay2[0][2] = cv::Point( 720, 480);
	overlay2[0][3] = cv::Point( 720, 0 );

	const cv::Point* ppt2[1] = { overlay2[0] };
	int npt2[] = { 4 };

	carCounter CC(1,false);
	CC.run(bufferSize,minObjectSizeDay,minObjectSizeNight,skip,learningTime,fileName,saveImgTo,dataBase,fps,expectedDist,horizontalBandwidth,RUN_ONLINE,
		*ppt,*ppt2,npt,npt2,
		USE_MOG2_ON,nmixtures,backgroundratio,
		DETECT_SHADOWS_ON,SHOW_LAST_CAR_ON,SHOW_BOUNDBOX_ON,SHOW_PREDICTION_ON,SHOW_LATEST_PATHS_ON,SHOW_TRANSIT_LEDGER_ON,SHOW_REGION_MONITORS_ON,
		SHOW_PATH_OF_CAR_X_OFF,USE_RESIZED_WITH_OVERLAYS_FRAME, startRegion, endRegion);
}
