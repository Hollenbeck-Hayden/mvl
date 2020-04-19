# Use latest version of CMake
cmake_minimum_required(VERSION 3.17)

# Define MVL Project
project(mvl VERSION 0.1.0 
	DESCRIPTION "Mathematical Vector Library"
	LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


# Build library
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE_DIR}>
)

target_compile_features(${PROJECT_NAME}
	INTERFACE
		cxx_std_17
)

target_compile_options(${PROJECT_NAME}
	INTERFACE
		-Wall
)

#target_sources(${PROJECT_NAME}
#	mvl/mvl.h
#	mvl/affine.h
#)





# Build options
option(MVL_BUILD_TESTS "Build tests" ON)


# Build tests
if(MVL_BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()



# Export target
install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}-export
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)



# Package management
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
	"${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION
		${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)


# Install target
install(EXPORT ${PROJECT_NAME}-export
	FILE		${PROJECT_NAME}Targets.cmake
	NAMESPACE	${PROJECT_NAME}::
	DESTINATION	${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# Export CMake files
install(FILES
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION
		${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake
)

# Install header files
install(
	DIRECTORY	${PROJECT_SOURCE_DIR}/include/mvl
	DESTINATION	include
)
