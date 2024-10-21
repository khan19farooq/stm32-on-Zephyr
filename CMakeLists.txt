# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0
#
# This CMake file is picked by the Zephyr build system because it is defined
# as the module CMake entry point (see zephyr/module.yml).


# This is needed so that custom driver classes using system calls are taken into
# account

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.13.1)

# Define the project name and version
project(my_app VERSION 0.1.0)

# Include the Zephyr build system
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Add source files for the project
target_sources(app PRIVATE src/main.c)

##################################################################################

#zephyr_syscall_include_directories(include)

#zephyr_include_directories(include)

#add_subdirectory(drivers)
#add_subdirectory(lib)
