build:
	g++ -std=c++11 -o factor src/source.cpp src/ntl_utils.cpp -lntl -lgmp -lpthread

run:
	make build
	./factor

prod-build:
	g++ -std=c++11 -O3 -o prod-factor src/source.cpp src/ntl_utils.cpp -lntl -lgmp -lpthread

prod-run:
	make prod-build
	./prod-factor

