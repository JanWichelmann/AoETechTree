cmake_minimum_required(VERSION 3.13)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
  set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
  set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
endif()

project(TechTree)

if (NOT CMAKE_BUILD_TYPE STREQUAL Debug)
  set(IS_RELEASE TRUE)
endif()

if (IS_RELEASE)
  include(CheckIPOSupported)
  check_ipo_supported(RESULT ENABLE_LTO OUTPUT error)
  if (NOT MSVC)
    add_link_options(-s)
  endif()
endif()

if(CMAKE_GENERATOR MATCHES "Ninja")
  add_compile_options(-fdiagnostics-color)
endif()

add_compile_definitions(WINVER=0x0501)
add_compile_definitions(NOMINMAX)
add_compile_definitions(WIN32_LEAN_AND_MEAN)

if(MSVC)
  foreach(flag_var
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
  endforeach(flag_var)
else()
  add_compile_options(-fno-exceptions)
  if (IS_RELEASE)
    add_link_options(-Wl,--exclude-all-symbols)
  endif()
  add_link_options(-static-libstdc++ -static-libgcc)
  add_definitions(-Wall -Wsign-compare)
endif()

add_subdirectory(TechTree)
add_subdirectory(AoETechTree)
