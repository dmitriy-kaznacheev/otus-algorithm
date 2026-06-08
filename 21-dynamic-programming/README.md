# Задачи на динамическое программирование

## Цель
Освоить реализацию задач на динамическое программирование

## 1. Раз горох, два горох (JUNIOR)

Суслик и Хома нашли кладовку с горохом и решили его поделить.  
— Ты чего мой горох берёшь!  
— Как твой?  
— Подо мной, значит, мой!  
— Ах так? Тогда давай делить!  
— Давай!  

Суслик набрал себе `a/b` гороха, а Хома — `c/d` гороха от общего количества.  

Найдите дробь, которая покажет, какую часть от общего количества гороха они себе набрали.  

Ответ записать в виде **несократимой дроби**.  
Значение каждой дроби меньше единицы, сумма дробей не больше единицы.  

**Начальные данные:** одна строка в виде `a/b+c/d`.  
Строка записана именно в таком формате, вместо букв записаны числа, каждое число от 1 до 10000.  

**Вывод результата:** ответ в виде `x/y`, представляющих собой несократимую дробь.  
Максимальное значение дроби — `1/1`.


## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/dt_test 
    [----------] 6 tests from manual_peas_division_test
    [ RUN      ] manual_peas_division_test.simple_fractions
    [       OK ] manual_peas_division_test.simple_fractions (0 ms)
    [ RUN      ] manual_peas_division_test.fraction_reduction
    [       OK ] manual_peas_division_test.fraction_reduction (0 ms)
    [ RUN      ] manual_peas_division_test.large_numbers
    [       OK ] manual_peas_division_test.large_numbers (0 ms)
    [ RUN      ] manual_peas_division_test.sum_one
    [       OK ] manual_peas_division_test.sum_one (0 ms)
    [ RUN      ] manual_peas_division_test.zero
    [       OK ] manual_peas_division_test.zero (0 ms)
    [ RUN      ] manual_peas_division_test.invalid_format
    [       OK ] manual_peas_division_test.invalid_format (0 ms)
    [----------] 6 tests from manual_peas_division_test (0 ms total)
    [----------] 10 tests from DataFiles/PeasDivisionTest
    [ RUN      ] DataFiles/PeasDivisionTest.file/0
    [       OK ] DataFiles/PeasDivisionTest.file/0 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/1
    [       OK ] DataFiles/PeasDivisionTest.file/1 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/2
    [       OK ] DataFiles/PeasDivisionTest.file/2 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/3
    [       OK ] DataFiles/PeasDivisionTest.file/3 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/4
    [       OK ] DataFiles/PeasDivisionTest.file/4 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/5
    [       OK ] DataFiles/PeasDivisionTest.file/5 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/6
    [       OK ] DataFiles/PeasDivisionTest.file/6 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/7
    [       OK ] DataFiles/PeasDivisionTest.file/7 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/8
    [       OK ] DataFiles/PeasDivisionTest.file/8 (0 ms)
    [ RUN      ] DataFiles/PeasDivisionTest.file/9
    [       OK ] DataFiles/PeasDivisionTest.file/9 (0 ms)
    [----------] 10 tests from DataFiles/PeasDivisionTest (0 ms total)
  ```

  </details>

## 2. Ёлочка программиста (JUNIOR)

Новогодняя ёлочка программиста состоит из цифр.

На первой строке записана высота ёлочки — натуральное число от 1 до 100.

Далее на N строчках зарисована сама ёлочка: сначала 1 цифра, потом 2, на последней строке — N цифр через пробел. В начале и в конце каждой строки могут быть пробелы, чтобы ёлочка получилась красивой.

**Гирляндой** называется последовательность цифр, которую можно получить, спускаясь от верхушки ёлки до её подножья, каждый раз смещаясь либо влево-вниз, либо вправо-вниз.

Найти гирлянду с максимальной суммой цифр.

**Вывести** одно число — максимальную сумму найденной гирлянды.

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/dt_test 
    [----------] 5 tests from manual_christmas_tree_test
    [ RUN      ] manual_christmas_tree_test.Example1
    [       OK ] manual_christmas_tree_test.Example1 (0 ms)
    [ RUN      ] manual_christmas_tree_test.large
    [       OK ] manual_christmas_tree_test.large (0 ms)
    [ RUN      ] manual_christmas_tree_test.single
    [       OK ] manual_christmas_tree_test.single (0 ms)
    [ RUN      ] manual_christmas_tree_test.symmetric
    [       OK ] manual_christmas_tree_test.symmetric (0 ms)
    [ RUN      ] manual_christmas_tree_test.empty
    [       OK ] manual_christmas_tree_test.empty (0 ms)
    [----------] 5 tests from manual_christmas_tree_test (0 ms total)
    [----------] 10 tests from DataFiles/ChristmasTreeTest
    [ RUN      ] DataFiles/ChristmasTreeTest.file/0
    [       OK ] DataFiles/ChristmasTreeTest.file/0 (0 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/1
    [       OK ] DataFiles/ChristmasTreeTest.file/1 (0 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/2
    [       OK ] DataFiles/ChristmasTreeTest.file/2 (0 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/3
    [       OK ] DataFiles/ChristmasTreeTest.file/3 (2 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/4
    [       OK ] DataFiles/ChristmasTreeTest.file/4 (0 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/5
    [       OK ] DataFiles/ChristmasTreeTest.file/5 (1 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/6
    [       OK ] DataFiles/ChristmasTreeTest.file/6 (1 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/7
    [       OK ] DataFiles/ChristmasTreeTest.file/7 (4 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/8
    [       OK ] DataFiles/ChristmasTreeTest.file/8 (0 ms)
    [ RUN      ] DataFiles/ChristmasTreeTest.file/9
    [       OK ] DataFiles/ChristmasTreeTest.file/9 (4 ms)
    [----------] 10 tests from DataFiles/ChristmasTreeTest (14 ms total)

  ```

  </details>


## 3. Пятью восемь (JUNIOR)

Дано число N. Выяснить, сколько N-значных чисел можно составить,
используя цифры 5 и 8, в которых три одинаковые цифры не стоят рядом?

Начальные данные: натуральное число N.
Диапазон значений: N от 1 до 88.
Вывод результата: одно число — количество разных N-значных чисел по условию (сами числа выводить не надо).

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/dt_test 
    [----------] 6 tests from manual_five_and_eight_test
    [ RUN      ] manual_five_and_eight_test.N1
    [       OK ] manual_five_and_eight_test.N1 (0 ms)
    [ RUN      ] manual_five_and_eight_test.N2
    [       OK ] manual_five_and_eight_test.N2 (0 ms)
    [ RUN      ] manual_five_and_eight_test.N3
    [       OK ] manual_five_and_eight_test.N3 (0 ms)
    [ RUN      ] manual_five_and_eight_test.N4
    [       OK ] manual_five_and_eight_test.N4 (0 ms)
    [ RUN      ] manual_five_and_eight_test.N5
    [       OK ] manual_five_and_eight_test.N5 (0 ms)
    [ RUN      ] manual_five_and_eight_test.N_large
    [       OK ] manual_five_and_eight_test.N_large (0 ms)
    [----------] 6 tests from manual_five_and_eight_test (0 ms total)
    [----------] 10 tests from DataFiles/FiveAndEightTest
    [ RUN      ] DataFiles/FiveAndEightTest.file/0
    [       OK ] DataFiles/FiveAndEightTest.file/0 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/1
    [       OK ] DataFiles/FiveAndEightTest.file/1 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/2
    [       OK ] DataFiles/FiveAndEightTest.file/2 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/3
    [       OK ] DataFiles/FiveAndEightTest.file/3 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/4
    [       OK ] DataFiles/FiveAndEightTest.file/4 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/5
    [       OK ] DataFiles/FiveAndEightTest.file/5 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/6
    [       OK ] DataFiles/FiveAndEightTest.file/6 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/7
    [       OK ] DataFiles/FiveAndEightTest.file/7 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/8
    [       OK ] DataFiles/FiveAndEightTest.file/8 (0 ms)
    [ RUN      ] DataFiles/FiveAndEightTest.file/9
    [       OK ] DataFiles/FiveAndEightTest.file/9 (0 ms)
    [----------] 10 tests from DataFiles/FiveAndEightTest (0 ms total)

  ```

  </details>


## 4. Большой остров (JUNIOR)
Каждый элемент квадратной матрицы размеренности N x N равен нулю либо единице. Найдите количество «островов», образованных единицами. Под «островом» понимается группа единиц (либо одна единица), со всех сторон окруженная нулями (или краями матрицы). Единицы относятся к одному «острову», если из одной из них можно перейти к другой, «наступая» на единицы, расположенные в соседних клетках. Соседними являются клетки, граничащие по горизонтали или вертикали.

Входные данные
В первой строке вводится натуральное число N не больше 100 — размер квадратной матрицы.
В следующих N строках задаются элементы матрицы, по N чисел через пробел на каждой.

Выходные данные
Вывести единственное число — количество островов.

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/dt_test
    [----------] 8 tests from manual_big_island_test
    [ RUN      ] manual_big_island_test.two_islands
    [       OK ] manual_big_island_test.two_islands (0 ms)
    [ RUN      ] manual_big_island_test.five_islands
    [       OK ] manual_big_island_test.five_islands (0 ms)
    [ RUN      ] manual_big_island_test.not_connected
    [       OK ] manual_big_island_test.not_connected (0 ms)
    [ RUN      ] manual_big_island_test.single_islands
    [       OK ] manual_big_island_test.single_islands (0 ms)
    [ RUN      ] manual_big_island_test.to_islands
    [       OK ] manual_big_island_test.to_islands (0 ms)
    [ RUN      ] manual_big_island_test.single_cell
    [       OK ] manual_big_island_test.single_cell (0 ms)
    [ RUN      ] manual_big_island_test.l_shaped_islands
    [       OK ] manual_big_island_test.l_shaped_islands (0 ms)
    [ RUN      ] manual_big_island_test.empty_grid
    [       OK ] manual_big_island_test.empty_grid (0 ms)
    [----------] 8 tests from manual_big_island_test (0 ms total)
    [----------] 10 tests from DataFiles/BigIslandTest
    [ RUN      ] DataFiles/BigIslandTest.file/0
    [       OK ] DataFiles/BigIslandTest.file/0 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/1
    [       OK ] DataFiles/BigIslandTest.file/1 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/2
    [       OK ] DataFiles/BigIslandTest.file/2 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/3
    [       OK ] DataFiles/BigIslandTest.file/3 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/4
    [       OK ] DataFiles/BigIslandTest.file/4 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/5
    [       OK ] DataFiles/BigIslandTest.file/5 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/6
    [       OK ] DataFiles/BigIslandTest.file/6 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/7
    [       OK ] DataFiles/BigIslandTest.file/7 (0 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/8
    [       OK ] DataFiles/BigIslandTest.file/8 (1 ms)
    [ RUN      ] DataFiles/BigIslandTest.file/9
    [       OK ] DataFiles/BigIslandTest.file/9 (5 ms)
    [----------] 10 tests from DataFiles/BigIslandTest (7 ms total)

  ```

  </details>

## 5. Большой сарай

Задача на поиск максимального по площади прямоугольника, состоящего только из нулей, в бинарной матрице. Реализация разделена на несколько этапов — от простого перебора до оптимального решения.

### Оглавление

- [Условие задачи (MIDDLE)](#условие-задачи-middle)
- [Этап 1. Маленький сарай](#этап-1-маленький-сарай)
- [Этап 2. Длина сарая](#этап-2-длина-сарая)
- [Этап 3. Ширина сарая](#этап-3-ширина-сарая)
- [Условие задачи (SENIOR)](#условие-задачи-senior)
- [Этап 4. Большой сарай](#этап-4-большой-сарай)
- [Решение. Все этапы](#решение-все-этапы)
---

### Условие задачи (MIDDLE)

**Большой и маленький сарай**

Фермер хочет построить на своей земле как можно больший по площади сарай. На участке есть деревья и хозяйственные постройки, которые нельзя переносить.

Представим ферму как сетку размера **N × M**. Каждая постройка занимает один узел сетки. Требуется найти максимальную площадь сарая (прямоугольник, состоящий только из свободных клеток).

#### Входные данные:
- **Первая строка:** `N M` — размеры матрицы (1 ≤ N, M ≤ 1000).
- **Вторая строка:** `T` — количество занятых клеток (0 ≤ T ≤ 10000).
- **Следующие T строк:** `X Y` — координаты построек (0 ≤ X < N, 0 ≤ Y < M).

#### Выходные данные:
- Одно число — максимальная площадь сарая (количество ячеек).

> Решение разделено на 4 этапа.

---

### Этап 1. Маленький сарай

*Простейшее решение полным перебором*

#### Условие
Решается та же задача поиска максимального прямоугольника из нулей, но с ограничениями и прямым вводом матрицы.

#### Входные данные:
- **Первая строка:** `N M` (1 ≤ N, M ≤ 30).
- **Следующие M строк:** по `N` элементов (`0` или `1`) через пробел.

#### Выходные данные:
- Одно число — максимальная площадь.

---

### Этап 2. Длина сарая 

*Преобразование матрицы в гистограммы* 

Для каждой клетки вычисляется, сколько свободных клеток находится **подряд вверх**, начиная с данной.

#### Входные данные:
- **Первая строка:** `N M` (1 ≤ N, M ≤ 1000).
- **Вторая строка:** `T` — количество занятых клеток (0 ≤ T ≤ 10000).
- **Следующие T строк:** `X Y` — координаты занятых клеток.

#### Выходные данные:
- Матрица **N × M** чисел, показывающих высоту «столбца» свободных клеток вверх от текущей позиции.
- Формат: `M` строк по `N` чисел через пробел.

---

### Этап 3. Ширина сарая

*Вычисление границ расширения прямоугольника* 

Для каждого элемента массива **A** (высоты столбца) определяются индексы ближайших меньших элементов слева и справа. Это позволяет вычислить максимальную ширину прямоугольника для заданной высоты.

#### Входные данные:
- **Первая строка:** `N` — длина массива (1 ≤ N ≤ 10000).
- **Следующие N строк:** элементы массива `A[i]` (0 ≤ A[i] ≤ 10000).

#### Выходные данные:
- **Первая строка:** Массив **L** — индексы самых левых элементов, которые ≥ текущего.
- **Вторая строка:** Массив **R** — индексы самых правых элементов, которые ≥ текущего.
- Индексация с нуля. Числа разделены пробелами.

#### Подсказка
Площадь прямоугольника для столбца `i` вычисляется по формуле:
`Площадь = A[i] * (R[i] - L[i] + 1)`

---

### Условие задачи (SENIOR)

**Большой сарай. Итоговое решение** 

Финальная сборка всех этапов в одну программу. Решается задача, описанная в блоке MIDDLE, с исходными ограничениями N, M ≤ 1000.

#### Входные данные:
- **Первая строка:** `N M` — размеры матрицы (1 ≤ N, M ≤ 1000).
- **Вторая строка:** `T` — количество занятых клеток (0 ≤ T ≤ 10000).
- **Следующие T строк:** `X Y` — координаты построек.

#### Выходные данные:
- Одно число — максимальная площадь сарая.

---

### Этап 4. Большой сарай 

## Решение. Все этапы
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    [----------] 8 tests from small_barn_test
    [ RUN      ] small_barn_test.simple
    [       OK ] small_barn_test.simple (0 ms)
    [ RUN      ] small_barn_test.empty
    [       OK ] small_barn_test.empty (0 ms)
    [ RUN      ] small_barn_test.center_empty
    [       OK ] small_barn_test.center_empty (0 ms)
    [ RUN      ] small_barn_test.all_filled
    [       OK ] small_barn_test.all_filled (0 ms)
    [ RUN      ] small_barn_test.single_empty_cell
    [       OK ] small_barn_test.single_empty_cell (0 ms)
    [ RUN      ] small_barn_test.empty_grid
    [       OK ] small_barn_test.empty_grid (0 ms)
    [ RUN      ] small_barn_test.single_row
    [       OK ] small_barn_test.single_row (0 ms)
    [ RUN      ] small_barn_test.single_column
    [       OK ] small_barn_test.single_column (0 ms)
    [----------] 8 tests from small_barn_test (0 ms total)
    [----------] 6 tests from barn_length_test
    [ RUN      ] barn_length_test.simple
    [       OK ] barn_length_test.simple (0 ms)
    [ RUN      ] barn_length_test.no_obstacles
    [       OK ] barn_length_test.no_obstacles (0 ms)
    [ RUN      ] barn_length_test.no_free
    [       OK ] barn_length_test.no_free (0 ms)
    [ RUN      ] barn_length_test.single_column
    [       OK ] barn_length_test.single_column (0 ms)
    [ RUN      ] barn_length_test.first_row_obstacle
    [       OK ] barn_length_test.first_row_obstacle (0 ms)
    [ RUN      ] barn_length_test.scattered_obstacles
    [       OK ] barn_length_test.scattered_obstacles (0 ms)
    [----------] 6 tests from barn_length_test (0 ms total)
    [----------] 9 tests from barn_width_test
    [ RUN      ] barn_width_test.example_from_task
    [       OK ] barn_width_test.example_from_task (0 ms)
    [ RUN      ] barn_width_test.increasing_sequence
    [       OK ] barn_width_test.increasing_sequence (0 ms)
    [ RUN      ] barn_width_test.secreasing_sequence
    [       OK ] barn_width_test.secreasing_sequence (0 ms)
    [ RUN      ] barn_width_test.all_equal
    [       OK ] barn_width_test.all_equal (0 ms)
    [ RUN      ] barn_width_test.single_element
    [       OK ] barn_width_test.single_element (0 ms)
    [ RUN      ] barn_width_test.empty_array
    [       OK ] barn_width_test.empty_array (0 ms)
    [ RUN      ] barn_width_test.min_in_middle
    [       OK ] barn_width_test.min_in_middle (0 ms)
    [ RUN      ] barn_width_test.max_in_middle
    [       OK ] barn_width_test.max_in_middle (0 ms)
    [ RUN      ] barn_width_test.every_other_max
    [       OK ] barn_width_test.every_other_max (0 ms)
    [----------] 9 tests from barn_width_test (0 ms total)
    [----------] 24 tests from big_barn_test
    [ RUN      ] big_barn_test.example_from_task
    [       OK ] big_barn_test.example_from_task (0 ms)
    [ RUN      ] big_barn_test.no_obstacles
    [       OK ] big_barn_test.no_obstacles (0 ms)
    [ RUN      ] big_barn_test.diagonal_obstacles
    [       OK ] big_barn_test.diagonal_obstacles (0 ms)
    [ RUN      ] big_barn_test.single_empty_cell
    [       OK ] big_barn_test.single_empty_cell (0 ms)
    [ RUN      ] big_barn_test.single_occupied_cell
    [       OK ] big_barn_test.single_occupied_cell (0 ms)
    [ RUN      ] big_barn_test.large_grid_with_one_obstacle
    [       OK ] big_barn_test.large_grid_with_one_obstacle (0 ms)
    [ RUN      ] big_barn_test.vertical_stripe
    [       OK ] big_barn_test.vertical_stripe (0 ms)
    [ RUN      ] big_barn_test.cross_obstacles
    [       OK ] big_barn_test.cross_obstacles (0 ms)
    [ RUN      ] big_barn_test.all_occupied
    [       OK ] big_barn_test.all_occupied (0 ms)
    [ RUN      ] big_barn_test.horizontal_obstacle_line
    [       OK ] big_barn_test.horizontal_obstacle_line (0 ms)
    [ RUN      ] big_barn_test.vertical_obstacle_line
    [       OK ] big_barn_test.vertical_obstacle_line (0 ms)
    [ RUN      ] big_barn_test.chess_pattern
    [       OK ] big_barn_test.chess_pattern (0 ms)
    [ RUN      ] big_barn_test.rectangle_in_corner
    [       OK ] big_barn_test.rectangle_in_corner (0 ms)
    [ RUN      ] big_barn_test.wide_field
    [       OK ] big_barn_test.wide_field (0 ms)
    [ RUN      ] big_barn_test.tall_field
    [       OK ] big_barn_test.tall_field (0 ms)
    [ RUN      ] big_barn_test.multiple_scattered_obstacles
    [       OK ] big_barn_test.multiple_scattered_obstacles (0 ms)
    [ RUN      ] big_barn_test.single_row
    [       OK ] big_barn_test.single_row (0 ms)
    [ RUN      ] big_barn_test.single_column
    [       OK ] big_barn_test.single_column (0 ms)
    [ RUN      ] big_barn_test.border_obstacles
    [       OK ] big_barn_test.border_obstacles (0 ms)
    [ RUN      ] big_barn_test.complex_case
    [       OK ] big_barn_test.complex_case (0 ms)
    [ RUN      ] big_barn_test.invalid_coordinates
    [       OK ] big_barn_test.invalid_coordinates (0 ms)
    [ RUN      ] big_barn_test.negative_coordinates
    [       OK ] big_barn_test.negative_coordinates (0 ms)
    [ RUN      ] big_barn_test.duplicate_obstacles
    [       OK ] big_barn_test.duplicate_obstacles (0 ms)
    [ RUN      ] big_barn_test.zero_size_grid
    [       OK ] big_barn_test.zero_size_grid (0 ms)
    [----------] 24 tests from big_barn_test (0 ms total)
    [----------] 1 test from verification_test
    [ RUN      ] verification_test.bruteforce_vs_optimal
    [       OK ] verification_test.bruteforce_vs_optimal (0 ms)
    [----------] 1 test from verification_test (0 ms total)
  ```

  </details>
