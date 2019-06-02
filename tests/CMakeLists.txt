# 
#        Copyright (C) 2019 Clovis Durand <cd.clovel19²gmail.com>
# 
# -----------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Target configuration for tests
#------------------------------------------------------------------------------

# Header files --------------------------------------------
file(GLOB PUBLIC_HEADERS ${CMAKE_SOURCE_DIR}/inc/*.h ${CMAKE_SOURCE_DIR}/inc/*.hpp)
file(GLOB PRIVATE_HEADERS ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/src/*.hpp)

set(HEADERS 
    ${PUBLIC_HEADERS}
    ${PRIVATE_HEADERS}
)

include_directories(
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/src
)

# Source files --------------------------------------------
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.c ${CMAKE_SOURCE_DIR}/tests/*.cpp)

list(REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Target definition ---------------------------------------
add_definitions(-DTESTS)

# add_test(testname Exename arg1 arg2 ...)
#add_test(test_default tests_${PROJECT_NAME} -1)
add_test(test_base64_encode_decode tests_${PROJECT_NAME} 0)
add_test(test_base64_decode_encode tests_${PROJECT_NAME} 1)
add_test(test_base64_decode tests_${PROJECT_NAME} 2)
add_test(test_base64_encode tests_${PROJECT_NAME} 3)
add_test(test_literal_to_string tests_${PROJECT_NAME} 4)
add_test(test_string_to_literal tests_${PROJECT_NAME} 5)
# add_test(XXXXX tests_${PROJECT_NAME} 0)

add_executable(tests_${PROJECT_NAME}
    ${TEST_SOURCES}
    ${SOURCES}
)
target_link_libraries(tests_${PROJECT_NAME}
    ${OpenCV_LIBS}
)
