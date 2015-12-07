PROJECT_NAME        = cas
MAP_SIZE            = 100
LOOP_COUNT          = 200
DEFAULT_T           = 4
DEFAULT_INFECTION   = 0.00001
CXX                 = g++
CXXFLAGS            = -std=c++14 -O3
EXECUTABLE          = ${PROJECT_NAME}-${MAP_SIZE}-${LOOP_COUNT}-${DEFAULT_INFECTION}-${DEFAULT_T}
TEST_EXE            = ${PROJECT_NAME}_test


MAKE.cas  = make -j4 -C src/ CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"       \
			PROJECT_NAME="${EXECUTABLE}.run" PROJECT_DIR=".."          \
			BUILD_DIR="../build/${EXECUTABLE}"                         \
			DEFINES="-DLOOP_COUNT=${LOOP_COUNT} -DMAP_SIZE=${MAP_SIZE} \
					 -DDEFAULT_T=${DEFAULT_T} -DDEFAULT_INFECTION=${DEFAULT_INFECTION}"

MAKE.test = make -j4 -C tests/ CXX="${CXX}" CXXFLAGS="${CXXFLAGS}"     \
			PROJECT_DIR=".."  BUILD_DIR="../build/${EXECUTABLE}"       \
			DEFINES="-DLOOP_COUNT=${LOOP_COUNT} -DMAP_SIZE=${MAP_SIZE} \
					 -DDEFAULT_T=${DEFAULT_T} -DDEFAULT_INFECTION=${DEFAULT_INFECTION}"


all: ${EXECUTABLE} ${TEST_EXE}

build:
	[ -d build ] || mkdir build

${EXECUTABLE}: build
	[ -d build/${EXECUTABLE} ] || mkdir build/${EXECUTABLE}
	${MAKE.cas}

${TEST_EXE}: build
	[ -d build/test ] || mkdir build/test
	${MAKE.test}

.PHONY: test clean run zip tar

zip:
	zip -r 04_xcibul10_xslouk02.zip Makefile src/bmp.hh            \
		tests/test_plot.cpp src/cell.hh src/cellular_automata.hh   \
		src/main.cpp src/Makefile src/plot.hh src/state.hh         \
		tests/check_bmp.sh tests/test_state.cpp tests/main.cpp     \
		tests/Makefile tests/support.hh tests/test_automata.cpp    \
		tests/test_bmp.cpp tests/test_cell.cpp doc.pdf

tar:
	tar czvf 04_xcibul10_xslouk02.tar.gz Makefile src/bmp.hh       \
		tests/test_plot.cpp src/cell.hh src/cellular_automata.hh   \
		src/main.cpp src/Makefile src/plot.hh src/state.hh         \
		tests/check_bmp.sh tests/test_state.cpp tests/main.cpp     \
		tests/Makefile tests/support.hh tests/test_automata.cpp    \
		tests/test_bmp.cpp tests/test_cell.cpp doc.pdf
		
test:
	${MAKE.test} run

clean:
	${MAKE.cas} clean
	${MAKE.test} clean
	
run:
	${MAKE.cas} run


