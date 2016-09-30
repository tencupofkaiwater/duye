#!/bin/sh

export ROOT_DIR=`pwd`
echo "ROOT_DIR=$ROOT_DIR"

export RELEASE_DIR=$ROOT_DIR/release
echo "RELEASE_DIR=$RELEASE_DIR"

export BIN_DIR=$RELEASE_DIR/bin
echo "BIN_DIR=$BIN_DIR"

export CONF_DIR=$RELEASE_DIR/conf
echo "CONF_DIR=$CONF_DIR"

export INS_INC_DIR=/usr/include
echo "INS_INC_DIR=$INS_INC_DIR"

export INS_BIN_DIR=/usr/bin
echo "INS_BIN_DIR=$INS_BIN_DIR"

export INS_CONF_DIR=/etc
echo "INS_CONF_DIR=$INS_CONF_DIR"

