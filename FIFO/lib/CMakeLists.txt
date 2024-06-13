# lib/CMakeLists.txt
# Create a library from the queue implementation files
add_library(fifoQueue
    queue.cpp
)

# Specify the include directories for this library
target_include_directories(fifoQueue
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
