#!/bin/bash

cd $1

if [[ `uname` == "Darwin" ]]; then
    ./configure CXX=c++ CXXFLAGS="-std=c++11 -stdlib=libc++"
else
    ./configure
fi

make check

cd -

uname > gtest
