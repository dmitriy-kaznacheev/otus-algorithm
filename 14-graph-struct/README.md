# Cтруктуры данных для работы с графами

## Цель
Реализовать набор шаблонных структур данных для работы с графами в C++ с использованием статического полиморфизма (CRTP).


## Описание
  - **статический полиморфизм**: использование CRTP вместо виртуальных функций для повышения производительности;
  - **шаблонные структуры**: поддержка любых типов вершин и рёбер;
  - **единый интерфейс**: все реализации следуют общему API;
  - **полный набор представлений графа**: 9 различных способов хранения;
  - **встроенные тесты**: автоматическая проверка корректности каждой реализации.


## Поддерживаемые представления графа
  - **Перечисление множеств (`EnumerateGraph`)**: перечисление множеств вершин и рёбер. 
  - **Матрица смежности (`AdjacencyMatrixGraph`)**: эффективное хранение плотных графов;
  - **Матрица инцидентности (`IncidenceMatrixGraph`)**: для задач с анализом инцидентности;
  - **Перечень рёбер (`EdgeListGraph`)**: компактное хранение разреженных графов;
  - **Векторы смежности (`AdjacencyVectorGraph`)**: альтернатива спискам смежности;
  - **Массивы смежности (`AdjacencyArrayGraph`)**: фиксированный размер, высокая скорость доступа;
  - **Списки смежности (`AdjacencyListGraph`)**: баланс памяти и скорости;
  - **Структура с оглавлением (`IndexedGraph`)**: оптимизированный доступ к соседям;
  - **Список вершин и список рёбер (`VertexEdgeListGraph`)**: простая структура для анализа;

## Основные операции
Все реализации поддерживают единый набор операций:
  - `add_vertex(v)` — добавить вершину;
  - `add_edge(e)` — добавить ребро;
  - `has_edge(from, to)` — проверить существование ребра;
  - `get_neighbors(v)` — получить соседей вершины;
  - `vertex_count()` — количество вершин;
  - `edge_count()` — количество рёбер;
  - `get_vertices()` — получить все вершины;
  - `get_edges()` — получить все рёбра.

## Анализ алгоритмической сложности реализаций графа

В данной библиотеке реализовано несколько способов хранения графа. Выбор конкретного класса зависит от плотности графа (соотношения рёбер и вершин) и частоты выполнения специфических операций.

### Сводная таблица сложности методов

| Класс реализации | Добавление вершины | Добавление ребра | Проверка наличия ребра | Получение соседей | Память |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **AdjacencyArrayGraph** | $O(1)$ | $O(D)$ | $O(D)$ | $O(D)$ | $O(V_{max}^2)$ |
| **AdjacencyListGraph** | $O(1)$ | $O(D)$ | $O(D)$ | $O(D)$ | $O(V + E)$ |
| **AdjacencyMatrixGraph** | $O(V)$ | $O(V)$ | **$O(1)$** | $O(V)$ | $O(V^2)$ |
| **AdjacencyVectorGraph** | $O(1)$ | $O(D)$ | $O(D)$ | $O(D)$ | $O(V + E)$ |
| **EdgeListGraph** | $O(1)$ | $O(E)$ | $O(E)$ | $O(E)$ | $O(V + E)$ |
| **EnumerateGraph** | $O(1)$ | $O(1)$ | **$O(1)$** | $O(E)$ | $O(V + E)$ |
| **IncidenceMatrixGraph** | $O(V \cdot E)$ | $O(V \cdot E)$ | $O(E)$ | $O(E)$ | $O(V \cdot E)$ |
| **IndexedGraph** | $O(1)$ | $O(D)$ | $O(D)$ | $O(D)$ | $O(V + E)$ |
| **VertexEdgeListGraph** | $O(V)$ | $O(V + E)$ | $O(E)$ | $O(E)$ | $O(V + E)$ |

**Обозначения:**
  - **V** — общее количество вершин.
  - **E** — общее количество рёбер.
  - **D** — степень вершины (количество смежных рёбер).
  - **$O(1)$** — амортизированная константная сложность (использование хэш-таблиц).

### Рекомендации по выбору
  - **Универсальный выбор:** `AdjacencyVectorGraph`. Оптимален по памяти и скорости итерации благодаря кэш-локальности векторов.
  - **Для плотных графов ($E \approx V^2$):** `AdjacencyMatrixGraph`. Позволяет мгновенно проверять связь между вершинами.
  - **Для специфических вычислений:** `IncidenceMatrixGraph` (матрица инцидентности), если требуется работа с топологией в терминах инцидентности вершин и рёбер.
  - **Для поиска рёбер:** `EnumerateGraph`. Обеспечивает максимально быстрое добавление и проверку рёбер, но неэффективен при обходах (BFS/DFS).

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/graph_test 
    Running main() from /data/projects/otus-algorithm/14-graph-struct/build/_deps/googletest-src/googletest/src/gtest_main.cc
    [==========] Running 45 tests from 9 test suites.
    [----------] Global test environment set-up.
    [----------] 5 tests from GraphTest/0, where TypeParam = graph_core::EnumerateGraph<int>
    [ RUN      ] GraphTest/0.vertex_operations
    [       OK ] GraphTest/0.vertex_operations (0 ms)
    [ RUN      ] GraphTest/0.edge_operations
    [       OK ] GraphTest/0.edge_operations (0 ms)
    [ RUN      ] GraphTest/0.get_neighbors
    [       OK ] GraphTest/0.get_neighbors (0 ms)
    [ RUN      ] GraphTest/0.get_edges
    [       OK ] GraphTest/0.get_edges (0 ms)
    [ RUN      ] GraphTest/0.boundary_cases
    [       OK ] GraphTest/0.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/0 (0 ms total)

    [----------] 5 tests from GraphTest/1, where TypeParam = graph_core::AdjacencyMatrixGraph<int>
    [ RUN      ] GraphTest/1.vertex_operations
    [       OK ] GraphTest/1.vertex_operations (0 ms)
    [ RUN      ] GraphTest/1.edge_operations
    [       OK ] GraphTest/1.edge_operations (0 ms)
    [ RUN      ] GraphTest/1.get_neighbors
    [       OK ] GraphTest/1.get_neighbors (0 ms)
    [ RUN      ] GraphTest/1.get_edges
    [       OK ] GraphTest/1.get_edges (0 ms)
    [ RUN      ] GraphTest/1.boundary_cases
    [       OK ] GraphTest/1.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/1 (0 ms total)

    [----------] 5 tests from GraphTest/2, where TypeParam = graph_core::IncidenceMatrixGraph<int>
    [ RUN      ] GraphTest/2.vertex_operations
    [       OK ] GraphTest/2.vertex_operations (0 ms)
    [ RUN      ] GraphTest/2.edge_operations
    [       OK ] GraphTest/2.edge_operations (0 ms)
    [ RUN      ] GraphTest/2.get_neighbors
    [       OK ] GraphTest/2.get_neighbors (0 ms)
    [ RUN      ] GraphTest/2.get_edges
    [       OK ] GraphTest/2.get_edges (0 ms)
    [ RUN      ] GraphTest/2.boundary_cases
    [       OK ] GraphTest/2.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/2 (0 ms total)

    [----------] 5 tests from GraphTest/3, where TypeParam = graph_core::EdgeListGraph<int>
    [ RUN      ] GraphTest/3.vertex_operations
    [       OK ] GraphTest/3.vertex_operations (0 ms)
    [ RUN      ] GraphTest/3.edge_operations
    [       OK ] GraphTest/3.edge_operations (0 ms)
    [ RUN      ] GraphTest/3.get_neighbors
    [       OK ] GraphTest/3.get_neighbors (0 ms)
    [ RUN      ] GraphTest/3.get_edges
    [       OK ] GraphTest/3.get_edges (0 ms)
    [ RUN      ] GraphTest/3.boundary_cases
    [       OK ] GraphTest/3.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/3 (0 ms total)

    [----------] 5 tests from GraphTest/4, where TypeParam = graph_core::AdjacencyVectorGraph<int>
    [ RUN      ] GraphTest/4.vertex_operations
    [       OK ] GraphTest/4.vertex_operations (0 ms)
    [ RUN      ] GraphTest/4.edge_operations
    [       OK ] GraphTest/4.edge_operations (0 ms)
    [ RUN      ] GraphTest/4.get_neighbors
    [       OK ] GraphTest/4.get_neighbors (0 ms)
    [ RUN      ] GraphTest/4.get_edges
    [       OK ] GraphTest/4.get_edges (0 ms)
    [ RUN      ] GraphTest/4.boundary_cases
    [       OK ] GraphTest/4.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/4 (0 ms total)

    [----------] 5 tests from GraphTest/5, where TypeParam = graph_core::AdjacencyArrayGraph<int,10ul>
    [ RUN      ] GraphTest/5.vertex_operations
    [       OK ] GraphTest/5.vertex_operations (0 ms)
    [ RUN      ] GraphTest/5.edge_operations
    [       OK ] GraphTest/5.edge_operations (0 ms)
    [ RUN      ] GraphTest/5.get_neighbors
    [       OK ] GraphTest/5.get_neighbors (0 ms)
    [ RUN      ] GraphTest/5.get_edges
    [       OK ] GraphTest/5.get_edges (0 ms)
    [ RUN      ] GraphTest/5.boundary_cases
    [       OK ] GraphTest/5.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/5 (0 ms total)

    [----------] 5 tests from GraphTest/6, where TypeParam = graph_core::AdjacencyListGraph<int>
    [ RUN      ] GraphTest/6.vertex_operations
    [       OK ] GraphTest/6.vertex_operations (0 ms)
    [ RUN      ] GraphTest/6.edge_operations
    [       OK ] GraphTest/6.edge_operations (0 ms)
    [ RUN      ] GraphTest/6.get_neighbors
    [       OK ] GraphTest/6.get_neighbors (0 ms)
    [ RUN      ] GraphTest/6.get_edges
    [       OK ] GraphTest/6.get_edges (0 ms)
    [ RUN      ] GraphTest/6.boundary_cases
    [       OK ] GraphTest/6.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/6 (0 ms total)

    [----------] 5 tests from GraphTest/7, where TypeParam = graph_core::IndexedGraph<int>
    [ RUN      ] GraphTest/7.vertex_operations
    [       OK ] GraphTest/7.vertex_operations (0 ms)
    [ RUN      ] GraphTest/7.edge_operations
    [       OK ] GraphTest/7.edge_operations (0 ms)
    [ RUN      ] GraphTest/7.get_neighbors
    [       OK ] GraphTest/7.get_neighbors (0 ms)
    [ RUN      ] GraphTest/7.get_edges
    [       OK ] GraphTest/7.get_edges (0 ms)
    [ RUN      ] GraphTest/7.boundary_cases
    [       OK ] GraphTest/7.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/7 (0 ms total)

    [----------] 5 tests from GraphTest/8, where TypeParam = graph_core::VertexEdgeListGraph<int>
    [ RUN      ] GraphTest/8.vertex_operations
    [       OK ] GraphTest/8.vertex_operations (0 ms)
    [ RUN      ] GraphTest/8.edge_operations
    [       OK ] GraphTest/8.edge_operations (0 ms)
    [ RUN      ] GraphTest/8.get_neighbors
    [       OK ] GraphTest/8.get_neighbors (0 ms)
    [ RUN      ] GraphTest/8.get_edges
    [       OK ] GraphTest/8.get_edges (0 ms)
    [ RUN      ] GraphTest/8.boundary_cases
    [       OK ] GraphTest/8.boundary_cases (0 ms)
    [----------] 5 tests from GraphTest/8 (0 ms total)

    [----------] Global test environment tear-down
    [==========] 45 tests from 9 test suites ran. (1 ms total)
    [  PASSED  ] 45 tests.
    
  ```

  </details>
