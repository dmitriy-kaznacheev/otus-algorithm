# Быстрая и внешняя сортировки

## Цель
Реализация, тестирование и сравнение алгоритмов сортировки 

## Описание

Реализовать следующие алгоритмы:
1. `QuickSort`
2. `MergeSort`
3. `ExternalSort`

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
    $ ./tests/quick_sort_test
    --- quick [random] ---
    [ + ] test_0:        1 41 us
    [ + ] test_1:       10 5 us
    [ + ] test_2:      100 58 us
    [ + ] test_3:     1000 757 us
    [ + ] test_4:    10000 3147 us
    [ + ] test_5:   100000 36581 us
    [ + ] test_6:  1000000 418976 us
    [ + ] test_7: 10000000 4702130 us

    --- quick [digits] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 7 us
    [ + ] test_3:     1000 56 us
    [ + ] test_4:    10000 578 us
    [ + ] test_5:   100000 4623 us
    [ + ] test_6:  1000000 49384 us
    [ + ] test_7: 10000000 480160 us

    --- quick [sorted] ---
    [ + ] test_0:        1 1 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 16 us
    [ + ] test_3:     1000 185 us
    [ + ] test_4:    10000 2252 us
    [ + ] test_5:   100000 24167 us
    [ + ] test_6:  1000000 284966 us
    [ + ] test_7: 10000000 3178624 us

    --- quick [revers] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 15 us
    [ + ] test_3:     1000 181 us
    [ + ] test_4:    10000 2098 us
    [ + ] test_5:   100000 24663 us
    [ + ] test_6:  1000000 274466 us
    [ + ] test_7: 10000000 3372441 us

    --- merge [random] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 3 us
    [ + ] test_2:      100 29 us
    [ + ] test_3:     1000 329 us
    [ + ] test_4:    10000 3832 us
    [ + ] test_5:   100000 44992 us
    [ + ] test_6:  1000000 475532 us
    [ + ] test_7: 10000000 5391640 us

    --- merge [digits] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 4 us
    [ + ] test_2:      100 27 us
    [ + ] test_3:     1000 314 us
    [ + ] test_4:    10000 3442 us
    [ + ] test_5:   100000 38414 us
    [ + ] test_6:  1000000 412782 us
    [ + ] test_7: 10000000 4737508 us

    --- merge [sorted] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 3 us
    [ + ] test_2:      100 22 us
    [ + ] test_3:     1000 263 us
    [ + ] test_4:    10000 2891 us
    [ + ] test_5:   100000 33572 us
    [ + ] test_6:  1000000 370433 us
    [ + ] test_7: 10000000 4280789 us

    --- merge [revers] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 5 us
    [ + ] test_2:      100 20 us
    [ + ] test_3:     1000 227 us
    [ + ] test_4:    10000 2468 us
    [ + ] test_5:   100000 27143 us
    [ + ] test_6:  1000000 297744 us
    [ + ] test_7: 10000000 3226416 us
  ```

  </details>
