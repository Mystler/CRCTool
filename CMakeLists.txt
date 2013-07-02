cmake_minimum_required(VERSION 2.8.9)
project(CRCTool)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_COMPILER_IS_CLANG TRUE)
endif()
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
    set(WARNING_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS "-std=c++0x ${WARNING_FLAGS} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${WARNING_FLAGS} ${CMAKE_C_FLAGS}")
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools REQUIRED)

set(CRCTool_HEADERS
    CRCTool.h
)
set(CRCTool_SOURCES
    main.cpp
    CRCTool.cpp
)
set(CRCTool_QUI crctool.ui)
set(CRCTool_TS
    lang_de.ts
)

qt5_wrap_ui(CRCTool_UI ${CRCTool_QUI})
qt5_wrap_cpp(CRCTool_MOC ${CRCTool_HEADERS})
qt5_add_translation(CRCTool_LOC ${CRCTool_TS})

add_executable(CRCTool WIN32 MACOSX_BUNDLE
    ${CRCTool_MOC} ${CRCTool_SOURCES}
    ${CRCTool_UI} ${CRCTool_LOC}
)

target_link_libraries(CRCTool ${Qt5Core_QTMAIN_LIBRARIES})
qt5_use_modules(CRCTool Widgets)

source_group("Source Files" FILES ${CRCTool_SOURCES})
source_group("Resource Files" FILES ${CRCTool_QUI})
source_group("Generated Files" FILES ${CRCTool_MOC} ${CRCTool_UI} ${CRCTool_LOC})

install(TARGETS CRCTool DESTINATION .)
install(FILES ${CRCTool_LOC} DESTINATION .)
