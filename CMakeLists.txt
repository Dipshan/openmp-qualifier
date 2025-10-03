cmake_minimum_required(VERSION 4.0)
project(openmp_qualifier)

set(CMAKE_CXX_STANDARD 14)

# Try to find OpenMP
find_package(OpenMP)

# Common source files
set(COMMON_SOURCES common/common.cpp)

# Bubble Sort Executables
add_executable(bss bubbleSort/bss.cpp ${COMMON_SOURCES})
add_executable(bbp bubbleSort/bsp.cpp ${COMMON_SOURCES}
        main.cpp)
if(OpenMP_CXX_FOUND)
    target_link_libraries(bbp OpenMP::OpenMP_CXX)
    target_compile_definitions(bbp PRIVATE _OPENMP)
endif()

# Quick Sort Executables
add_executable(qss quickSort/qss.cpp ${COMMON_SOURCES})
add_executable(qsp quickSort/qsp.cpp ${COMMON_SOURCES})
if(OpenMP_CXX_FOUND)
    target_link_libraries(qsp OpenMP::OpenMP_CXX)
    target_compile_definitions(qsp PRIVATE _OPENMP)
endif()

# Merge Sort Executables
add_executable(mss mergeSort/mss.cpp ${COMMON_SOURCES})
add_executable(msp mergeSort/msp.cpp ${COMMON_SOURCES})
if(OpenMP_CXX_FOUND)
    target_link_libraries(msp OpenMP::OpenMP_CXX)
    target_compile_definitions(msp PRIVATE _OPENMP)
endif()

# Reference STL Sort
add_executable(reference reference.cpp ${COMMON_SOURCES})

# Include directories
target_include_directories(bss PRIVATE common)
target_include_directories(bbp PRIVATE common)
target_include_directories(qss PRIVATE common)
target_include_directories(qsp PRIVATE common)
target_include_directories(mss PRIVATE common)
target_include_directories(msp PRIVATE common)
target_include_directories(reference PRIVATE common)

# Print OpenMP status
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP found and enabled")
else()
    message(WARNING "OpenMP not found - parallel versions will run in serial mode")
endif()