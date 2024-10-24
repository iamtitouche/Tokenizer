cmake_minimum_required(VERSION 3.14)
project(Tokenizer)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activer les informations de débogage
set(CMAKE_BUILD_TYPE Debug)

# Inclure le dossier des headers
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Ajouter l'exécutable
add_executable(Tokenizer main.cpp src/file.cpp src/TokenRec.cpp src/tokenizer.cpp src/Token.cpp)
