#!/bin/sh
apt-get install xz-utils
unxz gmp-6.1.2.tar.xz
tar xf gmp-6.1.2.tar
cd gmp-6.1.2/
sudo ./configure && make && make install
gunzip ntl-10.5.0.tar.gz
tar xf ntl-10.5.0.tar
cd ..
cd ./ntl-10.5.0/src 
sudo ./configure && make && make install