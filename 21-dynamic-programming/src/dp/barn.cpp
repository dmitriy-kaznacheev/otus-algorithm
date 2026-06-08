#include <algorithm>
#include <dp/barn.h>
#include <stack>
#include <stdexcept>

namespace {

constexpr int ZANYATO = 1;
constexpr int PUSTO = 0;

// проверка корректности координат препятствий
void validate_coordinates(int x, int y, int n, int m) {
  if ((x < 0) || (x >= n) || (y < 0) || (y >= m)) {
    throw std::out_of_range("Координаты препятствия (" + std::to_string(x) +
                            ", " + std::to_string(y) +
                            ") выходят за границы поля " + std::to_string(n) +
                            "x" + std::to_string(m));
  }
}

// cетка с препятствиями
std::vector<std::vector<int>>
create_grid(int n, int m, const std::vector<std::pair<int, int>> &blocked) {
  std::vector<std::vector<int>> grid(n, std::vector<int>(m, PUSTO));

  for (const auto &[x, y] : blocked) {
    validate_coordinates(x, y, n, m);
    grid[x][y] = ZANYATO;
  }

  return grid;
}

// матрица длин (сколько свободных клеток вверх от каждой позиции)
std::vector<std::vector<int>>
build_length_matrix(const std::vector<std::vector<int>> &grid) {

  int n = grid.size();
  int m = grid[0].size();
  std::vector<std::vector<int>> length(n, std::vector<int>(m, 0));

  for (int col = 0; col < m; ++col) {
    int consecutive_free = 0;
    for (int row = 0; row < n; ++row) {
      if (grid[row][col] == PUSTO) {
        ++consecutive_free;
      } else {
        consecutive_free = 0;
      }
      length[row][col] = consecutive_free;
    }
  }

  return length;
}

/*
 * вычисление максимальной площади прямоугольника в гистограмме
 *
 * алгоритм "Largest Rectangle in Histogram" с использованием монотонного стека:
 * для каждого столбца гистограммы находим максимальный прямоугольник,
 * который может использовать этот столбец как минимальную длин
 */
int max_rectangle_in_histogram(const std::vector<int> &lengths) {
  int n = lengths.size();
  std::stack<int> st;
  int max_area = 0;

  for (int i = 0; i <= n; ++i) {
    int current_length = (i == n) ? 0 : lengths[i];

    // пока текущая длина меньше длины на вершине стека,
    // вычисляем площадь прямоугольника с этой длиной
    while (!st.empty() && current_length < lengths[st.top()]) {
      int length = lengths[st.top()];
      st.pop();

      // ширина: если стек пуст, то прямоугольник идет от начала до i
      // иначе - от следующего после st.top() элемента до i
      int width = st.empty() ? i : i - st.top() - 1;
      max_area = std::max(max_area, length * width);
    }
    st.push(i);
  }

  return max_area;
}

} // namespace

namespace dp {

int max_barn_area_bruteforce(const std::vector<std::vector<int>> &grid) {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }

  int n = grid.size();
  int m = grid[0].size();
  int max_area = 0;

  // перебор всех возможных прямоугольников
  for (int top = 0; top < n; ++top) {
    for (int bottom = top; bottom < n; ++bottom) {
      for (int left = 0; left < m; ++left) {
        for (int right = left; right < m; ++right) {
          bool is_free = true;

          // проверка, что в прямоугольнике нет препятствий
          for (int i = top; i <= bottom && is_free; ++i) {
            for (int j = left; j <= right && is_free; ++j) {
              if (grid[i][j] == ZANYATO) {
                is_free = false;
              }
            }
          }

          if (is_free) {
            int area = (bottom - top + 1) * (right - left + 1);
            max_area = std::max(max_area, area);
          }
        }
      }
    }
  }

  return max_area;
}

std::vector<std::vector<int>>
compute_barn_length(int n, int m,
                    const std::vector<std::pair<int, int>> &blocked) {
  if ((n <= 0) || (m <= 0)) {
    return {};
  }

  auto grid = create_grid(n, m, blocked);
  return build_length_matrix(grid);
}

std::pair<std::vector<int>, std::vector<int>>
compute_barn_width(const std::vector<int> &lengths) {
  int n = lengths.size();
  std::vector<int> L(n), R(n);

  // L[i] — индекс самого левого элемента, который >= lengths[i]
  std::stack<int> st;
  for (int i = 0; i < n; ++i) {
    while (!st.empty() && lengths[st.top()] >= lengths[i]) {
      st.pop();
    }
    L[i] = st.empty() ? 0 : st.top() + 1;
    st.push(i);
  }

  // очистка стека
  std::stack<int>().swap(st);

  // R[i] — индекс самого правого элемента, который >= lengths[i]
  for (int i = n - 1; i >= 0; --i) {
    while (!st.empty() && lengths[st.top()] >= lengths[i]) {
      st.pop();
    }
    R[i] = st.empty() ? n - 1 : st.top() - 1;
    st.push(i);
  }

  return {L, R};
}

int max_barn_area(int n, int m,
                  const std::vector<std::pair<int, int>> &blocked) {
  if ((n <= 0) || (m <= 0)) {
    return 0;
  }

  auto grid = create_grid(n, m, blocked);

  auto length_matrix = build_length_matrix(grid);

  // поиск максимального прямоугольника для каждой строки в гистограмме длин
  int max_area = 0;
  for (int row = 0; row < n; ++row) {
    max_area =
        std::max(max_area, max_rectangle_in_histogram(length_matrix[row]));
  }

  return max_area;
}

} // namespace dp