# this file contains a list of tools that can be activated and downloaded on-demand each tool is enabled during
# configuration by passing an additional `-DUSE_<TOOL>=<VALUE>` argument to CMake

include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

# enables CCACHE support through the USE_CCACHE flag possible values are: YES, NO or equivalent
if(USE_CCACHE)
    CPMAddPackage("gh:TheLartians/Ccache.cmake@1.2.4")
endif()
