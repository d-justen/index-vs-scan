file (GLOB_RECURSE SRCS . *.cpp)

add_library(${PROJECT_NAME}
    ${SRCS}
)

add_dependencies(${PROJECT_NAME} ${EXTERNAL_PROJECTS} ${EXTERNAL_TEST_PROJECTS})

add_executable(Main
    Main.cpp
)

target_link_libraries(Main
    # Add libraries here
    ${PROJECT_NAME}
    ${EXTERNAL_LIBRARIES}
)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O3 -ftree-vectorize -ftree-vectorizer-verbose=n -fopt-info-vec-missed")

message(STATUS, "CXXFLAGS: ${CMAKE_CXX_FLAGS}")