qt_add_executable(MultimediaApp main.cpp)

qt_add_qml_module(MultimediaApp
    URI MultimediaApp
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/pages/PlayerPage.qml
)

target_link_libraries(MultimediaApp
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        viewmodels
        services
        infrastructure
        domain
)