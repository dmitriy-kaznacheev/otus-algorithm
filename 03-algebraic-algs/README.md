# Алгебраические алгоритмы

## Цель
Реализовать популярные алгебраические алгоритмы;
использовать изученный подход при решении других задач.

## Решения

### Наибольший общий делитель

* алгоритм Евклида через вычитание `euclidean_sub`
* алгоритм Евклида через остаток `euclidean_div`
* алгоритм Стейна через битовые операции `binary_stein`

  <br />
  <details>
    <summary>результаты тестов</summary>

    ```
    $ ./tests/algebraic_test 
    [ + ] euclidean_sub_0: 476 ns
    [ + ] euclidean_div_0: 471 ns
    [ + ]  binary_stein_0: 361 ns
    [ + ] euclidean_sub_1: 505 ns
    [ + ] euclidean_div_1: 179 ns
    [ + ]  binary_stein_1: 459 ns
    [ + ] euclidean_sub_2: 73003965 ns
    [ + ] euclidean_div_2: 367 ns
    [ + ]  binary_stein_2: 332 ns
    [ + ] euclidean_sub_3: 146026257 ns
    [ + ] euclidean_div_3: 288 ns
    [ + ]  binary_stein_3: 409 ns
    [ + ] euclidean_sub_4: 2214273 ns
    [ + ] euclidean_div_4: 99 ns
    [ + ]  binary_stein_4: 500 ns
    [ + ] euclidean_sub_5: 1505591 ns
    [ + ] euclidean_div_5: 131 ns
    [ + ]  binary_stein_5: 328 ns
    ```
  </details>

### Возведение числа в целую неотрицательную степень

* обычные итерации
* степень двойки с домножением
* двоичное разложение показателя степени

  <br />
  <details>
    <summary>результаты тестов</summary>

    ```
    $ ./tests/algebraic_test
    [ + ] itr_pow_0: 197 ns
    [ + ] two_pow_0: 92 ns
    [ + ] bin_pow_0: 93 ns
    [ + ] itr_pow_1: 33 ns
    [ + ] two_pow_1: 34 ns
    [ + ] bin_pow_1: 33 ns
    [ + ] itr_pow_2: 2303 ns
    [ + ] two_pow_2: 122 ns
    [ + ] bin_pow_2: 100 ns
    [ + ] itr_pow_3: 23583 ns
    [ + ] two_pow_3: 108 ns
    [ + ] bin_pow_3: 110 ns
    [ + ] itr_pow_4: 228103 ns
    [ + ] two_pow_4: 154 ns
    [ + ] bin_pow_4: 143 ns
    [ + ] itr_pow_5: 2213142 ns
    [ + ] two_pow_5: 132 ns
    [ + ] bin_pow_5: 162 ns
    [ + ] itr_pow_6: 20941757 ns
    [ + ] two_pow_6: 133 ns
    [ + ] bin_pow_6: 146 ns
    [ + ] itr_pow_7: 209163291 ns
    [ + ] two_pow_7: 216 ns
    [ + ] bin_pow_7: 191 ns
    [ + ] itr_pow_8: 2093599930 ns
    [ + ] two_pow_8: 213 ns
    [ + ] bin_pow_8: 174 ns
    [ + ] itr_pow_9: oo ns
    [ + ] two_pow_9: 218 ns
    [ + ] bin_pow_9: 164 ns
    ```
  </details>

### Числа Фибоначчи

* рекурсия
* итерации
* формула золотого сечения
* возведение матрицы в степень

  <br />
  <details>
    <summary>результаты тестов</summary>

    ```
    $ ./tests/algebraic_test
    [ + ]       recursion_0: 737 ns
    [ + ]       iterative_0: 151 ns
    [ + ]    golden_ratio_0: 19830 ns
    [ + ] matrix_multiply_0: 409 ns
    [ + ]       recursion_1: 140 ns
    [ + ]       iterative_1: 83 ns
    [ + ]    golden_ratio_1: 6149 ns
    [ + ] matrix_multiply_1: 557 ns
    [ + ]       recursion_2: 126 ns
    [ + ]       iterative_2: 127 ns
    [ + ]    golden_ratio_2: 697 ns
    [ + ] matrix_multiply_2: 1009 ns
    [ + ]       recursion_3: 144 ns
    [ + ]       iterative_3: 251 ns
    [ + ]    golden_ratio_3: 393 ns
    [ + ] matrix_multiply_3: 1186 ns
    [ + ]       recursion_4: 159 ns
    [ + ]       iterative_4: 210 ns
    [ + ]    golden_ratio_4: 612 ns
    [ + ] matrix_multiply_4: 1475 ns
    [ + ]       recursion_5: 231 ns
    [ + ]       iterative_5: 176 ns
    [ + ]    golden_ratio_5: 399 ns
    [ + ] matrix_multiply_5: 1344 ns
    [ + ]       recursion_6: 1380 ns
    [ + ]       iterative_6: 334 ns
    [ + ]    golden_ratio_6: 437 ns
    [ + ] matrix_multiply_6: 2023 ns
    ```
  </details>