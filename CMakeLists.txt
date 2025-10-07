cmake_minimum_required(VERSION 3.16)
project(lamport_auth_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic moc/uic handling
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt5 (Widgets + Core + Network)
find_package(Qt5 COMPONENTS Widgets Core Network REQUIRED)

# Find Crypto++ (user can override CRYPTOPP_ROOT)
if(NOT DEFINED CRYPTOPP_ROOT)
  set(CRYPTOPP_ROOT /usr) # default path on Linux
endif()
find_path(CRYPTOPP_INCLUDE_DIRS cryptopp/sha.h HINTS ${CRYPTOPP_ROOT}/include /usr/include /usr/local/include)
find_library(CRYPTOPP_LIBRARIES NAMES cryptopp libcryptopp HINTS ${CRYPTOPP_ROOT}/lib /usr/lib /usr/local/lib)

if(NOT CRYPTOPP_INCLUDE_DIRS OR NOT CRYPTOPP_LIBRARIES)
  message(WARNING "Crypto++ not found by CMake. You can still build if you link manually or provide CRYPTOPP_ROOT.")
endif()

# include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
if(CRYPTOPP_INCLUDE_DIRS)
  include_directories(${CRYPTOPP_INCLUDE_DIRS})
endif()

set(SOURCES
    src/main.cpp
    src/gui/MainWindow.cpp
    src/network/NetworkManager.cpp
    src/app/Controller.cpp
    src/crypto/LamportChain.cpp
    src/util/ConfigManager.cpp
)

# UI file
set(UI_FILES
    src/gui/mainwindow.ui
)

# Add executable
add_executable(lamport_app
    ${SOURCES}
    ${UI_FILES}
)

# Link Qt5 libraries
target_link_libraries(lamport_app PRIVATE Qt5::Widgets Qt5::Core Qt5::Network)

# Link Crypto++ if found
if(CRYPTOPP_LIBRARIES)
  target_link_libraries(lamport_app PRIVATE ${CRYPTOPP_LIBRARIES})
endif()

# Optional install rule
install(TARGETS lamport_app DESTINATION bin)

# ---- config_test target ----
add_executable(config_test
  tests/config_test.cpp
)
target_include_directories(config_test PRIVATE ${SRC_DIR})
target_link_libraries(config_test PRIVATE Qt5::Core)
set_target_properties(config_test PROPERTIES FOLDER "tests")
