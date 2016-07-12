#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**)
{
    VideoCapture cap(6); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        {
            cout<<"Camera not detected"<<endl;
            return -1;
        }

    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        // do any processing
        imwrite("self.png", frame);
        if(waitKey(30) >= 0) break;   // you can increase delay to 2 seconds here
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}