cmake_minimum_required (VERSION 3.7.2)
project (SimplePaddle)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (SOURCE_FILES main.cpp Ball.cpp GameObject.cpp Paddle.cpp)

add_executable (SimplePaddle ${SOURCE_FILES})

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package (SFML REQUIRED system window graphics)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(SimplePaddle ${SFML_LIBRARIES})
endif()
