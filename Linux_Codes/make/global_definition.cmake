SET(PROJE_NAME "HazineAraci")
PROJECT(${PROJE_NAME} C CXX ASM)
SET(DESCRIPTION "Gebze Teknik Universitesi Otonom Hazine Araci")
SET(VERSION "0.1")

# Default C standard: gnu11
SET(C_STANDARD gnu11)

# Default CXX standard: gnu++11
SET(CXX_STANDARD gnu++11)

# Debug Options 
SET(GDB_DEBUG_OPTIONS " -g3")

# C Flags
set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -Wall ${GDB_DEBUG_OPTIONS} -std=${C_STANDARD}" )

# C++ Flags
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -Wall ${GDB_DEBUG_OPTIONS} -std=${CXX_STANDARD}" )

# Cmake options
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/local_build/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/local_build/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/local_build/bin")