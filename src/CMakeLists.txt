# 
#          Copyright (C) 2019 Clovis Durand <cd.clovel19@gmail.com>
# 
# -----------------------------------------------------------------------------

# Header files --------------------------------------------
file(GLOB_RECURSE CXX_PUBLIC_HEADERS ${CMAKE_SOURCE_DIR}/inc/*.hpp)
file(GLOB_RECURSE C_PUBLIC_HEADERS ${CMAKE_SOURCE_DIR}/inc/*.h)
set(PUBLIC_HEADERS
    ${CXX_PUBLIC_HEADERS}
    ${C_PUBLIC_HEADERS}
)

file(GLOB_RECURSE CXX_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE C_SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

# Target definition ---------------------------------------
add_executable(${PROJECT_NAME}
    ${CXX_SOURCES}
    ${C_SOURCES}
)
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
)
