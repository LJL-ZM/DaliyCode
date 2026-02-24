.PHONY:clean all
all:Server Client
Server:Server.cc
	g++ $^ -o $@ -std=c++11 -lpthread -ljsoncpp
Client:Client.cc
	g++ $^ -o $@ -std=c++11 -lpthread -ljsoncpp
clean:
	rm -rf Server Client