# Задачи на динамическое программирование

## Цель
Освоить реализацию задач на динамическое программирование

### JUNIOR  
#### 1. Раз горох, два горох

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


#### Решение
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

#### 2. Ёлочка программиста 

Новогодняя ёлочка программиста состоит из цифр.

На первой строке записана высота ёлочки — натуральное число от 1 до 100.

Далее на N строчках зарисована сама ёлочка: сначала 1 цифра, потом 2, на последней строке — N цифр через пробел. В начале и в конце каждой строки могут быть пробелы, чтобы ёлочка получилась красивой.

**Гирляндой** называется последовательность цифр, которую можно получить, спускаясь от верхушки ёлки до её подножья, каждый раз смещаясь либо влево-вниз, либо вправо-вниз.

Найти гирлянду с максимальной суммой цифр.

**Вывести** одно число — максимальную сумму найденной гирлянды.

#### Решение
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


#### 3. Пятью восемь 

Дано число N. Выяснить, сколько N-значных чисел можно составить,
используя цифры 5 и 8, в которых три одинаковые цифры не стоят рядом?

Начальные данные: натуральное число N.
Диапазон значений: N от 1 до 88.
Вывод результата: одно число — количество разных N-значных чисел по условию (сами числа выводить не надо).

#### Решение
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
