add_executable(algebraic_test 
  algebraic_test.cpp
  fibo_test.cpp
  gcd_test.cpp
  power_test.cpp
  primes_test.cpp
)

target_link_libraries(algebraic_test
  PRIVATE
  fibo
  gcd
  power
  primes
)

