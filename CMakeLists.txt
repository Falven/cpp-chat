include(cmake/PreventInSourceBuilds.cmake)

cmake_minimum_required(VERSION 3.0)

project(cpp-chat CXX)

set(cpp-chat_VERSION_MAJOR 0)
set(cpp-chat_VERSION_MINOR 1)
set(cpp-chat_VERSION_PATCH 0)
set(cpp-chat_VERSION_STRING ${cpp-chat_VERSION_MAJOR}.${cpp-chat_VERSION_MINOR}.${cpp-chat_VERSION_PATCH})

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Statically specifies what build type (configuration) will be built in this build tree. Possible values are empty, Debug, Release, RelWithDebInfo and MinSizeRel..")

set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++14")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_CXX_FLAGS "-std=c++14")

include(GNUInstallDirs)

add_subdirectory(lib/src)

install(DIRECTORY ${cpp-chat_SOURCE_DIR}/chat DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
set(INCLUDE_INSTALL_DIR include/ CACHE INTERNAL "Include file installation directory.")
set(LIB_INSTALL_DIR lib/ CACHE INTERNAL "Lib file installation directory.")
set(SYSCONFIG_INSTALL_DIR etc/ CACHE INTERNAL "Config file installation directory.")
configure_package_config_file(cppchatConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/cppchatConfig.cmake INSTALL_DESTINATION cmake PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/cppchatConfigVersion.cmake VERSION ${cpp-chat_VERSION_STRING} COMPATIBILITY SameMajorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cppchatConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/cppchatConfigVersion.cmake DESTINATION cmake)

add_executable(chat Chat.cpp)
