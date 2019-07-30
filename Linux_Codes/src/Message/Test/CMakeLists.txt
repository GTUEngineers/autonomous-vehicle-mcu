include(GNUInstallDirs)
set(TARGET_NAME "messagebuilder_test")
PROJECT(${TARGET_NAME} CXX C ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/test/)

add_executable(
        messagebuilder_test
        messagebuilder_test.cpp
)

target_include_directories(${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)

TARGET_LINK_LIBRARIES(${TARGET_NAME} "Message")
