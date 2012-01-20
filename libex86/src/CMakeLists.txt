file(GLOB_RECURSE SOURCES *.c)
add_definitions(-DREGISTER_SIZE=64)
add_library(ex86 SHARED ${SOURCES})
