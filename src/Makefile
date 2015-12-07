BUILD_DIR   = .
PROJECT_DIR = .
SOURCES     = main.cpp
OBJECTS     = ${BUILD_DIR}/main.o
HEADERS     = bmp.hh cell.hh cellular_automata.hh plot.hh state.hh
PROJECT_NAME= cas
TARGET      = ${PROJECT_DIR}/${PROJECT_NAME}
DEFINES     =

# MACROS
LINK.cxx    = ${CXX} ${LDFLAGS} -o
BUILD.cxx   = ${CXX} ${CXXFLAGS} ${DEFINES} -c -o

all: ${TARGET}

${PROJECT_DIR}/${PROJECT_NAME}: ${BUILD_DIR}/main.o
	${LINK.cxx} ${PROJECT_DIR}/${PROJECT_NAME} ${BUILD_DIR}/main.o

${BUILD_DIR}/main.o: main.cpp ${HEADERS}
	${BUILD.cxx} ${BUILD_DIR}/main.o main.cpp

.PHONY: clean run

run:
	pushd ${PROJECT_DIR} && ./${PROJECT_NAME} && popd

clean:
	-rm -rf ${OBJECTS} ${TARGET}
