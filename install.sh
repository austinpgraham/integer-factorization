#!/bin/sh
sudo apt-get update
sudo apt-get install make g++
sudo apt-get install libgmp3-dev
tar xf ntl-10.5.0.tar.gz
cd ntl-10.5.0/src
sudo ./configure
make
sudo make install