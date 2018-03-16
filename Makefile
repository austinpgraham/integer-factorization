build:
	g++ -std=c++11 -o factor source.cpp

run:
	make build
	./factor

prod-build:
	g++ -std=c++11 -O3 -o prod-factor source.cpp

prod-run:
	make prod-build
	./prod-factor

