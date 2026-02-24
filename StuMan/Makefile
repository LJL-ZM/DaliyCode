.PHONY:clean all
all:Server
Server:Server.cc
	g++ $^ -o $@ -std=c++11 -lpthread -ljsoncpp
clean:
	rm -rf Server