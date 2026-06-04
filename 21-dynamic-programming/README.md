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
    [==========] Running 16 tests from 2 test suites.
    [----------] Global test environment set-up.
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

    [----------] Global test environment tear-down
    [==========] 16 tests from 2 test suites ran. (1 ms total)
    [  PASSED  ] 16 tests.
  ```

  </details>
