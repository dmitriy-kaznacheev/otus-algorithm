#pragma once

#include <numeric> // gcd
#include <string>

namespace dp {

/**
 * "Раз горох, два горох" (JUNIOR 1)
 *
 * Находит сумму двух дробей a/b + c/d, заданных строкой,
 * возвращает несократимую дробь в виде x/y.
 *
 * @param expression строка формата "a/b+c/d"
 * @return строка "x/y" — несократимая дробь
 * @throw std::invalid_argument если формат неверный
 */
std::string sum_fractions(const std::string &expression);

} // namespace dp
