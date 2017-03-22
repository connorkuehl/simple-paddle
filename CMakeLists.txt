cmake_minimum_required (VERSION 3.5.1)
project (SimplePaddle)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (SOURCE
    src/main.cpp
    src/Ball.cpp 
    src/GameObject.cpp 
    src/Paddle.cpp
    )

set (HEADERS
    src/GameObject.h
    src/Ball.h
    src/Paddle.h
    )

add_executable (SimplePaddle ${SOURCE} ${HEADERS})

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package (SFML REQUIRED system window graphics)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(SimplePaddle ${SFML_LIBRARIES})
endif()
