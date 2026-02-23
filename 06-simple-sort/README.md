# Простые алгоритмы сортировки

## Цель
Реализация, тестирование и сравнение простых алгоритмов сортировки

## Описание

Реализовать следующие алгоритмы:
1. `BubbleSort`
2. `InsertionSort`
3. `ShellSort`

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
    $ ./tests/simple_sort_test
    --- bubble [random] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 3 us
    [ + ] test_2:      100 186 us
    [ + ] test_3:     1000 6517 us
    [ + ] test_4:    10000 461271 us
    [ + ] test_5:   100000 45948465 us

    --- bubble [digits] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 56 us
    [ + ] test_3:     1000 3585 us
    [ + ] test_4:    10000 244459 us
    [ + ] test_5:   100000 24344099 us

    --- bubble [sorted] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 30 us
    [ + ] test_3:     1000 2909 us
    [ + ] test_4:    10000 249356 us
    [ + ] test_5:   100000 25244793 us

    --- bubble [revers] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 87 us
    [ + ] test_3:     1000 8396 us
    [ + ] test_4:    10000 712425 us
    [ + ] test_5:   100000 113770171 us

    --- insertion [random] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 30 us
    [ + ] test_3:     1000 2703 us
    [ + ] test_4:    10000 272549 us
    [ + ] test_5:   100000 25897951 us

    --- insertion [digits] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 30 us
    [ + ] test_3:     1000 2244 us
    [ + ] test_4:    10000 225696 us
    [ + ] test_5:   100000 22728737 us

    --- insertion [sorted] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 2 us
    [ + ] test_3:     1000 90 us
    [ + ] test_4:    10000 7301 us
    [ + ] test_5:   100000 627905 us

    --- insertion [revers] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 0 us
    [ + ] test_2:      100 55 us
    [ + ] test_3:     1000 4933 us
    [ + ] test_4:    10000 480095 us
    [ + ] test_5:   100000 48772189 us

    --- shell [random] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 20 us
    [ + ] test_3:     1000 351 us
    [ + ] test_4:    10000 5473 us
    [ + ] test_5:   100000 86160 us

    --- shell [digits] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 15 us
    [ + ] test_3:     1000 223 us
    [ + ] test_4:    10000 3203 us
    [ + ] test_5:   100000 38324 us

    --- shell [sorted] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 13 us
    [ + ] test_3:     1000 223 us
    [ + ] test_4:    10000 3648 us
    [ + ] test_5:   100000 56607 us

    --- shell [revers] ---
    [ + ] test_0:        1 0 us
    [ + ] test_1:       10 1 us
    [ + ] test_2:      100 15 us
    [ + ] test_3:     1000 249 us
    [ + ] test_4:    10000 3280 us
    [ + ] test_5:   100000 42685 us
  ```

  </details>
