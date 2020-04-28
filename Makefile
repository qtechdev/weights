CXX=g++
CXX_FLAGS=-std=c++17 -I./include/
LD_FLAGS=

BUILD_DIR=build/
OUTPUT_DIR=out/

SUBDIRS=$(patsubst src/%,%,$(dir $(wildcard src/*/)))
BUILD_DIRS=${BUILD_DIR} $(addprefix ${BUILD_DIR},${SUBDIRS})


CXX_SOURCES=$(wildcard src/*.cpp)  $(wildcard src/*/*.cpp)
CXX_OBJECTS=$(patsubst src/%,${BUILD_DIR}%,${CXX_SOURCES:.cpp=.o})

NAME=weights
BINARY=${OUTPUT_DIR}${NAME}

all: dirs ${BINARY}

${BINARY}: ${CC_OBJECTS} ${CXX_OBJECTS}
	${CXX} ${LD_FLAGS} -o $@ $^

${BUILD_DIR}%.o: src/%.cpp
	${CXX} ${CXX_FLAGS} -o $@ -c $<

.PHONY: dirs
dirs:
	mkdir -p ${OUTPUT_DIR}
	mkdir -p ${BUILD_DIRS}

.PHONY: clean
clean:
	-rm -r ${BUILD_DIR}
