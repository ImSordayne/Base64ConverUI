cmake_minimum_required(VERSION 3.16)
project(Base64ConverUI VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

if(WIN32)
    set(build_option WIN32)
endif()
add_executable(Base64ConverUI ${build_option}
    src/main.cpp
    src/Base64ConverUI.cpp
    src/Base64Conver.cpp
)

target_link_libraries(Base64ConverUI
    Qt6::Core
    Qt6::Widgets
)

qt_generate_deploy_script(
    TARGET Base64ConverUI
    OUTPUT_SCRIPT deploy_script
    CONTENT "
qt_deploy_runtime_dependencies(
    EXECUTABLE \"$<TARGET_FILE:Base64ConverUI>\"
    GENERATE_QT_CONF
    VERBOSE
)"
)

install(TARGETS Base64ConverUI
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    BUNDLE  DESTINATION .
)
install(SCRIPT ${deploy_script})

set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/Base64ConverUI.exe")
set(DIRS "${CMAKE_BINARY_DIR}")

install(CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
" COMPONENT Runtime)