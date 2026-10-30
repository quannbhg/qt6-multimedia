add_library(infrastructure STATIC
    playback/qtplaybackengine.cpp
    include/infrastructure/qtplaybackengine.h
)

target_include_directories(infrastructure PUBLIC include)

target_link_libraries(infrastructure
    PUBLIC
        domain
        Qt6::Sql
        Qt6::Network
        Qt6::Multimedia
)