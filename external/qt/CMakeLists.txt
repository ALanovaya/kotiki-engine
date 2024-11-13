include(FetchContent)

set(QT_BUILD_EXAMPLES OFF) 
set(QT_BUILD_TESTS OFF)

FetchContent_Declare( 
    Qt 
    GIT_REPOSITORY 
    https://github.com/qt/qtbase.git 
    GIT_TAG v6.8.0 
)

set(QT_COMPONENTS Core Widgets Gui )

set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTORCC ON) 
set(CMAKE_AUTOUIC ON)

FetchContent_MakeAvailable(Qt)