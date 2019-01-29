cmake_minimum_required (VERSION 3.12)
project (example CXX)
add_executable (example example.cpp)
target_compile_features (example PUBLIC cxx_std_17)
target_compile_options (example PUBLIC -O0 -Wall -Wextra -pedantic -Wconversion -Wformat=2 
    -fsanitize=address,undefined
    -fstack-protector-strong
    -Wno-unused
)
target_link_libraries (example PUBLIC
    asan
    ubsan
)
