cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
set(PROJECT_NAME timer1)
include(ExternalProject)

project("${PROJECT_NAME}" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Insert Dependencies here
execute_process(
  COMMAND git clone https://github.com/chriskohlhoff/networking-ts-impl "${CMAKE_CURRENT_BINARY_DIR}/deps/networking-ts-impl"
  )
set(NETWORK_TS_INCLUDES "${CMAKE_CURRENT_BINARY_DIR}/deps/networking-ts-impl/include")

# Build the app
add_executable("${PROJECT_NAME}"
	# List your files to include in the project
	src/main.cpp
	)

# Include directories for your dependencies so that the #include directive
# works
target_include_directories("${PROJECT_NAME}" BEFORE
	PUBLIC
		include
    ${NETWORK_TS_INCLUDES}
    )

# Link personally-made dependencies
# add_subdirectory

# Link your dependencies
target_link_libraries("${PROJECT_NAME}"
	pthread
	)

# Add Tests
#add_subdirectory(tests)

# INSTALL
install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
