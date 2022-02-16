all: lesson10

lesson10: LTexture.o
	g++ lesson10.cpp LTexture.o -w -lSDL2 -lSDL2_image -o lesson10

LTexture.o: LTexture.cpp LTexture.hpp
	g++ -c LTexture.cpp -o LTexture.o

clean: 
	rm lesson10
