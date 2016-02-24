cmake_minimum_required (VERSION 2.6)

project (EiT)

include_directories("${PROJECT_BINARY_DIR}")

set(EXECUTABLE_NAME "EiT")


file( GLOB LIB_SOURCES *.cpp )
file( GLOB LIB_HEADERS *.h )

add_executable( ${EXECUTABLE_NAME} ${LIB_SOURCES} ${LIB_HEADERS} ${DisplayImage_SRCS})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()



cmake_minimum_required(VERSION 2.8)
project( DisplayImage )
find_package( OpenCV REQUIRED )

file(GLOB DisplayImage_SRCS
    "*.h"
    "*.cpp")

ADD_EXECUTABLE (DisplayImage ${DisplayImage_SRCS})

include_directories( ${OpenCV_INCLUDE_DIRS} )
target_link_libraries( ${EXECUTABLE_NAME} ${OpenCV_LIBS} )

