# Реализация алгоритма поиска подстроки методом Бойера-Мура

## Цель
Освоить реализацию алгоритма Бойера-Мура.

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/substr_test 
    [==========] Running 9 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 9 tests from boyer_moore
    [ RUN      ] boyer_moore.basic_search
    [       OK ] boyer_moore.basic_search (0 ms)
    [ RUN      ] boyer_moore.not_found
    [       OK ] boyer_moore.not_found (0 ms)
    [ RUN      ] boyer_moore.empty_needle
    [       OK ] boyer_moore.empty_needle (0 ms)
    [ RUN      ] boyer_moore.empty_haystack
    [       OK ] boyer_moore.empty_haystack (0 ms)
    [ RUN      ] boyer_moore.needle_longer
    [       OK ] boyer_moore.needle_longer (0 ms)
    [ RUN      ] boyer_moore.full_text_exact_match
    [       OK ] boyer_moore.full_text_exact_match (0 ms)
    [ RUN      ] boyer_moore.overlapping_search
    [       OK ] boyer_moore.overlapping_search (0 ms)
    [ RUN      ] boyer_moore.single_symbol_needle
    [       OK ] boyer_moore.single_symbol_needle (0 ms)
    [ RUN      ] boyer_moore.wchar_support
    [       OK ] boyer_moore.wchar_support (0 ms)
    [----------] 9 tests from boyer_moore (0 ms total)

    [----------] Global test environment tear-down
    [==========] 9 tests from 1 test suite ran. (0 ms total)
    [  PASSED  ] 9 tests.    
  ```

  </details>
