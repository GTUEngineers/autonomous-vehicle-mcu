set(TARGET_NAME "MCU_Communication_CLI")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${TARGET_NAME})

SET(SOURCEFILES
	CommandLineInterface.cpp
    ${CMAKE_SOURCE_DIR}/src/mcu_communication/UARTMessageBuilder.cpp
        )

SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR}
	    ${CMAKE_BINARY_DIR}/src/ProtoFiles
	    ${CMAKE_SOURCE_DIR}/src/ZmqCommunication
        ${CMAKE_SOURCE_DIR}/src/mcu_communication
        ${CMAKE_CURRENT_BINARY_DIR}
        )


#include_directories(${INCLUDEDIRS})

add_executable(
        ${TARGET_NAME} 
        ${SOURCEFILES}
)

target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDEDIRS})
#TARGET_LINK_LIBRARIES(${TARGET_NAME} "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY})
#ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY} "pthread")

