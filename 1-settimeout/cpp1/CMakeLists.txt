cmake_minimum_required (VERSION 3.5)
project (set_timeout)

add_executable(set_timeout set_timeout.cc)
set_property(TARGET set_timeout PROPERTY CXX_STANDARD 17)
target_compile_features(set_timeout PRIVATE cxx_auto_type)
