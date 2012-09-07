WAT?
====
I just wanted to see if I could make remote camera using Crossroads I/O and OpenCV.
Also I've put server on BeagleBone board and checked performance.
It's all performing well. We can go home.

Me can't do buildz. Halp plz !!11one
------------------------------------

### Requirements

* [OpenCV 2.x](http://opencv.willowgarage.com/wiki/)
* [Crossroads I/O](https://github.com/250bpm/libxs)
* [LibXS C++ bindings](https://github.com/250bpm/cppxs)
* CMake

### Get & Build

First    

    git clone https://github.com/mszubart/remote_cam.git
    mkdir remote_cam/build
    cd remote_cam/build
    
Then

    cmake ..
    make

Or something like this...

### Run it! Run!
Executables can be probably, maybe found in build/server and build/client directories.

### License
@ LICENSE file
