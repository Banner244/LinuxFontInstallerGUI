cmake_minimum_required(VERSION 3.10)
project(SimpleLinuxFontInstaller)

# Setze automatisch den CMAKE_EXPORT_COMPILE_COMMANDS
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setze die Ausgabeverzeichnisse für statische und gemeinsame Bibliotheken sowie ausführbare Dateien
set(FullOutputDir "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

# Suche nach GTKMM 4.0 und libadwaita-1
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
pkg_check_modules(LIBADWAITA REQUIRED libadwaita-1)

# Erstelle die View-Bibliothek
file(GLOB VIEW_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/View/*.cpp")
add_library(view STATIC ${VIEW_SOURCES})  # oder SHARED je nach Bedarf

file(GLOB CONTROLLER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Controller/*.cpp")
add_library(controller STATIC ${CONTROLLER_SOURCES})  # oder SHARED je nach Bedarf

file(GLOB MODELS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/Models/*.cpp")
add_library(models STATIC ${MODELS_SOURCES})  # oder SHARED je nach Bedarf

file(GLOB APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/App/*.cpp")
add_library(app STATIC ${APP_SOURCES})  # oder SHARED je nach Bedarf

# Stelle sicher, dass die GTKMM- und libadwaita-Header in view und controller eingebunden sind
target_include_directories(view PRIVATE ${GTKMM_INCLUDE_DIRS} ${LIBADWAITA_INCLUDE_DIRS})
target_include_directories(controller PRIVATE ${GTKMM_INCLUDE_DIRS} ${LIBADWAITA_INCLUDE_DIRS})
target_include_directories(app PRIVATE ${GTKMM_INCLUDE_DIRS} ${LIBADWAITA_INCLUDE_DIRS})
target_include_directories(models PRIVATE ${GTKMM_INCLUDE_DIRS} ${LIBADWAITA_INCLUDE_DIRS})

# Setze die C++ Version und den Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Erstelle das Haupt-Executable
add_executable(${PROJECT_NAME} src/App/main.cpp)

# Füge GTKMM- und libadwaita-Header zu den Include-Verzeichnissen hinzu
target_include_directories(${PROJECT_NAME} PRIVATE ${GTKMM_INCLUDE_DIRS} ${LIBADWAITA_INCLUDE_DIRS})

# Linke die GTKMM- und libadwaita-Bibliotheken sowie die view- und controller-Bibliothek
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARIES} ${LIBADWAITA_LIBRARIES} app view controller models )


# Falls du zusätzliche Compiler-Optionen benötigst
# target_compile_options(${PROJECT_NAME} PRIVATE ${GTKMM_CFLAGS_OTHER})

