# Реализация алгоритмов поиска кратчайшего пути в графах

Алгоритмы поиска кратчайшего пути между вершинами во взвешенных графах. 
Реализованы два классических алгоритма: **Дейкстры** (для графов с неотрицательными весами рёбер) 
и **Беллмана‑Форда** (поддерживает отрицательные веса и детектирует отрицательные циклы).

## Цель
Освоить реализацию алгоритмов поиска кратчайшего пути во взвешенных графах.

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/graph_path_test 
    [==========] Running 6 tests from 3 test suites.
    [----------] Global test environment set-up.
    [----------] 2 tests from dejkstra_test
    [ RUN      ] dejkstra_test.normal_path
    [       OK ] dejkstra_test.normal_path (0 ms)
    [ RUN      ] dejkstra_test.unreachable_path
    [       OK ] dejkstra_test.unreachable_path (0 ms)
    [----------] 2 tests from dejkstra_test (0 ms total)

    [----------] 3 tests from belman_ford_test
    [ RUN      ] belman_ford_test.negative_weights
    [       OK ] belman_ford_test.negative_weights (0 ms)
    [ RUN      ] belman_ford_test.negative_cycle
    [       OK ] belman_ford_test.negative_cycle (0 ms)
    [ RUN      ] belman_ford_test.unreachable_path
    [       OK ] belman_ford_test.unreachable_path (0 ms)
    [----------] 3 tests from belman_ford_test (0 ms total)

    [----------] 1 test from template_test
    [ RUN      ] template_test.double_weights
    [       OK ] template_test.double_weights (0 ms)
    [----------] 1 test from template_test (0 ms total)

    [----------] Global test environment tear-down
    [==========] 6 tests from 3 test suites ran. (0 ms total)
    [  PASSED  ] 6 tests.
    
  ```

  </details>
