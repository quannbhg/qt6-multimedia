add_library(services STATIC
    src/playbackservice.cpp
    include/services/playbackservice.h
)

target_include_directories(services PUBLIC include)

target_link_libraries(services PUBLIC domain)