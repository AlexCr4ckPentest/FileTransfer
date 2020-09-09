CXX=g++
CXX_FLAGS=-Wall -Wextra -Wpedantic -O3 -Os -std=c++17
LIBS=-lsockpp -lboost_filesystem
PROJECT=file-receiver

$(PROJECT): src/main.cpp src/file_receiver.cpp include/file_receiver.hpp
	$(CXX) -c $(CXX_FLAGS) src/main.cpp
	$(CXX) -c $(CXX_FLAGS) src/file_receiver.cpp
	$(CXX) $(LIBS) main.o file_receiver.o -o $@
	rm -f *.o

.PHONY: clean
clean:
	rm -f $(PROJECT)
	rm -f *.o