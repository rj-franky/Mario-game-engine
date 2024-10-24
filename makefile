mario: mario.cpp
	cc mario.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
clean:
	rm *.o *mario
