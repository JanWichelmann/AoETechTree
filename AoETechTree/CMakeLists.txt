set(SOURCE_FILES
  AoETechTree.cpp
)

add_library(AoETechTree SHARED ${SOURCE_FILES})
set_target_properties(AoETechTree PROPERTIES PREFIX "" SUFFIX ".dll")
if(ENABLE_LTO)
  message(STATUS "Building with link time optimization")
  set_property(TARGET AoETechTree PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
target_link_libraries(AoETechTree winmm) # for timeGetTime()
install(TARGETS AoETechTree
        LIBRARY DESTINATION lib)

