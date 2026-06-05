#pragma once

#include <vector>

namespace dp {

/**
 * "Ёлочка программиста" (JUNIOR 2)
 *
 * Находит максимальную сумму гирлянды (путь сверху вниз
 * с движением влево-вниз или вправо-вниз) в треугольной матрице.
 *
 * @param triangle треугольная матрица: triangle[i] имеет размер i+1
 * @return максимальная сумма пути
 */
int max_garland_sum(const std::vector<std::vector<int>> &triangle);

} // namespace dp
