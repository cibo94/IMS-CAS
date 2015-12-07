PROJECT_NAME        = cas
MAP_SIZE            = 100
CXX                 = g++
CXXFLAGS            = -std=c++14 -O3
EXECUTABLE          = ${PROJECT_NAME}${MAP_SIZE}
TEST_EXE            = ${PROJECT_NAME}_test

MAKE.cas  = make -C src/ CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"    \
			TARGET_NAME="cas${MAP_SIZE}" PROJECT_DIR=".."       \
			BUILD_DIR="../build/cas${MAP_SIZE}" DEFINES="-DMAP_SIZE=${MAP_SIZE}"

MAKE.test = make -C tests/ CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"  \
			PROJECT_DIR=".."  BUILD_DIR="../build/cas${MAP_SIZE}"

all: ${EXECUTABLE} ${TEST_EXE}

build:
	[ -d build ] || mkdir build

${EXECUTABLE}: build
	[ -d build/cas${MAP_SIZE} ] || mkdir build/${PROJECT_NAME}${MAP_SIZE}
	${MAKE.cas}

${TEST_EXE}: build
	[ -d build/test ] || mkdir build/test
	${MAKE.test}

.PHONY: test clean run

test:
	${MAKE.test} run

clean:
	${MAKE.cas} clean
	${MAKE.test} clean
	
run:
	${MAKE.cas} run
