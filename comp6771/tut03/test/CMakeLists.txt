cxx_library(
   TARGET test_main
   FILENAME test_main.cpp
)
target_include_directories(test_main PUBLIC .)

cxx_test(
   TARGET lambda_string
   FILENAME "lambda_string.cpp"
)

cxx_test(
   TARGET car_test
   FILENAME "car_test.cpp"
   LINK car
)

cxx_test(
   TARGET dict_test
   FILENAME "dict_test.cpp"
   LINK dict
)
