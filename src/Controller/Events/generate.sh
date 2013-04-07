#!/bin/sh
./generateBody.sh $1 > $1.cpp
./generateHeader.sh $1 > $1.h
