# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "release")
  file(REMOVE_RECURSE
  "freertos_hello.bin"
  "output.map"
  )
endif()
