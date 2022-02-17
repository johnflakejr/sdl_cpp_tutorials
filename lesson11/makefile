all: lesson11

lesson11: LTexture.o
	g++ lesson11.cpp LTexture.o -w -lSDL2 -lSDL2_image -o lesson11

LTexture.o: LTexture.cpp LTexture.hpp
	g++ -c LTexture.cpp -o LTexture.o

clean: 
	rm lesson11
