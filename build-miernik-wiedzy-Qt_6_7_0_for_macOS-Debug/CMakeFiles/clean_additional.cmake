# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/miernik-wiedzy_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/miernik-wiedzy_autogen.dir/ParseCache.txt"
  "miernik-wiedzy_autogen"
  )
endif()
