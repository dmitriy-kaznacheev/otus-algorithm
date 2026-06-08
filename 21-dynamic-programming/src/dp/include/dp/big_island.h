#pragma once

#include <vector>

namespace dp {

/**
 * "Большой остров" (JUNIOR 4)
 *
 * Подсчитывает количество 4-связных островов из единиц в квадратной матрице.
 *
 * @param grid квадратная матрица N×N из 0 и 1
 * @return количество островов
 */
int count_islands(const std::vector<std::vector<int>> &grid);

} // namespace dp
