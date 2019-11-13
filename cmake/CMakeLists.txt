cmake_minimum_required(VERSION 3.10.2)

# project name
PROJECT(CPy)

# head file path
INCLUDE_DIRECTORIES(
include
include/python3.6m  # Copy the directory of headers into ./include
include/numpy
)

# source directory
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

# set environment variable
SET(TEST_MATH
${DIR_SRCS}
)

# set extern libraries
SET(LIBRARIES
pymodule.so  # Your shared object file
python3.6m
)

LINK_DIRECTORIES(
.  # directory of lib*.so files. Note that name of your .so files must be rename as lib*.so
)

# add executable file
ADD_EXECUTABLE(
${PROJECT_NAME} 
${TEST_MATH}
)

# add link library
TARGET_LINK_LIBRARIES(
${PROJECT_NAME}
${LIBRARIES}
)

# reference: https://blog.csdn.net/hebbely/article/details/79169965
# .
#├── build
#├── CMakeLists.txt
#├── include
#│   └── b.h
#└── src
#    ├── b.c
#    └── main.c
