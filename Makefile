# compiler flags
CPPFLAGS = -Wall -g3 -O0

# for C++11 (LLVM/clang-500.2.76) on Mac OS X
CPP = g++ -std=c++11 -stdlib=libc++

# for C++11 (g++ 4.6.3) on Ubuntu 12.04 (64-bit)
# CPP = /usr/bin/g++ -std=c++0x

# gtest configured, built and tested as follows on OSX:
#
# 	./configure CXX=g++ CXXFLAGS="-std=c++11 -stdlib=libc++"
# 	make
# 	make check
#
INCLUDE_GTEST = -I gtest-1.7.0/include
GTEST_LPATH = gtest-1.7.0/lib/.libs
GTEST_LIBS = ${GTEST_LPATH}/libgtest_main.a ${GTEST_LPATH}/libgtest.a
PTHREAD_LIBS = -lpthread

EXECUTABLES = gtest_demo

all: ${EXECUTABLES}

# misc
clean:
	rm -fv *.o *.a *.so *.dylib ${EXECUTABLES}

demoTest.o: demoTest.cpp
	${CPP} ${CPPFLAGS} ${INCLUDE_GTEST} -c demoTest.cpp

DemoFixture.o: DemoFixture.cpp
	${CPP} ${CPPFLAGS} ${INCLUDE_GTEST} -c DemoFixture.cpp

# googletest does not play nicely with libraries.
# Listing each object file is the most reliable
# way to construct a suite.
TESTOBJECTS = demoTest.o DemoFixture.o

gtest_demo: ${TESTOBJECTS}
	${CPP} -o gtest_demo ${TESTOBJECTS} ${GTEST_LIBS} ${PTHREAD_LIBS}

