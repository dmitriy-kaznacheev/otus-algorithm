# Реализация алгоритма нахождения минимального остовного дерева

## Цель
Освоить реализацию алгоритма нахождения минимального остовного дерева (MST — Minimum Spanning Tree) .


## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/mst_test 
    [==========] Running 16 tests from 4 test suites.
    [----------] Global test environment set-up.
    [----------] 5 tests from graph_test
    [ RUN      ] graph_test.create
    [       OK ] graph_test.create (0 ms)
    [ RUN      ] graph_test.add_edges
    [       OK ] graph_test.add_edges (0 ms)
    [ RUN      ] graph_test.out_of_bounds
    [       OK ] graph_test.out_of_bounds (0 ms)
    [ RUN      ] graph_test.negative_weight
    [       OK ] graph_test.negative_weight (0 ms)
    [ RUN      ] graph_test.adjacency_list
    [       OK ] graph_test.adjacency_list (0 ms)
    [----------] 5 tests from graph_test (0 ms total)

    [----------] 3 tests from dsu_test
    [ RUN      ] dsu_test.init
    [       OK ] dsu_test.init (0 ms)
    [ RUN      ] dsu_test.union_and_find
    [       OK ] dsu_test.union_and_find (0 ms)
    [ RUN      ] dsu_test.rank_optimization
    [       OK ] dsu_test.rank_optimization (0 ms)
    [----------] 3 tests from dsu_test (0 ms total)

    [----------] 4 tests from kruskal_test
    [ RUN      ] kruskal_test.connected_graph
    [       OK ] kruskal_test.connected_graph (0 ms)
    [ RUN      ] kruskal_test.disconnected_graph
    [       OK ] kruskal_test.disconnected_graph (0 ms)
    [ RUN      ] kruskal_test.single_vertex
    [       OK ] kruskal_test.single_vertex (0 ms)
    [ RUN      ] kruskal_test.empty_graph
    [       OK ] kruskal_test.empty_graph (0 ms)
    [----------] 4 tests from kruskal_test (0 ms total)

    [----------] 4 tests from prim_test
    [ RUN      ] prim_test.connected_graph
    [       OK ] prim_test.connected_graph (0 ms)
    [ RUN      ] prim_test.disconnected_graph
    [       OK ] prim_test.disconnected_graph (0 ms)
    [ RUN      ] prim_test.different_start_vertex
    [       OK ] prim_test.different_start_vertex (0 ms)
    [ RUN      ] prim_test.invalid_start_vertex
    [       OK ] prim_test.invalid_start_vertex (0 ms)
    [----------] 4 tests from prim_test (0 ms total)

    [----------] Global test environment tear-down
    [==========] 16 tests from 4 test suites ran. (0 ms total)
    [  PASSED  ] 16 tests.
    
  ```

  </details>
