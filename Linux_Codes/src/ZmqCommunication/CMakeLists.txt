cmake_minimum_required(VERSION 3.10)
set(TARGET_NAME "ZmqCommunication")
PROJECT(${TARGET_NAME} CXX C ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/)
include_directories(${CMAKE_BINARY_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})

SET(SOURCEFILES
        comBase.cpp
	    server.cpp
	    client.cpp

    )
SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR}
        )
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} "zmq")
add_subdirectory(Test)
