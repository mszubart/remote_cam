#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <xs/xs.hpp>

using namespace cv;
using namespace std;

#include <time.h>
#include <unistd.h>

int main(int ac, char** av) {
    int hwm = 10;
    int source_index = 0;
    
    xs::context_t ctx;
    xs::socket_t sock(ctx, XS_PUB);

    sock.setsockopt(XS_SNDHWM, &hwm, sizeof(hwm));
    sock.bind("tcp://*:5555");

    VideoCapture cap;
    cap.open(source_index);

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 352);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 288);

    if (!cap.isOpened()) {
        cerr << "Cant open device: " << source_index << "\n";
        exit(EXIT_FAILURE);
    }

    CvSize siz;
    siz.width = (int) cap.get(CV_CAP_PROP_FRAME_WIDTH);
    siz.height = (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    Mat frame;

    time_t rawtime;
    struct tm *timeinfo;
    char buffer [80];

    for (;;) {
        if (!cap.read(frame))
            break;
        
        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
  
        rectangle(frame, Point(0, siz.height - 11), Point(siz.width, siz.width), Scalar(32, 32, 32), CV_FILLED, 1, 0);
        putText(frame, buffer, Point(10, siz.height - 3), CV_FONT_HERSHEY_SIMPLEX, 0.3, Scalar(186, 186, 186));
        
        sock.send(frame.data, frame.cols * frame.rows * frame.elemSize());
        usleep(40000);
    }
    return 0;
}

