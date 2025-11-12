cmake_minimum_required(VERSION 3.5)

set(PROJ_NAME "Lab5")
project(${PROJ_NAME})

add_compile_options(-Wall -Wextra)

# chcemy, by nasz kod był w pełni zgodny ze standardem
add_compile_options(-pedantic)

# zmieniamy niektóre ostrzeżenia na błędy
# missing return in non-void function: “control reaches end of non-void function"
add_compile_options(-Werror=return-type)

# misleading parentheses - read here: https://www.ibm.com/docs/en/ztpf/1.1.0.14?topic=warnings-parentheses
add_compile_options(-Werror=parentheses)

# VLA is a non-standard feature of some c++ compilers - this prevents its usage
add_compile_options(-Werror=vla)

# detect some trivial array-bounds errors in code (only compile-time !!)
add_compile_options(-Werror=array-bounds)

# additional warnings
add_compile_options ( -Wcast-qual )
add_compile_options ( -Wmaybe-uninitialized )
# te dwie opcje muszą być razem i nie zawsze działają (ale jeśli działają, to dużo łatwiej wyłapać w programie pewne błędy)
# jeśli po dopisaniu tych linijek program przestanie się kompilować - usuńcie je
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(${PROJ_NAME} lab5.c)
