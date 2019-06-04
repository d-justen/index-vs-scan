file (GLOB_RECURSE SRCS . *.cpp)

add_library(${PROJECT_NAME}
    ${SRCS}
)

find_package(PAPI REQUIRED)
include_directories (${PAPI_INCLUDE_DIRS})
link_directories (${PROJECT_BINARY_DIR}/ext/lib /usr/local/lib/)

add_dependencies(${PROJECT_NAME} ${EXTERNAL_PROJECTS} ${EXTERNAL_TEST_PROJECTS})

add_executable(Main
    Main.cpp
)

add_executable(PapiTest
    PAPI_flops.c
)

target_link_libraries(Main
    # Add libraries here
    ${PROJECT_NAME}
    ${EXTERNAL_LIBRARIES}
    ${PAPI_LIBRARIES}
)

set(CMAKE_EXE_LINKER_FLAGS "-lpapi")