cxx_library(
   TARGET test_main
   FILENAME test_main.cpp
)
target_include_directories(test_main PUBLIC .)

cxx_executable(
   TARGET is_a_pointer
   FILENAME "is_a_pointer_test.cpp"
)