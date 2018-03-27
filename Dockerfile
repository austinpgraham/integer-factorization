FROM gcc:4.9
COPY . /prod-factor
WORKDIR /prod-factor
RUN apt-get install xz-utils
RUN unxz gmp-6.1.2.tar.xz
RUN tar xf gmp-6.1.2.tar
RUN cd gmp-6.1.2/ && ./configure && make && make install
RUN gunzip ntl-10.5.0.tar.gz
RUN tar xf ntl-10.5.0.tar
RUN cd ./ntl-10.5.0/src && ./configure
RUN cd ./ntl-10.5.0/src && make && make install
RUN g++ -std=c++11 -O3 -o run-factor src/source.cpp src/ntl_utils.cpp -L/usr/local/lib/ -lntl -lgmp -lpthread
CMD "./run-factor output1.txt output2.txt"
