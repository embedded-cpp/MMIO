# Getting started

mmio is a header-only C++ library. You can integrate it into a project in several common ways.

## Option 1: add it as a submodule

If you already use Git submodules, this is a straightforward approach:

```bash
git submodule add https://github.com/embedded-cpp/mmio.git extern/mmio
```

Then add it to your build:

```cmake
add_subdirectory(extern/mmio)
target_link_libraries(your_target PRIVATE mmio)
```

## Option 2: copy the headers into your project

If you prefer a simple, dependency-light setup, you can copy the contents of the `include/` directory into your project and include the headers directly.

## Option 3: use CPM

If your project already uses CMake Package Manager, you can pull mmio from GitHub like this:

```cmake
include(cmake/CPM.cmake)

CPMAddPackage(
  NAME mmio
  GITHUB_REPOSITORY embedded-cpp/mmio
  GIT_TAG main
)

target_link_libraries(your_target PRIVATE mmio)
```

## Option 4: use FetchContent

You can also integrate mmio with `FetchContent`:

```cmake
include(FetchContent)

FetchContent_Declare(
  mmio
  GIT_REPOSITORY https://github.com/embedded-cpp/mmio.git
  GIT_TAG main
)

FetchContent_MakeAvailable(mmio)
target_link_libraries(your_target PRIVATE mmio)
```

## Include the public header

Once the library is available to your build, include the main header:

```cpp
#include "mmio/mmio.hpp"
```

## Next step: define registers and fields

After that, you can define register types and fields for your target hardware. The library is designed to work well alongside generated register descriptions and handwritten driver code.

## Future integration with svd2cpp

A workflow based on `svd2cpp` is planned for the future. The goal is to make it easier to generate register and field definitions directly from SVD files.
