# Пирамидальная сортировка

## Цель
Реализация, тестирование и сравнение алгоритмов сортировки 

## Описание

Реализовать следующие алгоритмы:
1. `HeapSort`
2. `SelectionSort`

Произвести тестирование алгоритмов на массивах с различным характером данных:

* `random` — массив из случайных чисел
* `digits` — массив из случайных цифр
* `sorted` — на 99% отсортированный массив
* `revers` — обратно-отсортированный массив

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/heap_sort_test
    --- heap [random] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 5 us
    [ + ] test_2:      100 80 us
    [ + ] test_3:     1000 542 us
    [ + ] test_4:    10000 7419 us
    [ + ] test_5:   100000 63741 us

    --- heap [digits] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 2 us
    [ + ] test_2:      100 23 us
    [ + ] test_3:     1000 331 us
    [ + ] test_4:    10000 4354 us
    [ + ] test_5:   100000 55747 us

    --- heap [sorted] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 28 us
    [ + ] test_3:     1000 371 us
    [ + ] test_4:    10000 5086 us
    [ + ] test_5:   100000 62327 us

    --- heap [revers] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 25 us
    [ + ] test_3:     1000 333 us
    [ + ] test_4:    10000 4522 us
    [ + ] test_5:   100000 57825 us

    --- selection [random] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 37 us
    [ + ] test_3:     1000 2296 us
    [ + ] test_4:    10000 229656 us
    [ + ] test_5:   100000 22676537 us

    --- selection [digits] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 32 us
    [ + ] test_3:     1000 2281 us
    [ + ] test_4:    10000 227749 us
    [ + ] test_5:   100000 22526637 us

    --- selection [sorted] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 29 us
    [ + ] test_3:     1000 2626 us
    [ + ] test_4:    10000 223326 us
    [ + ] test_5:   100000 22227142 us

    --- selection [revers] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 26 us
    [ + ] test_3:     1000 2250 us
    [ + ] test_4:    10000 223347 us
    [ + ] test_5:   100000 22081131 us
  ```

  </details>
