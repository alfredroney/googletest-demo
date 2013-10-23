EXECUTABLES = gtest_demo

all: gtest ${EXECUTABLES}
	./gtest_demo

# call uname to get the OS name (Darwin,Linux)
UNAME = $(shell uname)

ifeq (${UNAME},Darwin)
# for C++11 (LLVM/clang-500.2.76) on Mac OS X
CPP = c++ -std=c++11 -stdlib=libc++
endif
ifeq (${UNAME},Linux)
# for C++11 (g++ 4.6.3) on Ubuntu 12.04 (64-bit)
CPP = g++ -std=c++0x
endif

# compiler flags
CPPFLAGS = -Wall -g3 -O0

# how this example builds agains googletest
GTEST_DIR   = gtest-1.7.0
GTEST_INCL  = -I ${GTEST_DIR}/include
GTEST_LPATH = ${GTEST_DIR}/lib/.libs
GTEST_LIBS  = ${GTEST_LPATH}/libgtest_main.a ${GTEST_LPATH}/libgtest.a

# needed on Linux, optional on Darwin
LPTHREAD = -lpthread

# The architecture of the last build is written to a text file named 'gtest'.
# This file serves as a sentinel to prevent multiple rebuilds.
gtest:
	./build_gtest.sh ${GTEST_DIR}

clean:
	cd ${GTEST_DIR} && make clean && cd - && rm -fv gtest
	rm -fv *.o *.a *.so *.dylib ${EXECUTABLES}

# individual test fixtures ("cases")
demoTest.o: demoTest.cpp
	${CPP} ${CPPFLAGS} ${GTEST_INCL} -c demoTest.cpp

DemoFixture.o: DemoFixture.cpp
	${CPP} ${CPPFLAGS} ${GTEST_INCL} -c DemoFixture.cpp

# googletest does not play nicely with libraries.
# Listing each object file is the least painful
# way to construct a suite.
TESTOBJECTS = demoTest.o DemoFixture.o

gtest_demo: ${TESTOBJECTS}
	${CPP} -o gtest_demo ${TESTOBJECTS} ${GTEST_LIBS} ${LPTHREAD}

