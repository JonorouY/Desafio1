cmake_minimum_required(VERSION 3.5)

project(Crear_y_rotar_matrices LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Crear_y_rotar_matrices main.h)

include(GNUInstallDirs)
install(TARGETS Crear_y_rotar_matrices
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
