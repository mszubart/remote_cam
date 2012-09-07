#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <xs/xs.hpp>

using namespace cv;
using namespace std;

int main(int ac, char** av) {
    const int x_len = 352;
    const int y_len = 288;
    const int el_size = 3;
    const int recv_size = x_len * y_len * el_size;

    // Horizontal part of the crosshair
    const int x_g1_sx = x_len / 3;
    const int x_g1_ex = x_g1_sx + 47;
    const int x_g2_sx = x_g1_ex + 25;
    const int x_g2_ex = x_g2_sx + 47;
    const int y_g12_sx = y_len / 2;
    const int y_g12_ex = y_g12_sx;

    // Vertical part of the crosshair
    const int x_g34_sx = x_len / 2;
    const int x_g34_ex = x_g34_sx;
    const int y_g3_sx = y_len / 3;
    const int y_g3_ex = y_g3_sx + 36;
    const int y_g4_sx = y_g3_ex + 25;
    const int y_g4_ex = y_g4_sx + 36;

    Mat frame;
    Mat gray_frame;
    frame.create(y_len, x_len, 16);

    xs::context_t ctx;
    xs::socket_t sock(ctx, XS_SUB);
    
    sock.setsockopt(XS_SUBSCRIBE, NULL, 0);
    sock.connect("tcp://127.0.0.1:5555");

    for (;;) {
        sock.recv(frame.data, recv_size, 0);

        cvtColor(frame, gray_frame, CV_BGR2GRAY);
        cvtColor(gray_frame, frame, CV_GRAY2BGR);

        rectangle(frame, Point(x_g1_sx, y_g12_sx), Point(x_g1_ex, y_g12_ex), Scalar(28, 28, 230), CV_FILLED, 1, 0); // g1
        rectangle(frame, Point(x_g2_sx, y_g12_sx), Point(x_g2_ex, y_g12_ex), Scalar(28, 28, 230), CV_FILLED, 1, 0); // g2
        rectangle(frame, Point(x_g34_sx, y_g3_sx), Point(x_g34_ex, y_g3_ex), Scalar(28, 28, 230), CV_FILLED, 1, 0); // g3
        rectangle(frame, Point(x_g34_sx, y_g4_sx), Point(x_g34_ex, y_g4_ex), Scalar(28, 28, 230), CV_FILLED, 1, 0); // g4

        imshow("RFB", frame);

      if (waitKey(30) >= 0)
            break;      
    }
    return 0;
}

