include(GNUInstallDirs)
set(TARGET_NAME "CommonLib")
PROJECT(${TARGET_NAME} CXX C ASM)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${TARGET_NAME})
find_package(Protobuf REQUIRED)

SET(SOURCEFILES
	common.cpp
        )
SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR} 
	${CMAKE_BINARY_DIR}/src/ProtoFiles
	${CMAKE_SOURCE_DIR}/src/mcu_communication
        ${CMAKE_SOURCE_DIR}/src/ZmqCommunication
        ${CMAKE_CURRENT_BINARY_DIR}
        )
include_directories(${INCLUDEDIRS})
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY})
