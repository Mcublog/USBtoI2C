#!/bin/sh

sudo socat PTY,link=/dev/ttyS10,raw,echo=0 PTY,link=/dev/ttyS11,raw,echo=0 &
sudo chmod 777 /dev/ttyS11 /dev/ttyS10
