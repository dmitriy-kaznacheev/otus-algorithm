#pragma once

#include <cstdint>

namespace dp {

/**
 * "Пятью восемь" (JUNIOR 3)
 *
 * Подсчитывает количество N-значных чисел из цифр 5 и 8,
 * в которых три одинаковые цифры не стоят рядом.
 *
 * @param N количество цифр (1 ≤ N ≤ 88)
 * @return количество таких чисел
 */
int64_t count_five_eight_numbers(int N);

} // namespace dp