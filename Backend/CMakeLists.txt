cmake_minimum_required(VERSION 3.16)

project(SMIdeaBackend)

# Find necessary packages
find_package(Threads REQUIRED)
#find_package(dmitigr_libs REQUIRED COMPONENTS pgfe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_path(PostgreSQL_INCLUDE_DIR NAMES libpq-fe.h PATHS /usr/include/postgresql)


# Include directories for the external libraries
add_subdirectory(cpp-httplib)
add_subdirectory(pgfe)

#include smi-lib
add_library(smi-lib 
                "smi-lib/User.cpp"  "smi-lib/Post.cpp"
            )

# Add the executable target
add_executable(main "main.cpp")

# Link necessary libraries
target_link_libraries(main Threads::Threads)  # If using threads

# If using libpq, link the library
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/smi-lib)
target_include_directories(main PRIVATE ${PostgreSQL_INCLUDE_DIR})
target_link_libraries(main 
                        httplib
                        pq
                        smi-lib)

# Additional libraries or flags if needed
# target_link_libraries(myapp other_library)

# Optionally, set C++ standard
#set_property(TARGET main PROPERTY CXX_STANDARD 17)