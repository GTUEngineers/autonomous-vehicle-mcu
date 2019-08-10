include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/test/)

add_executable(
        communication_test
        communication_test.cpp
)

target_include_directories(communication_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_SOURCE_DIR}/src/Logger)
TARGET_LINK_LIBRARIES(communication_test "Logger" "Communication")
