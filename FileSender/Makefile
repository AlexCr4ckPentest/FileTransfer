CXX=g++
CXX_FLAGS=-Wall -Wextra -Wpedantic -O3 -Os -std=c++17
LIBS=-lsockpp -lboost_filesystem
PROJECT=file-sender

$(PROJECT): src/main.cpp src/file_sender.cpp include/file_sender.hpp
	$(CXX) -c $(CXX_FLAGS) src/main.cpp
	$(CXX) -c $(CXX_FLAGS) src/file_sender.cpp
	$(CXX) main.o file_sender.o $(LIBS) -o $@
	rm -f *.o

.PHONY: clean
clean:
	rm -f $(PROJECT)
	rm -f *.o
