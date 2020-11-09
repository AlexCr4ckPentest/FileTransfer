#!/bin/bash

PROJECT_ROOT_DIR=$(pwd)
SOCKPP_LIB_ROOT_DIR=$PROJECT_ROOT_DIR/sockpp
SOCKPP_LIB_BUILD_DIR=$SOCKPP_LIB_ROOT_DIR/build

FILE_SENDER_SRC_DIR=$PROJECT_ROOT_DIR/FileSender
FILE_RECEIVER_SRC_DIR=$PROJECT_ROOT_DIR/FileReceiver


function download_and_build_sockpp_library() {
    echo -e "\e[1;34m[***]\e[0m Downloading the sockpp library..."
    git clone https://github.com/fpagliughi/sockpp &> /dev/null

    echo -e "\e[1;34m[***]\e[0m Building sockpp library..."
    cd $SOCKPP_LIB_ROOT_DIR && mkdir build && cd build
    cmake .. &> /dev/null && make &> /dev/null 
    echo -e "\e[1;32m[+]\e[0m Building finished!"
}


function cpy_library_to_project_source_dirs() {
    echo -e "\e[1;34m[***]\e[0m Copying library to project source folders..."
    cp $SOCKPP_LIB_BUILD_DIR/*libsockpp* $FILE_SENDER_SRC_DIR/
    cp $SOCKPP_LIB_BUILD_DIR/*libsockpp* $FILE_RECEIVER_SRC_DIR/
}


function build_file_sender() {
    echo -e "\e[1;34m[***]\e[0m Building file-sender..."
    cd $FILE_SENDER_SRC_DIR && make &> /dev/null &
    echo -e "\e[1;32m[+]\e[0m Building finished!"
}


function build_file_receiver() {
    echo -e "\e[1;34m[***]\e[0m Building file-receiver..."
    cd $FILE_RECEIVER_SRC_DIR && make &> /dev/null &
    echo -e "\e[1;32m[+]\e[0m Building finished!"
}


function cleanup() {
    cd $PROJECT_ROOT_DIR && rm -rf $SOCKPP_LIB_ROOT_DIR
}


function main() {
    download_and_build_sockpp_library
    cpy_library_to_project_source_dirs

    build_file_sender
    build_file_receiver

    cleanup
}


# Invoke main()
main
