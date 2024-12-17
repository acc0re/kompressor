cmake_minimum_required(VERSION 3.10) # Version 3.10 oder höher empfohlen
project(kompressor C)

set(CMAKE_C_STANDARD 99)

# Verwende die Multi-Threaded Debug Runtime für Debug-Builds
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

# Verwende die Multi-Threaded Release Runtime für Release-Builds
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

# Füge das Snappy-Unterverzeichnis hinzu
add_subdirectory(snappy)

# Hauptprogramm erstellen
add_executable(kompressor main.c)

# Verlinke die Snappy-Bibliothek
target_link_libraries(kompressor PRIVATE snappy)
