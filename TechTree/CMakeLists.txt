include_directories(include)

set(SOURCE_FILES
  BaseUnitData.cpp
  BitmapInfo.cpp
  ButtonControl.cpp
  CivData.cpp
  ColorTable.cpp
  ComboBoxControl.cpp
  Control.cpp
  ControlListElement.cpp
  DirectDrawArea.cpp
  DirectDrawAreaNode.cpp
  DirectDrawHandler.cpp
  DropDownButtonControl.cpp
  FontData.cpp
  Game.cpp
  GameDataHandler.cpp
  LabelControl.cpp
  LabelLineData.cpp
  ListBoxControl.cpp
  Panel.cpp
  ResearchData.cpp
  ResearchDataItem.cpp
  ScrollBarControl.cpp
  Shape.cpp
  SlpFile.cpp
  SlpFrameHeader.cpp
  StaticControlContainer.cpp
  TechTree.cpp
  TechTreeData.cpp
  TechTreeDesign.cpp
  TechTreeElement.cpp
  TechTreeRenderer.cpp
  TechTreeWindow.cpp
  TextBoxControl.cpp
  TextFormatData.cpp
  VanillaTechTreeRenderer.cpp
  Window.cpp
  functions.cpp
)

add_library(TechTree SHARED ${SOURCE_FILES})
set_target_properties(TechTree PROPERTIES PREFIX "" SUFFIX ".dll")
if(ENABLE_LTO)
  message(STATUS "Building with link time optimization")
  set_property(TARGET TechTree PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()
target_link_libraries(TechTree winmm) # for timeGetTime()
install(TARGETS TechTree
        LIBRARY DESTINATION lib)
