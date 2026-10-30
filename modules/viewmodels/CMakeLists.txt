add_library(viewmodels STATIC
    src/appinfoviewmodel.cpp
    src/playerviewmodel.cpp
    include/viewmodels/appinfoviewmodel.h
    include/viewmodels/playerviewmodel.h
)

target_include_directories(viewmodels PUBLIC include)

target_link_libraries(viewmodels
    PUBLIC
        services
        Qt6::Gui
        Qt6::Qml
)