include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/test/)

add_executable(
        communication_test
        ${CMAKE_CURRENT_SOURCE_DIR}/../AbstractCommunication.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Client.cpp
        communication_test.cpp
)

target_include_directories(communication_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)
