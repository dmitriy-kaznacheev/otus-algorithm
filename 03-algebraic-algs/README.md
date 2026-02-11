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

