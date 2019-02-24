include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/test/)

add_executable(
        messagebuilder_test
        ${CMAKE_CURRENT_SOURCE_DIR}/../messagebuilder.cpp
        messagebuilder_test.cpp
)

target_include_directories(messagebuilder_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)
