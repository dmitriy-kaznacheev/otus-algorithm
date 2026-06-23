# Реализация вероятностного алгоритма "Фильтр Блума"

## Цель
Изучение и реализация вероятностной структуры данных **Bloom Filter**, оценка её точности на синтетическом датасете.

## Описание алгоритма
Фильтр Блума позволяет проверять принадлежность элемента множеству, потребляя фиксированный объем памяти. 
Возможны ложноположительные срабатывания (**false positives**), но не бывает ложноотрицательных (**false negatives**).

**Параметры:**
- $m$ – размер битового массива;
- $k$ – количество хеш-функций;
- $n$ – ожидаемое количество элементов (`capacity`);
- $p$ – заданная допустимая вероятность ошибки (`error_rate`).

При инициализации $m$ и $k$ вычисляются автоматически по формулам:

$$
m = -\frac{n \cdot \ln(p)}{(\ln(2))^2}
$$

$$
k = \frac{m}{n} \cdot \ln(2)
$$

Для генерации $k$ индексов используется техника *double hashing*:

$$
\text{hash}_i(x) = (\text{hash}_1(x) + i \cdot \text{hash}_2(x)) \bmod m
$$

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/bloom_filter_test 
    [==========] Running 4 tests from 1 test suite.
    [----------] Global test environment set-up.
    [----------] 4 tests from BloomFilterTest
    [ RUN      ] BloomFilterTest.basic
    [       OK ] BloomFilterTest.basic (0 ms)
    [ RUN      ] BloomFilterTest.empty_filter
    [       OK ] BloomFilterTest.empty_filter (0 ms)
    [ RUN      ] BloomFilterTest.small_filter
    [       OK ] BloomFilterTest.small_filter (0 ms)
    [ RUN      ] BloomFilterTest.false_positive_rate

    ===== parameters ================
    capacity:     100000
    target error: 5%
    bit array:    623522 bits
    hash funcs:   4
    memory:       76.11 KB
    ----- results -----
    false negatives: 0 (must be 0)
    false positives: 504 
    expected rate:   5.00%
    observed rate:   5.04%
    z-score:         0.18 (ok)
    =================================

    [       OK ] BloomFilterTest.false_positive_rate (173 ms)
    [----------] 4 tests from BloomFilterTest (173 ms total)

    [----------] Global test environment tear-down
    [==========] 4 tests from 1 test suite ran. (173 ms total)
    [  PASSED  ] 4 tests.
  ```

  </details>
