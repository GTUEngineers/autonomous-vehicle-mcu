include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/test/)

add_executable(
        heartbeatMechanism_test
        ${CMAKE_CURRENT_SOURCE_DIR}/../comBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../heartbeatsMechanisim.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../publisher.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../subscriber.cpp
        main.cpp
)

target_include_directories(heartbeatMechanism_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)

TARGET_LINK_LIBRARIES(heartbeatMechanism_test "zmq" "pthread")
