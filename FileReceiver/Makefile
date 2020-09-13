CXX=g++
CXX_FLAGS=-Wall -Wextra -Wpedantic -O3 -Os -std=c++17
LIBS=-L. libsockpp.so -lboost_filesystem
PROJECT=file-receiver

$(PROJECT): src/main.cpp src/file_receiver.cpp include/file_receiver.hpp
	$(CXX) -c $(CXX_FLAGS) src/main.cpp
	$(CXX) -c $(CXX_FLAGS) src/file_receiver.cpp
	$(CXX) main.o file_receiver.o $(LIBS) -o $@
	rm -f *.o

.PHONY: clean
clean:
	rm -f $(PROJECT)
	rm -f *.o
