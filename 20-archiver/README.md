# Реализация программы сжатия файлов на основе алгоритма RLE

## Цель
Освоить реализацию алгоритма сжатия RLE.

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/archiver_test 
    [==========] Running 13 tests from 2 test suites.
    [----------] Global test environment set-up.
    [----------] 8 tests from algorithm_rle
    [ RUN      ] algorithm_rle.empty
    [       OK ] algorithm_rle.empty (0 ms)
    [ RUN      ] algorithm_rle.single_byte
    [       OK ] algorithm_rle.single_byte (0 ms)
    [ RUN      ] algorithm_rle.length_less_255
    [       OK ] algorithm_rle.length_less_255 (0 ms)
    [ RUN      ] algorithm_rle.length_equal_255
    [       OK ] algorithm_rle.length_equal_255 (0 ms)
    [ RUN      ] algorithm_rle.length_longer_255
    [       OK ] algorithm_rle.length_longer_255 (0 ms)
    [ RUN      ] algorithm_rle.mixed
    [       OK ] algorithm_rle.mixed (0 ms)
    [ RUN      ] algorithm_rle.invalid_odd_length
    [       OK ] algorithm_rle.invalid_odd_length (0 ms)
    [ RUN      ] algorithm_rle.invalid_zero_count
    [       OK ] algorithm_rle.invalid_zero_count (0 ms)
    [----------] 8 tests from algorithm_rle (0 ms total)

    [----------] 5 tests from archiver
    [ RUN      ] archiver.small_file
    Compressed 41 -> 10 bytes (ratio: 24.3902%)
    Decompressed 10 -> 41 bytes
    [       OK ] archiver.small_file (0 ms)
    [ RUN      ] archiver.empty_file
    Compressed 0 -> 0 bytes (ratio: -nan%)
    Decompressed 0 -> 0 bytes
    [       OK ] archiver.empty_file (0 ms)
    [ RUN      ] archiver.big_file
    Compressed 1000 -> 8 bytes (ratio: 0.8%)
    Decompressed 8 -> 1000 bytes
    [       OK ] archiver.big_file (0 ms)
    [ RUN      ] archiver.missing_file
    Archiver: cannot open input file nonexistent.txt
    Archiver: cannot open input file nonexistent.arch
    [       OK ] archiver.missing_file (0 ms)
    [ RUN      ] archiver.mock_algorithm
    Compressed 13 -> 14 bytes (ratio: 107.692%)
    Decompressed 14 -> 13 bytes
    [       OK ] archiver.mock_algorithm (0 ms)
    [----------] 5 tests from archiver (0 ms total)

    [----------] Global test environment tear-down
    [==========] 13 tests from 2 test suites ran. (1 ms total)
    [  PASSED  ] 13 tests.
  ```

  </details>
