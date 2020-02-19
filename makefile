all: ./src/main.cpp
	g++ ./src/main.cpp -o koikeizer -lX11 -lpthread

clean:
	rm koikeizer
