file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(tests ${srcs} ${hdrs})
target_link_libraries(tests gtest data_compression)
