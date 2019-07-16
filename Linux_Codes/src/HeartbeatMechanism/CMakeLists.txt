cmake_minimum_required(VERSION 3.10)
set(TARGET_NAME "HeartbeatMechanism")
PROJECT(${TARGET_NAME} CXX C ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/)
include_directories(${CMAKE_BINARY_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})

SET(SOURCEFILES
        comBase.cpp
	publisher.cpp
	subscriber.cpp
        )
SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR}
        )
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
#TARGET_LINK_LIBRARIES(${TARGET_NAME} "")
#add_subdirectory(Test)
