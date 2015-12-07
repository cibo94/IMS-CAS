BUILD_DIR   = .
PROJECT_DIR = .
SOURCES     = main.cpp plot.cpp test_automata.cpp test_bmp.cpp test_cell.cpp \
			  test_state.cpp
OBJECTS     = ${BUILD_DIR}/test_main.o ${BUILD_DIR}/plot.o \
			  ${BUILD_DIR}/test_automata.o ${BUILD_DIR}/test_bmp.o \
			  ${BUILD_DIR}/test_cell.o ${BUILD_DIR}/test_state.o
HEADERS     = support.hh
TARGETS     = ${PROJECT_DIR}/test ${PROJECT_DIR}/test_bmp
DEFINES		=
LIBS		=

# MACROS
LINK.cxx    = ${CXX} ${LDFLAGS} ${DEFINES} -o
BUILD.cxx   = ${CXX} ${CXXFLAGS} -c -o
BMP.check   = ./check_bmp.sh

all: ${TARGETS}

# LINK
${PROJECT_DIR}/test: ${BUILD_DIR}/test_main.o ${BUILD_DIR}/test_plot.o \
					 ${BUILD_DIR}/test_automata.o  ${BUILD_DIR}/test_cell.o \
					 ${BUILD_DIR}/test_state.o
	${LINK.cxx} ${PROJECT_DIR}/test ${BUILD_DIR}/test_main.o \
			${BUILD_DIR}/test_plot.o ${BUILD_DIR}/test_automata.o \
			${BUILD_DIR}/test_cell.o ${BUILD_DIR}/test_state.o ${LIBS}

${PROJECT_DIR}/test_bmp: ${BUILD_DIR}/test_bmp.o
	${LINK.cxx} ${PROJECT_DIR}/test_bmp ${BUILD_DIR}/test_bmp.o

# BUILD
${BUILD_DIR}/test_main.o: main.cpp support.hh
	${BUILD.cxx} ${BUILD_DIR}/test_main.o main.cpp

${BUILD_DIR}/test_plot.o: test_plot.cpp support.hh
	${BUILD.cxx} ${BUILD_DIR}/test_plot.o test_plot.cpp

${BUILD_DIR}/test_automata.o: test_automata.cpp support.hh
	${BUILD.cxx} ${BUILD_DIR}/test_automata.o test_automata.cpp

${BUILD_DIR}/test_bmp.o: test_bmp.cpp support.hh
	${BUILD.cxx} ${BUILD_DIR}/test_bmp.o test_bmp.cpp

${BUILD_DIR}/test_cell.o: test_cell.cpp support.hh
	${BUILD.cxx} ${BUILD_DIR}/test_cell.o test_cell.cpp

${BUILD_DIR}/test_state.o: test_state.cpp support.hh
	${BUILD.cxx} ${BUILD_DIR}/test_state.o test_state.cpp

# SUPP

.PHONY: clean test

run:
	${PROJECT_DIR}/test
	${BMP.check} ${PROJECT_DIR}/test_bmp

clean:
	-rm -rf ${OBJECTS} ${TARGETS}
