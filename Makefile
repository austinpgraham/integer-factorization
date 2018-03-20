build:
	g++ -std=c++11 -o factor source.cpp -lNTL -lgmp

run:
	make build
	./factor

prod-build:
	g++ -std=c++11 -O3 -o prod-factor source.cpp -lNTL -lgmp

prod-run:
	make prod-build
	./prod-factor

