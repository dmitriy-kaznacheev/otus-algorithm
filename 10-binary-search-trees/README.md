# Двоичное дерево поиска (BST)

## Цель
Создать двоичное дерево поиска, реализовать один из вариантов балансировки.
Сравнить эффективность алгоритмов на случайных и упорядоченных данных.

## Описание

Реализовать следующие алгоритмы:
1. создать простейшее двоичное дерево поиска `bst` 
2. создать сбалансированное АВЛ-дерево `avl`
3. создать декартово дерево `treap`

Протестировать работу алгоритма:
* создать два дерева
* добавить N чисел в случайном (первое) и возрастающем (второе) порядке
* искать N/10 случайных чисел в каждом дереве
* удалить N/10 случайных элементов в каждом дереве

## Решение
  <br />
  <details>
    <summary>результаты тестов</summary>

  ```
    $ ./tests/bst_test 
    --- binary search tree [increasing] ---
    [ + ] insert:    25000 50s
    [ + ] search:     2500 0s
    [ + ] remove:     2500 4s

    --- binary search tree [random] ---
    [ + ] insert: 10000000 60s
    [ + ] search:  1000000 1s
    [ + ] remove:  1000000 5s

    --- avl binary search tree [increasing] ---
    [ + ] insert: 10000000 59s
    [ + ] is balanced before
    [ + ] search:  1000000 1s
    [ + ] remove:  1000000 6s
    [ + ] is balanced after

    --- avl binary search tree [random] ---
    [ + ] insert: 10000000 75s
    [ + ] is balanced before
    [ + ] search:  1000000 1s
    [ + ] remove:  1000000 8s
    [ + ] is balanced after

    --- treap binary search tree [increasing] ---
    [ + ] insert: 10000000 71s
    [ + ] is balanced before
    [ + ] search:  1000000 2s
    [ + ] remove:  1000000 7s
    [ + ] is balanced after

    --- treap binary search tree [random] ---
    [ + ] insert: 10000000 176s
    [ + ] is balanced before
    [ + ] search:  1000000 3s
    [ + ] remove:  1000000 7s
    [ + ] is balanced after
    
  ```

  </details>
