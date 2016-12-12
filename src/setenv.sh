#!/bin/sh

export ROOT_DIR=`pwd`
echo "ROOT_DIR=$ROOT_DIR"

export RELEASE_DIR=$ROOT_DIR/release
echo "RELEASE_DIR=$RELEASE_DIR"

export BIN_DIR=$RELEASE_DIR/bin
echo "BIN_DIR=$BIN_DIR"

export LIB_DIR=$RELEASE_DIR/lib
echo "LIB_DIR=$LIB_DIR"

export INC_DIR=$RELEASE_DIR/include
echo "INC_DIR=$INC_DIR"

export INS_INC_DIR=/usr/local/include/duye
echo "INS_INC_DIR=$INS_INC_DIR"

export INS_LIB_DIR=/usr/lib`getconf LONG_BIT`
echo "INS_LIB_DIR=$INS_LIB_DIR"

export INS_BIN_DIR=/usr/bin
echo "INS_BIN_DIR=$INS_BIN_DIR"
