cmake_minimum_required(VERSION 3.29)
project(CarbonFootprintApp)

set(CMAKE_CXX_STANDARD 20)

# Find Qt on macOS and Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring for macOS")

    # You can ask your team members to set the Qt path as an environment variable on macOS
    set(QT_DIR $ENV{QT_MACOS_PATH})  # Assuming users set this env variable
    if(NOT QT_DIR)
        message(FATAL_ERROR "Please set QT_MACOS_PATH environment variable to your Qt installation directory")
        # Path is: QT_MACOS_PATH=/Users/youruser/Qt/6.x.x
    endif()

    set(CMAKE_PREFIX_PATH "${QT_DIR}/lib/cmake/Qt6")

elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring for Windows")

    # You can set the Qt path as an environment variable on Windows
    set(QT_DIR $ENV{QT_WINDOWS_PATH})  # Assuming users set this env variable
    if(NOT QT_DIR)
        message(FATAL_ERROR "Please set QT_WINDOWS_PATH environment variable to your Qt installation directory")
        # Windows:
        #   Open the System Properties -> Environment Variables.
        #   Add a new environment variable QT_WINDOWS_PATH with the path to your Qt installation, e.g., C:\Qt\6.x.x.
    endif()

    set(CMAKE_PREFIX_PATH "${QT_DIR}/lib/cmake/Qt6")

endif()

# Find Qt modules
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# Source files from the source directory, not build directory
add_executable(CarbonFootprintApp
        main.cpp
        classes/MainPage.cpp
        classes/MainPage.h
        classes/MainController.cpp
        classes/MainController.h
        classes/FootprintMethodPage.cpp
        classes/FootprintMethodPage.h
        classes/HouseholdFootprintPage.cpp
        classes/HouseholdFootprintPage.h
        classes/FlightsPage.cpp
        classes/FlightsPage.h
        classes/FlightEntryWidget.cpp
)

# Link Qt libraries
target_link_libraries(CarbonFootprintApp Qt6::Widgets Qt6::Core Qt6::Gui)

# Enable automatic MOC (Meta-Object Compiler) processing for Q_OBJECT classes
set_target_properties(CarbonFootprintApp PROPERTIES
        AUTOMOC ON
)
