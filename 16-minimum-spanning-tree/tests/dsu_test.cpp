#include <mst/core.h>
#include <gtest/gtest.h>

TEST(dsu_test, init) {
  mst::DSU dsu(3);
  EXPECT_EQ(dsu.find(0), 0);
  EXPECT_EQ(dsu.find(1), 1);
  EXPECT_EQ(dsu.find(2), 2);
}

TEST(dsu_test, union_and_find) {
  mst::DSU dsu(3);

  // объединенить 0 и 1
  EXPECT_TRUE(dsu.unite(0, 1));
  EXPECT_EQ(dsu.find(0), dsu.find(1));

  // попытка объединить уже объединённые
  EXPECT_FALSE(dsu.unite(0, 1));

  // объединенить с 2
  EXPECT_TRUE(dsu.unite(1, 2));
  EXPECT_EQ(dsu.find(0), dsu.find(2));
}

TEST(dsu_test, rank_optimization) {
  mst::DSU dsu(4);
  dsu.unite(0, 1);
  dsu.unite(2, 3);
  dsu.unite(1, 3); // присоединить меньшее дерево к большему

  // все в одном множестве
  EXPECT_EQ(dsu.find(0), dsu.find(3));
}
