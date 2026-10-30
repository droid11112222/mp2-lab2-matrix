#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 5;
  TDynamicMatrix<int> m2(m1);
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 10;
  TDynamicMatrix<int> m2(m1);
  m2[0][0] = 20;
  EXPECT_EQ(m1[0][0], 10);
  EXPECT_EQ(m2[0][0], 20);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(3);
  EXPECT_EQ(m.size(), 3);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 42;
  EXPECT_EQ(m[1][2], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(3);
  ASSERT_ANY_THROW(m[0].at(-1) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);
  ASSERT_ANY_THROW(m[0].at(3) = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 7;
  m = m;
  EXPECT_EQ(m[0][0], 7);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0] = 9;
  m2 = m1;
  EXPECT_EQ(m2[0][0], 9);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(2), m2(5);
  m2 = m1;
  EXPECT_EQ(m2.size(), 2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(2), m2(4);
  m1[0][0] = 11;
  m2 = m1;
  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[0][0], 11);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][1] = 1;
  m2[0][1] = 1;
  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(2);
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(2), m2(3);
  EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0] = 1;
  m2[0][0] = 2;
  TDynamicMatrix<int> res = m1 + m2;
  EXPECT_EQ(res[0][0], 3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0] = 5;
  m2[0][0] = 3;
  TDynamicMatrix<int> res = m1 - m2;
  EXPECT_EQ(res[0][0], 2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_matrix)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0]=1; m1[0][1]=2;
  m1[1][0]=3; m1[1][1]=4;
  m2[0][0]=5; m2[0][1]=6;
  m2[1][0]=7; m2[1][1]=8;
  TDynamicMatrix<int> res = m1 * m2;
  EXPECT_EQ(res[0][0], 19);
  EXPECT_EQ(res[0][1], 22);
  EXPECT_EQ(res[1][0], 43);
  EXPECT_EQ(res[1][1], 50);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> m(2);
  m[0][0]=1; m[0][1]=2;
  m[1][0]=3; m[1][1]=4;
  TDynamicVector<int> v(2);
  v[0]=5; v[1]=6;
  TDynamicVector<int> res = m * v;
  EXPECT_EQ(res[0], 17);
  EXPECT_EQ(res[1], 39);
}