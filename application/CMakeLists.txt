cmake_minimum_required(VERSION 3.10)
project(xadc_monitor)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create library
add_library(xadc_lib
    src/xadc_lib.c
)

# Create executable
add_executable(xadc_monitor
    src/main.c
)

# Link library to executable
target_link_libraries(xadc_monitor
    xadc_lib
)

# Installation rules
install(TARGETS xadc_monitor
    RUNTIME DESTINATION bin
)
