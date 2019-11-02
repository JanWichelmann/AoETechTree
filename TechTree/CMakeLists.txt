include_directories(include)

set(SOURCE_FILES
  AnotherControlRelatedClass.cpp
  BaseUnitData.cpp
  ButtonControl.cpp
  CivData.cpp
  ComboBoxControl.cpp
  Control.cpp
  ControlListElement.cpp
  DirectDrawBufferData.cpp
  DirectDrawBufferDataListElement.cpp
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
  SlpFile.cpp
  SlpFileElement.cpp
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
  Unknown1064ByteDirectDrawRelatedClass.cpp
  UnknownPaletteRelatedClass.cpp
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
