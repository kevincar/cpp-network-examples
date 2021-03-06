cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
set(PROJECT_NAME daytime)
include(ExternalProject)

project("${PROJECT_NAME}" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Insert Dependencies here
# experimental/net
execute_process(
  COMMAND git clone https://github.com/chriskohlhoff/networking-ts-impl "${CMAKE_CURRENT_BINARY_DIR}/deps/networking-ts-impl"
  )
set(NETWORK_TS_INCLUDES "${CMAKE_CURRENT_BINARY_DIR}/deps/networking-ts-impl/include")
macro(get_WIN32_WINNT version)
    if (WIN32 AND CMAKE_SYSTEM_VERSION)
        set(ver ${CMAKE_SYSTEM_VERSION})
        string(REPLACE "." "" ver ${ver})
        string(REGEX REPLACE "([0-9])" "0\\1" ver ${ver})

		set(${version} "0x${ver}")
    endif()
endmacro()
if(WIN32)
	get_WIN32_WINNT(ver)
	add_definitions(-D_WIN32_WINNT=${ver})
endif()

# Build the app
add_executable("${PROJECT_NAME}1" "src/${PROJECT_NAME}1.cpp")
add_executable("${PROJECT_NAME}2" "src/${PROJECT_NAME}2.cpp")
add_executable("${PROJECT_NAME}3" "src/${PROJECT_NAME}3.cpp")
add_executable("${PROJECT_NAME}4" "src/${PROJECT_NAME}4.cpp")
add_executable("${PROJECT_NAME}5" "src/${PROJECT_NAME}5.cpp")
add_executable("${PROJECT_NAME}6" "src/${PROJECT_NAME}6.cpp")
add_executable("${PROJECT_NAME}7" "src/${PROJECT_NAME}7.cpp")

# Include directories for your dependencies so that the #include directive
# works
target_include_directories("${PROJECT_NAME}1" BEFORE PUBLIC include ${NETWORK_TS_INCLUDES})
target_include_directories("${PROJECT_NAME}2" BEFORE PUBLIC include ${NETWORK_TS_INCLUDES})
target_include_directories("${PROJECT_NAME}3" BEFORE PUBLIC include ${NETWORK_TS_INCLUDES})
target_include_directories("${PROJECT_NAME}4" BEFORE PUBLIC include ${NETWORK_TS_INCLUDES})
target_include_directories("${PROJECT_NAME}5" BEFORE PUBLIC include ${NETWORK_TS_INCLUDES})
target_include_directories("${PROJECT_NAME}6" BEFORE PUBLIC include ${NETWORK_TS_INCLUDES})
target_include_directories("${PROJECT_NAME}7" BEFORE PUBLIC include ${NETWORK_TS_INCLUDES})

# Link personally-made dependencies
# add_subdirectory

# Link your dependencies

if(NOT WIN32)
	set(PTHREAD_LIB "pthread")
else()
	set(PTHREAD_LIB "")
endif()
target_link_libraries("${PROJECT_NAME}1" "${PTHREAD_LIB}")
target_link_libraries("${PROJECT_NAME}2" "${PTHREAD_LIB}")
target_link_libraries("${PROJECT_NAME}3" "${PTHREAD_LIB}")
target_link_libraries("${PROJECT_NAME}4" "${PTHREAD_LIB}")
target_link_libraries("${PROJECT_NAME}5" "${PTHREAD_LIB}")
target_link_libraries("${PROJECT_NAME}6" "${PTHREAD_LIB}")
target_link_libraries("${PROJECT_NAME}7" "${PTHREAD_LIB}")

# Add Tests
#add_subdirectory(tests)

# INSTALL
#install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
