add_library(services STATIC
    src/placeholder.cpp
)

target_include_directories(services PUBLIC include)

target_link_libraries(services PUBLIC domain)