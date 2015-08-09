cmake_minimum_required(VERSION 2.8.4)
project(Sample_Test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DENABLE_DEBUG=0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG=1")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_definitions(-DGLM_FORCE_RADIANS)

if(UNIX)
  if(APPLE)
    set(PLATFORM "Apple")
  else(APPLE)
    set(PLATFORM "Linux")
  endif(APPLE)
else(UNIX)
  if(WIN32)
    set(PLATFORM "Win32")
  else(WIN32)
    set(PLATFORM "Unknown")
  endif(WIN32)
endif(UNIX)

set(LINK_DIRS
     ../../bin/
    ../../lib/GLFW/lib/${PLATFORM}
    ../../lib/GLEW/lib/${PLATFORM}
    ../../lib/soil/lib/${PLATFORM}
    )

set(INCLUDE_LIB_DIRS
    ../../lib/GLFW/include
    ../../lib/GLEW/include
    ../../lib/glm
    ../../lib/soil/include
    )

set(INCLUDE_DIRS
    ../../include
    ../common
    )

FILE(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "../common/*.cpp")
FILE(GLOB_RECURSE HEADER_FILES "src/*.h" "../common/*.h")

if(PLATFORM STREQUAL "Win32")
    set(LINK_FILES
        glfw3dll
        glew32.dll
        SOIL
        opengl32
        )
else(PLATFORM STREQUAL "Win32")
    set(LINK_FILES
        TakeOne
        glfw
        GLEW
        GL
        SOIL
        )
endif(PLATFORM STREQUAL "Win32")


include_directories(${INCLUDE_DIRS})

include_directories(SYSTEM ${INCLUDE_LIB_DIRS})
link_directories(${LINK_DIRS})

add_executable(Sample_Test ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(Sample_Test ${LINK_FILES})

#copy resources from engine to /res/default/
FILE(MAKE_DIRECTORY ../res/default/)
FILE(COPY ../../res/ DESTINATION ../../res/default/)

#postbuild commands; copy dll's
if(PLATFORM STREQUAL "Win32")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

    add_custom_command(TARGET TakeOne POST_BUILD            # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
            ${CMAKE_CURRENT_LIST_DIR}/lib/GLEW/lib/Win32/glew32.dll                 # <--this is in-file
            ${CMAKE_CURRENT_LIST_DIR}/bin/                                            # <--this is out-file path
            )

    add_custom_command(TARGET TakeOne POST_BUILD            # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different   # which executes "cmake - E copy_if_different..."
            ${CMAKE_CURRENT_LIST_DIR}/lib/GLFW/lib/Win32/glfw3.dll                  # <--this is in-file
            ${CMAKE_CURRENT_LIST_DIR}/bin/                                            # <--this is out-file path
            )

endif(PLATFORM STREQUAL "Win32")
