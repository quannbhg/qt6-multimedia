add_library(domain STATIC
    src/placeholder.cpp
    include/domain/mediaitem.h
    include/domain/playbackstate.h
    include/domain/iplaybackengine.h
)

target_include_directories(domain PUBLIC include)

target_link_libraries(domain PUBLIC Qt6::Core)