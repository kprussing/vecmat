# Copyright 2019 Keith F. Prussing
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
# 
# 1.  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 2.  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
# 3.  Neither the name of the copyright holder nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.15.4)
project(vecmat VERSION 0.8.0 LANGUAGES CXX)

add_library(vecmat INTERFACE
)
target_include_directories(vecmat
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(vecmat INTERFACE cxx_std_11)

#
# Define a scoped version of the library
#
add_library(vecmat::vecmat ALIAS vecmat)

#
# Installation details
#
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/vecmat)
install(TARGETS vecmat
    EXPORT vecmat-targets
)
set_target_properties(vecmat PROPERTIES EXPORT_NAME vecmat)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT vecmat-targets
    FILE vecmatTargets.cmake
    NAMESPACE vecmat::
    DESTINATION ${INSTALL_CONFIGDIR}
)

#
# Create a version file
#
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/vecmat-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/vecmat-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/vecmat-config.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#
# Install the configuration files
#
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/vecmat-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/vecmat-config-version.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

#
# Provide tests but let a user disable them
#
option(ENABLE_TESTS "Disable the included tests" ON)
if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

