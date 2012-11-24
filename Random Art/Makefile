LIBS = -ljpeg -lm
OBJS = main.o token.o jpeg.o


randart: $(OBJS)
	g++ -o randart $(OBJS) $(LIBS)

main.o: main.cpp token.h jpeg.h
	g++ -c main.cpp

token.o: token.cpp token.h jpeg.h
	g++ -c token.cpp

jpeg.o: jpeg.cpp jpeg.h
	g++ -c jpeg.cpp

clean: 
	rm *.o
	rm randart

