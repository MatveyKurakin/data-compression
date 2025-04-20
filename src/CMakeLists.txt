file(GLOB hdrs "*.h*" "include/*.h*")
file(GLOB srcs "*.cpp")

add_library(data_compression STATIC ${srcs} ${hdrs})
target_link_libraries(data_compression ${LIBRARY_DEPS})