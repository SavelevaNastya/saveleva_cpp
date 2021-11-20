#include "pch.h"
#include "../DNA/Header.h"
#include "../DNA/Source.cpp"

TEST(TEST_FillNuclArray, FillNuclArray_TEST) {
	RNK rnk;
	ASSERT_EQ(rnk.length(), 0);
	rnk.append(A);
	ASSERT_EQ(rnk.length(), 1);
	ASSERT_EQ(rnk.get_capacity(), 16);
	size_t Size_tPerNucl = (sizeof(size_t) * 8) / 2;
	ASSERT_EQ(rnk.get_real_size(), ceil(1.0 * rnk.length() / Size_tPerNucl) * sizeof(size_t));
	RNK rnk1(A, 120);
	ASSERT_EQ(rnk1.get_real_size(), ceil(1.0 * rnk1.length() / Size_tPerNucl) * sizeof(size_t));
}

TEST(TEST_OPERATORS, TEST_SQUARE_BRACKETS) {
	RNK rnk(T, 16);
	const RNK rnk1(G, 17);

	//std::cout << rnk[0];

	ASSERT_TRUE(rnk[0] == T);
	ASSERT_TRUE(rnk1[16] == G);

	rnk[15] = G;
	ASSERT_TRUE(rnk[15] == G);

	rnk[14] = rnk1[0];
	ASSERT_TRUE(rnk[14] == G);
}

TEST(TEST_OPERATORS, TEST_EQUAL_OPERATOR) {
	RNK rnk;
	const RNK rnk1(C, 17);

	rnk = rnk1;
	ASSERT_EQ(rnk.length(), rnk1.length());
	ASSERT_EQ(rnk[0], rnk1[0]);
	ASSERT_EQ(rnk[16], rnk1[16]);
}

TEST(TEST_OPERATORS, TEST_PLUS_OPERATOR) {
	const RNK rnk(G, 17);
	const RNK rnk1(C, 17);

	const RNK rnkSUM(rnk + rnk1);
	ASSERT_TRUE(rnkSUM[0] == G);
	ASSERT_TRUE(rnkSUM[33] == C);

	const RNK rnkSUMMA(rnkSUM + rnk1);
	ASSERT_EQ(rnkSUMMA.length(), 0);
}

TEST(TEST_OPERATORS, TEST_IS_EQUAL_OPERATOR) {
	const RNK rnk(G, 16);
	const RNK rnk1(G, 16);
	const RNK rnk2(C, 16);
	const RNK rnk3(C, 14);

	ASSERT_TRUE(rnk == rnk1);
	ASSERT_FALSE(rnk2 == rnk3);
}

TEST(TEST_OPERATORS, TEST_IS_NOT_EQUAL_OPERATOR) {
	const RNK rnk(G, 16);
	const RNK rnk1(G, 16);
	const RNK rnk2(C, 16);
	const RNK rnk3(C, 14);

	ASSERT_FALSE(rnk != rnk1);
	ASSERT_TRUE(rnk2 != rnk3);
}

TEST(TEST_OPERATORS, TEST_NEGATION_OPERATOR) {
	RNK rnk(G, 16);
	RNK rnk1(C, 16);

	ASSERT_TRUE(rnk != rnk1);
	!rnk;
	ASSERT_TRUE(rnk == rnk1);
}

TEST(TEST_METHODS, TEST_APPEND) {
	RNK rnk;
	ASSERT_TRUE(rnk.get_capacity() >= rnk.length());
	for (int i = 0; i < 16; i++) {
		rnk.append(T);
	}
	ASSERT_TRUE(rnk.get_capacity() == rnk.length());
	rnk.append(T);
	ASSERT_TRUE(rnk.get_capacity() >= rnk.length());
	for (int i = 0; i < 1000000; i++) {
		rnk.append(T);
	}
	ASSERT_EQ(rnk.length(), 1000000);
	ASSERT_TRUE(rnk.get_capacity() >= rnk.length());
}

TEST(TEST_METHODS, TEST_IS_COMPLEMENTARY) {
	RNK rnk(G, 16);
	RNK rnk1(C, 16);
	RNK rnk2(A, 16);

	ASSERT_TRUE(rnk.isComplementary(rnk1));
	ASSERT_FALSE(rnk1.isComplementary(rnk2));
}

TEST(TEST_METHODS, TEST_SPLIT) {
	RNK rnk(T, 16);
	std::pair<RNK, RNK> two_rnk = rnk.split(7);
	RNK r(T, 8);
	ASSERT_TRUE(two_rnk.first == r);
	ASSERT_TRUE(two_rnk.second == r);

	RNK rnk1(T, 16);
}

TEST(TEST_METHODS, TEST_CARDINALITY) {
	RNK rnk(T, 16);
	ASSERT_EQ(rnk.length(), rnk.cardinality(T));
	for (int i = 0; i < 10; i++) {
		rnk.append(C);
	}
	ASSERT_EQ(10, rnk.cardinality(C));
	ASSERT_EQ(16, rnk.cardinality(T));

	for (int i = 0; i < 20; i++) {
		rnk.append(A);
	}

	std::unordered_map<Nucleotide, int, std::hash<int>> m = rnk.cardinality();

	ASSERT_EQ(20, m[A]);
	ASSERT_EQ(10, m[C]);
	ASSERT_EQ(16, m[T]);
}

TEST(TEST_METHODS, TEST_TRIM) {
	RNK rnk(A, 10);
	for (int i = 0; i < 1000; i++) {
		rnk.append(T);
	}
	rnk.trim(0);
	EXPECT_EQ(rnk.get_capacity(), 0);
}

