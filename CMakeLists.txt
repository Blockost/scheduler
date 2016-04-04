cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ProjetGSI)

# Add directories to find BOOST
#set(BOOST_INCLUDEDIR /usr/include/)
#set(BOOST_LIBRARYDIR /usr/include/)

# Let's find BOOST
find_package(Boost REQUIRED COMPONENTS program_options) #COMPONENTS system program_options regex
include_directories(SYSTEM ${Boost_INCLUDE_DIRS} include)
link_directories(${Boost_INCLUDE_DIRS})

#Let's find OpenMP
find_package(OpenMP REQUIRED)

# Add source files to exec
set(SOURCE_FILES src/main.cpp src/Task.h src/flags.h src/basicScheduler.cpp src/basicScheduler.h include/json/jsoncpp.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#Let's find Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT Doxyfile)
    set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    add_custom_command(
            OUTPUT ${DOXYGEN_OUTPUT}
            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DEPENDS ${DOXYGEN_INPUT}
    )

    add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})
endif(DOXYGEN_FOUND)

# Link libraries to exec
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# -fopenmp: enableOpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -Wall -Wextra -Weffc++ -Wno-long-long ${OpenMP_CXX_FLAGS}")