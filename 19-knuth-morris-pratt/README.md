# Реализация алгоритма поиска подстроки методом Кнута-Морриса-Пратта

## Цель
Освоить реализацию алгоритма Кнута-Морриса-Пратта.

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/kmp_test 
    [==========] Running 9 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 9 tests from kmp
    [ RUN      ] kmp.basic_search
    [       OK ] kmp.basic_search (0 ms)
    [ RUN      ] kmp.not_found
    [       OK ] kmp.not_found (0 ms)
    [ RUN      ] kmp.empty_needle
    [       OK ] kmp.empty_needle (0 ms)
    [ RUN      ] kmp.empty_haystack
    [       OK ] kmp.empty_haystack (0 ms)
    [ RUN      ] kmp.needle_longer
    [       OK ] kmp.needle_longer (0 ms)
    [ RUN      ] kmp.full_text_exact_match
    [       OK ] kmp.full_text_exact_match (0 ms)
    [ RUN      ] kmp.overlapping_search
    [       OK ] kmp.overlapping_search (0 ms)
    [ RUN      ] kmp.single_symbol_needle
    [       OK ] kmp.single_symbol_needle (0 ms)
    [ RUN      ] kmp.vector_support
    [       OK ] kmp.vector_support (0 ms)
    [----------] 9 tests from kmp (0 ms total)

    [----------] Global test environment tear-down
    [==========] 9 tests from 1 test suite ran. (0 ms total)
    [  PASSED  ] 9 tests.
  
  ```

  </details>
