
set(TARGET_NAME "HeartbeatMechanism")
PROJECT(${TARGET_NAME} CXX C ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/)

SET(SOURCEFILES
        comBase.cpp
	publisher.cpp
	subscriber.cpp
	heartbeatsMechanism_car.cpp
	heartbeatsMechanism_station.cpp
        )
SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR}
        )
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} "zmq" "pthread")
add_subdirectory(Test)
