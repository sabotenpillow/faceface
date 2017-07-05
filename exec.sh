#!/bin/bash

if [ $# -eq 0 ]; then
  echo 'specify file written by C++'
  exit 1
fi

if [ ! -e $1 ]; then
  echo 'specified file don'\''t exit'
  exit 2
fi

g++ $1 -I/usr/local/include/opencv2 -I/usr/local/include/opencv -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
