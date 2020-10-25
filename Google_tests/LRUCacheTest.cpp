#include "gtest/gtest.h"
#include "../LRUCache.h"

TEST(LRUCacheSuite, ZeroCapacity) {
    LRUCache<int, std::string> cache(0);
    cache.Put(1, "first");
    EXPECT_EQ(cache.GetSize(), 0);
    EXPECT_FALSE(cache.Get(1).has_value());
}

TEST(LRUCacheSuite, EmptyCache) {
    LRUCache<int, std::string> cache(5);
    EXPECT_EQ(cache.GetSize(), 0);
}

TEST(LRUCacheSuite, GetValue) {
    LRUCache<int, std::string> cache(5);
    cache.Put(1, "one");
    EXPECT_EQ(cache.GetSize(), 1);
    ASSERT_TRUE(cache.Get(1).has_value());
    EXPECT_EQ(cache.Get(1).value(), "one");
    EXPECT_FALSE(cache.Get(2).has_value());
}

TEST(LRUCacheSuite, GetDifferentValues) {
    LRUCache<int, std::string> cache(5);
    cache.Put(1, "one");
    cache.Put(2, "two");
    EXPECT_EQ(cache.GetSize(), 2);
    ASSERT_TRUE(cache.Get(1).has_value());
    EXPECT_EQ(cache.Get(1).value(), "one");
    ASSERT_TRUE(cache.Get(2).has_value());
    EXPECT_EQ(cache.Get(2).value(), "two");
}

TEST(LRUCacheSuite, PutTwoValuesInOneKey) {
    LRUCache<int, std::string> cache(5);
    cache.Put(1, "one");
    cache.Put(1, "two");
    EXPECT_EQ(cache.GetSize(), 1);
    ASSERT_TRUE(cache.Get(1).has_value());
    EXPECT_EQ(cache.Get(1).value(), "two");
}

TEST(LRUCacheSuite, AddMoreElementsThanCapacity) {
    LRUCache<int, std::string> cache(3);
    cache.Put(1, "one");
    cache.Put(2, "two");
    cache.Put(3, "three");
    EXPECT_EQ(cache.GetSize(), 3);
    cache.Put(4, "four");

    EXPECT_EQ(cache.GetSize(), 3);
    ASSERT_FALSE(cache.Get(1).has_value());
    ASSERT_TRUE(cache.Get(2).has_value());
    EXPECT_EQ(cache.Get(2).value(), "two");
    ASSERT_TRUE(cache.Get(3).has_value());
    EXPECT_EQ(cache.Get(3).value(), "three");
    ASSERT_TRUE(cache.Get(4).has_value());
    EXPECT_EQ(cache.Get(4).value(), "four");
}

TEST(LRUCacheSuite, RemoveOldest) {
    LRUCache<int, std::string> cache(3);
    cache.Put(1, "one");
    cache.Put(2, "two");
    cache.Put(3, "three");
    EXPECT_EQ(cache.GetSize(), 3);
    ASSERT_TRUE(cache.Get(1).has_value());

    cache.Put(4, "four");

    EXPECT_EQ(cache.GetSize(), 3);
    ASSERT_TRUE(cache.Get(1).has_value());
    EXPECT_EQ(cache.Get(1).value(), "one");
    ASSERT_FALSE(cache.Get(2).has_value());
    ASSERT_TRUE(cache.Get(3).has_value());
    EXPECT_EQ(cache.Get(3).value(), "three");
    ASSERT_TRUE(cache.Get(4).has_value());
    EXPECT_EQ(cache.Get(4).value(), "four");
}

