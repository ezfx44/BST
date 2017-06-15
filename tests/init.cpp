#include <bst.h>
#include <catch.hpp>

SCENARIO ("init", "[init]")
{
  BST<int> test;
  REQUIRE(test.root_() == nullptr);
  REQUIRE(test.get_count() == 0);
}
SCENARIO("insert node", "[ins]")
{
  BST<int> test;
  test.insert_node(7);
  REQUIRE(test.get_count() == 1);
  REQUIRE(test.find_node(7, test.root_())->_key == 7);
}
SCENARIO("find node", "[find]")
{
  BST<int> test;
  test.insert_node(2);
  REQUIRE(test.find_node(2, test.root_()) != nullptr);
  REQUIRE(test.find_node(2, test.root_())->_key == 2);
}
SCENARIO("get root", "[root]")
{
  BST<int> test;
  test.insert_node(4);
  REQUIRE(test.root_() != 0);
}
SCENARIO ("reading/writing", "[r/wr]")
{
  BST<int> test1;
  test1.insert_node(1);
  test1.insert_node(2);
  test1.writing("file.txt");
  BST<int> test2;
  test2.reading("file.txt");
  REQUIRE(test2.find_node(1, test2.root_())!= nullptr);
  REQUIRE(test2.find_node(2, test2.root_())!= nullptr);
  REQUIRE(test1.get_count() == test2.get_count());
}
SCENARIO("delete", "[del]")
{
  BST<int> test;
  test.insert_node(8);
  test.insert_node(3);
  test.insert_node(1);
  test.insert_node(2);
  test.insert_node(6);
  test.insert_node(4);
  test.delete_val(3);
  REQUIRE(test.find_node(3, test.root_())== nullptr);
  REQUIRE(test.find_node(8, test.root_())== test.root_());
  REQUIRE(test.root_() != nullptr);
  REQUIRE(test.get_count() == 5);
}
