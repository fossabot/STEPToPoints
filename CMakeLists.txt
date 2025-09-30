#
# Program: STEPToPoints
#
# Description:
#
# The program STEPToPoints converts solids contained in STEP files into point clouds by regular sampling.
#
# Copyright(C) 2022 Alexander Leutgeb
#
# This library is free software; you can redistribute it and / or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301  USA
#

cmake_minimum_required (VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (STEPToPoints LANGUAGES CXX VERSION 2025.0.0)

set(CMAKE_PREFIX_PATH "${OPENCASCADE_PREFIX};${CMAKE_PREFIX_PATH}")

find_package(OpenCASCADE REQUIRED)
if(NOT OpenCASCADE_FOUND)
  message(STATUS "OpenCASCADE not found - installing via CMake fetchcontent")
  include(FetchContent)
  FetchContent_Declare(
    OpenCASCADE
    GIT_REPOSITORY https://github.com/Open-Cascade-SAS/OCCT.git
    GIT_TAG V7_9_1)

  FetchContent_MakeAvailable(OpenCASCADE)
else()
    message(STATUS "OpenCASCADE found: ${OpenCASCADE_VERSION}")
endif()

add_executable(STEPToPoints src/STEPToPoints.cpp)

target_link_libraries(STEPToPoints ${OpenCASCADE_FoundationClasses_LIBRARIES} ${OpenCASCADE_ModelingData_LIBRARIES} ${OpenCASCADE_ModelingAlgorithms_LIBRARIES} ${OpenCASCADE_Visualization_LIBRARIES} ${OpenCASCADE_ApplicationFramework_LIBRARIES} ${OpenCASCADE_DataExchange_LIBRARIES} ${OpenCASCADE_Draw_LIBRARIES})

# this is for std::execution::par
if(APPLE)
  target_compile_options(STEPToPoints PUBLIC "-fexperimental-library")
  target_link_options(STEPToPoints PUBLIC "-fexperimental-library")
endif()

