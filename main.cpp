#include "lucia.h"
/*
using namespace cv;

int main(int argc, char** argv) {
  feedForward n1(2, 1, "100");

  vector<vector<float> > input;
  input.push_back({0.0f, 0.0f});
  input.push_back({0.0f, 1.0f});
  input.push_back({1.0f, 0.0f});
  input.push_back({1.0f, 1.0f});

  vector<vector<float> > output;
  output.push_back({0.0f});
  output.push_back({1.0f});
  output.push_back({1.0f});
  output.push_back({0.0f});
  
  n1.runTraining(input, output, 100000);
  n1.loadWeights("net.txt");
  n1.printv(n1.makeClean(n1.calcOutput({1.0f, 1.0f})));
  
  
  vector<vector<float> > input;
  int num_input = 0;
  for(uint n = 0; n < 2; n++) {
    vector<float> vec_img;

    Mat img;
    Mat dst;
    Mat gray;
    string filename = "datasetImg/auto_" + to_string(n) + ".jpg";
    cout<<filename<<endl;
    img = imread(filename.c_str());
    resize(img, dst, Size(150, 150));
    cvtColor(dst, gray, CV_BGR2GRAY);

    for(int i = 0; i < gray.rows; i++) {
      for(int j = 0; j < gray.cols; j++) {
        Scalar intensity = gray.at<uchar>(i, j);
        vec_img.push_back(((float)intensity[0]) / 255.0f);
      }
    }

    input.push_back(vec_img);
    num_input = gray.rows * gray.cols;
  }

  vector<vector<float> > output;
  output.push_back({0.0f});
  output.push_back({1.0f});
  
  feedForward n2(num_input, 1, "1000");
  n2.runTraining(input, output);

  return 0;
}*/

int main(int argc, char *argv[]) {
  int FREQ = 22050;
  int CAP_SIZE = 2048;

  short buffer[FREQ * 2];
  ALCint num_samples;

  ALCdevice *device = alcCaptureOpenDevice(NULL, FREQ, AL_FORMAT_MONO16, (int)((float)FREQ/2.0f) );
  if(device == nullptr) {
  	cout<<"could not open device";
	  return 1;
  }
  
  cout<<alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER)<<endl;
  cout<<alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER)<<endl;
  cout<<alcGetString(NULL, ALC_DEVICE_SPECIFIER)<<endl;
  cout<<alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER)<<endl;
  cout<<alcGetString(NULL, ALC_EXTENSIONS)<<endl;

  alcCaptureStart(device);

  int last = 0;
  int minV = 0;
  int maxV = 0;
  while (true) {
    alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, sizeof(ALint), &num_samples);
    
	  if(num_samples > CAP_SIZE) {
	  	alcCaptureSamples(device, buffer, num_samples);

		  if(last != abs((int)*buffer)) {
		  	last = (int)((float)abs((int)*buffer) * 0.01f);

			  if(last < minV)
			  	minV = last;
			  if(last > maxV)
		  		maxV = last;

			  if(last > 100) {
			  	for(int i = 100; i < last; i++)
				  	cout<<"*";
				  cout<<" "<<num_samples<<endl;
			  }
		  }
	  }
  }
       
  alcCaptureStop(device);
  alcCaptureCloseDevice(device);
  return 0;
}
