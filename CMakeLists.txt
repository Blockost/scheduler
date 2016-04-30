cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ProjetGSI)

# Add directories to find BOOST
#set(BOOST_INCLUDEDIR /usr/lib/x86_64-linux-gnu/)
#set(BOOST_LIBRARYDIR /usr/lib/x86_64-linux-gnu/)

# Let's find BOOST
find_package(Boost REQUIRED COMPONENTS system program_options) #COMPONENTS
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} include)
link_directories(${Boost_INCLUDE_DIRS})

#Let's find OpenMP
find_package(OpenMP REQUIRED)

# Add source files to exec
set(SOURCE_FILES src/main.cpp src/flags.h include/termcolor/termcolor.hpp src/main.h src/task.h src/util/util.cpp src/util/util.h
        src/Scheduler/Scheduler.cpp src/Scheduler/Scheduler.h src/Scheduler/SequentialScheduler.cpp src/Scheduler/SequentialScheduler.h
        src/Scheduler/ParallelScheduler.cpp src/Scheduler/ParallelScheduler.h src/Client/Client.cpp src/Client/Client.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries to exec
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} rt)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# -fopenmp: enableOpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -Wall -Wextra -Weffc++ -Wno-long-long ${OpenMP_CXX_FLAGS}")