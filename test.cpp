#include "pch.h"
#include "../unordered_map/HashMap.cpp"
#include <thread>

TEST(WriteFunctionsTest, EmplaceTest) {
	HashMap<int, std::string> map;
	EXPECT_EQ(map.GetCapacity(), 20);
	EXPECT_EQ(map.size(), 0);
	for (int i = 0; i < 10; ++i) {
		map.emplace(i, "TestString");
	}
	EXPECT_EQ(map.size(), 10);
}

TEST(WriteFunctionsTest, InsertTest) {
	HashMap<int, std::string> map;
	EXPECT_EQ(map.GetCapacity(), 20);
	ASSERT_TRUE(map.empty());
	for (int i = 0; i < 10; ++i) {
		auto pair = std::make_pair(i, "TestString");
		map.insert(pair);
	}
	EXPECT_EQ(map.size(), 10);

	
}
TEST(WriteFunctionsTest, SquaredBracketsTest) {
	HashMap<int, std::string> map{ std::make_pair(1, "first"), std::make_pair(2, "second"), std::make_pair(3, "third") };
	EXPECT_EQ(map[1], "first");
	map[1] = "one";
	EXPECT_EQ(map[1], "one");
}

TEST(WriteFunctionsTest, EqualOperatorTest) {
	HashMap<int, std::string> map{ std::make_pair(1, "first"), std::make_pair(2, "second"), std::make_pair(3, "third") };
	HashMap<int, std::string> map_new{ std::make_pair(4, "four"), std::make_pair(5, "five") };

	map = map_new;

	EXPECT_EQ(map.size(), map_new.size());
}

TEST(WriteFunctionsTest, SwapTest) {
	HashMap<int, std::string> map;

	for (int i = 0; i < 10; ++i) {
		auto pair = std::make_pair(i, "TestString");
		map.insert(pair);
	}

	HashMap<int, std::string> map_new;

	for (int i = 0; i < 5; ++i) {
		auto pair = std::make_pair(i, "TestString");
		map_new.insert(pair);
	}

	map.swap(map_new);

	EXPECT_EQ(map.size(), 5);
	EXPECT_EQ(map_new.size(), 10);
}

TEST(WriteFunctionsTest, RehashTest) {
	HashMap<int, std::string> map;
	EXPECT_EQ(map.GetCapacity(), 20);
	for (int i = 0; i < 20; ++i) {
		auto pair = std::make_pair(i, "TestString");
		map.insert(pair);
	}
	EXPECT_EQ(map.GetCapacity(), 40);
}

TEST(ThreadSafeTest, InsertTest) {
	HashMap<int, std::string> map;

	std::thread t1([&]() {
		for (int i = 0; i < 10; i++) {
			map.insert(i, "TestString");
		}
		});

	std::thread t2([&]() {
		for (int i = 0; i < 10; i++) {
			map.insert(i, "TestString_____");
		}
		});

	t1.join();
	t2.join();
}