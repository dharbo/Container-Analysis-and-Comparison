#ifndef _operations_test_hpp_
#define _operations_test_hpp_

#include "operations.hpp"

#include <forward_list>
#include <list>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "book.hpp"
#include "doctest.hpp"

const Book book = Book("title", "author", "isbn", 123.45);
const Book other_book =
    Book("other-title", "other-author", "other-isbn", 543.21);
const Book unused_book = Book("unused", "unused", "unused", 333.33);

//
// INSERT AT BACK TESTS
//

TEST_CASE("InsertAtBackOfVector") {
  std::vector<Book> vec = std::vector<Book>();

  SUBCASE("EmptyVector") {
    insert_at_back_of_vector{vec}(book);
    CHECK_EQ(vec.size(), 1);
    CHECK_EQ(vec[0], book);
  }

  SUBCASE("NonEmptyVector") {
    vec.push_back(other_book);
    vec.push_back(other_book);
    insert_at_back_of_vector{vec}(book);
    CHECK_EQ(vec.size(), 3);
    CHECK_EQ(vec[0], other_book);
    CHECK_EQ(vec[1], other_book);
    CHECK_EQ(vec[2], book);
  }
}

TEST_CASE("InsertAtBackOfDll") {
  std::list<Book> dll = std::list<Book>();

  SUBCASE("EmptyDll") {
    insert_at_back_of_dll{dll}(book);
    CHECK_EQ(dll.size(), 1);
    CHECK_EQ(dll.front(), book);
  }

  SUBCASE("NonEmptyDll") {
    dll.push_back(other_book);
    dll.push_back(other_book);
    insert_at_back_of_dll{dll}(book);
    CHECK_EQ(dll.size(), 3);
    CHECK_EQ(dll.front(), other_book);
    CHECK_EQ(*std::next(dll.begin()), other_book);
    CHECK_EQ(dll.back(), book);
  }
}

TEST_CASE("InsertAtBackOfSll") {
  std::forward_list<Book> sll = std::forward_list<Book>();

  SUBCASE("EmptySll") {
    insert_at_back_of_sll{sll}(book);
    CHECK_EQ(*sll.begin(), book);
    CHECK_EQ(std::next(sll.begin()), sll.end());
  }

  SUBCASE("NonEmptySll") {
    sll.push_front(other_book);
    sll.push_front(other_book);
    insert_at_back_of_sll{sll}(book);
    CHECK_EQ(*sll.begin(), other_book);
    CHECK_EQ(*std::next(sll.begin()), other_book);
    CHECK_EQ(*std::next(sll.begin(), 2), book);
    CHECK_EQ(std::next(sll.begin(), 3), sll.end());
  }
}

//
// INSERT AT FRONT TESTS
//

TEST_CASE("InsertAtFrontOfVector") {
  std::vector<Book> vec = std::vector<Book>();

  SUBCASE("EmptyVector") {
    insert_at_front_of_vector{vec}(book);
    CHECK_EQ(vec.size(), 1);
    CHECK_EQ(vec[0], book);
  }

  SUBCASE("NonEmptyVector") {
    vec.push_back(other_book);
    vec.push_back(other_book);
    insert_at_front_of_vector{vec}(book);
    CHECK_EQ(vec.size(), 3);
    CHECK_EQ(vec[0], book);
    CHECK_EQ(vec[1], other_book);
    CHECK_EQ(vec[2], other_book);
  }
}

TEST_CASE("InsertAtFrontOfDll") {
  std::list<Book> dll = std::list<Book>();

  SUBCASE("EmptyDll") {
    insert_at_front_of_dll{dll}(book);
    CHECK_EQ(dll.size(), 1);
    CHECK_EQ(dll.front(), book);
  }

  SUBCASE("NonEmptyDll") {
    dll.push_back(other_book);
    dll.push_back(other_book);
    insert_at_front_of_dll{dll}(book);
    CHECK_EQ(dll.size(), 3);
    CHECK_EQ(dll.front(), book);
    CHECK_EQ(*std::next(dll.begin()), other_book);
    CHECK_EQ(dll.back(), other_book);
  }
}

TEST_CASE("InsertAtFrontOfSll") {
  std::forward_list<Book> sll = std::forward_list<Book>();

  SUBCASE("EmptySll") {
    insert_at_front_of_sll{sll}(book);
    CHECK_EQ(*sll.begin(), book);
    CHECK_EQ(std::next(sll.begin()), sll.end());
  }

  SUBCASE("NonEmptySll") {
    sll.push_front(other_book);
    sll.push_front(other_book);
    insert_at_front_of_sll{sll}(book);
    CHECK_EQ(*sll.begin(), book);
    CHECK_EQ(*std::next(sll.begin()), other_book);
    CHECK_EQ(*std::next(sll.begin(), 2), other_book);
    CHECK_EQ(std::next(sll.begin(), 3), sll.end());
  }
}

//
// INSERT INTO TESTS
//

TEST_CASE("InsertIntoBst") {
  std::map<std::string, Book> bst = std::map<std::string, Book>();

  SUBCASE("EmptyBst") {
    insert_into_bst{bst}(book);
    CHECK_EQ(bst.size(), 1);
    CHECK_EQ(bst[book.isbn()], book);
  }

  SUBCASE("NonEmptyBst") {
    bst[other_book.isbn()] = other_book;
    insert_into_bst{bst}(book);
    CHECK_EQ(bst.size(), 2);
    CHECK_EQ(bst[book.isbn()], book);
    CHECK_EQ(bst[other_book.isbn()], other_book);
  }
}

TEST_CASE("InsertIntoHashTable") {
  std::unordered_map<std::string, Book> hash_table =
      std::unordered_map<std::string, Book>();

  SUBCASE("EmptyHashTable") {
    insert_into_hash_table{hash_table}(book);
    CHECK_EQ(hash_table.size(), 1);
    CHECK_EQ(hash_table[book.isbn()], book);
  }

  SUBCASE("NonEmptyHashTable") {
    hash_table[other_book.isbn()] = other_book;
    insert_into_hash_table{hash_table}(book);
    CHECK_EQ(hash_table.size(), 2);
    CHECK_EQ(hash_table[book.isbn()], book);
    CHECK_EQ(hash_table[other_book.isbn()], other_book);
  }
}

//
// REMOVE FROM BACK TESTS
//

TEST_CASE("RemoveFromBackOfVector") {
  std::vector<Book> vec = std::vector<Book>();

  SUBCASE("EmptyVector") {
    CHECK_THROWS_AS(
        remove_from_back_of_vector{vec}(unused_book), std::out_of_range);
  }

  SUBCASE("NonEmptyVector") {
    vec.push_back(other_book);
    vec.push_back(other_book);
    vec.push_back(book);
    remove_from_back_of_vector{vec}(unused_book);
    CHECK_EQ(vec.size(), 2);
    CHECK_EQ(vec[0], other_book);
    CHECK_EQ(vec[1], other_book);
  }
}

TEST_CASE("RemoveFromBackOfDll") {
  std::list<Book> dll = std::list<Book>();

  SUBCASE("EmptyDll") {
    CHECK_THROWS_AS(
        remove_from_back_of_dll{dll}(unused_book), std::out_of_range);
  }

  SUBCASE("NonEmptyDll") {
    dll.push_back(other_book);
    dll.push_back(other_book);
    dll.push_back(book);
    remove_from_back_of_dll{dll}(unused_book);
    CHECK_EQ(dll.size(), 2);
    CHECK_EQ(dll.front(), other_book);
    CHECK_EQ(dll.back(), other_book);
  }
}

TEST_CASE("RemoveFromBackOfSll") {
  std::forward_list<Book> sll = std::forward_list<Book>();

  SUBCASE("EmptySll") {
    CHECK_THROWS_AS(
        remove_from_back_of_sll{sll}(unused_book), std::out_of_range);
  }

  SUBCASE("NonEmptySll") {
    sll.push_front(book);
    sll.push_front(other_book);
    sll.push_front(other_book);
    remove_from_back_of_sll{sll}(unused_book);
    CHECK_EQ(*sll.begin(), other_book);
    CHECK_EQ(*std::next(sll.begin()), other_book);
    CHECK_EQ(std::next(sll.begin(), 2), sll.end());
  }
}

//
// REMOVE FROM FRONT TESTS
//

TEST_CASE("RemoveFromFrontOfVector") {
  std::vector<Book> vec = std::vector<Book>();

  SUBCASE("EmptyVector") {
    CHECK_THROWS_AS(
        remove_from_front_of_vector{vec}(unused_book), std::out_of_range);
  }

  SUBCASE("NonEmptyVector") {
    vec.push_back(book);
    vec.push_back(other_book);
    vec.push_back(other_book);
    remove_from_front_of_vector{vec}(unused_book);
    CHECK_EQ(vec.size(), 2);
    CHECK_EQ(vec[0], other_book);
    CHECK_EQ(vec[1], other_book);
  }
}

TEST_CASE("RemoveFromFrontOfDll") {
  std::list<Book> dll = std::list<Book>();

  SUBCASE("EmptyDll") {
    CHECK_THROWS_AS(
        remove_from_front_of_dll{dll}(unused_book), std::out_of_range);
  }

  SUBCASE("NonEmptyDll") {
    dll.push_back(book);
    dll.push_back(other_book);
    dll.push_back(other_book);
    remove_from_front_of_dll{dll}(unused_book);
    CHECK_EQ(dll.size(), 2);
    CHECK_EQ(dll.front(), other_book);
    CHECK_EQ(dll.back(), other_book);
  }
}

TEST_CASE("RemoveFromFrontOfSll") {
  std::forward_list<Book> sll = std::forward_list<Book>();

  SUBCASE("EmptySll") {
    CHECK_THROWS_AS(
        remove_from_front_of_sll{sll}(unused_book), std::out_of_range);
  }

  SUBCASE("NonEmptySll") {
    sll.push_front(other_book);
    sll.push_front(other_book);
    sll.push_front(book);
    remove_from_front_of_sll{sll}(unused_book);
    CHECK_EQ(*sll.begin(), other_book);
    CHECK_EQ(*std::next(sll.begin()), other_book);
    CHECK_EQ(std::next(sll.begin(), 2), sll.end());
  }
}

//
// REMOVE FROM TESTS
//

TEST_CASE("RemoveFromBst") {
  std::map<std::string, Book> bst = std::map<std::string, Book>();

  SUBCASE("EmptyBst") {
    remove_from_bst{bst}(book);
    CHECK_EQ(bst.size(), 0);
  }

  SUBCASE("NonEmptyBst") {
    bst[book.isbn()] = book;
    bst[other_book.isbn()] = other_book;
    remove_from_bst{bst}(book);
    CHECK_EQ(bst.size(), 1);
    CHECK_EQ(bst.count(book.isbn()), 0);
    CHECK_EQ(bst[other_book.isbn()], other_book);
  }
}

TEST_CASE("RemoveFromHashTable") {
  std::unordered_map<std::string, Book> hash_table =
      std::unordered_map<std::string, Book>();

  SUBCASE("EmptyHashTable") {
    remove_from_hash_table{hash_table}(book);
    CHECK_EQ(hash_table.size(), 0);
  }

  SUBCASE("NonEmptyHashTable") {
    hash_table[book.isbn()] = book;
    hash_table[other_book.isbn()] = other_book;
    remove_from_hash_table{hash_table}(book);
    CHECK_EQ(hash_table.size(), 1);
    CHECK_EQ(hash_table.count(book.isbn()), 0);
    CHECK_EQ(hash_table[other_book.isbn()], other_book);
  }
}

//
// SEARCH TESTS
//

TEST_CASE("SearchWithinVector") {
  std::vector<Book> vec = std::vector<Book>();

  SUBCASE("ItemNotFound") {
    vec.push_back(other_book);
    vec.push_back(other_book);
    vec.push_back(other_book);
    const Book* const book_ptr =
        search_within_vector{vec, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, nullptr);
  }

  SUBCASE("ItemFound") {
    vec.push_back(other_book);
    vec.push_back(book);
    vec.push_back(other_book);
    const Book* const book_ptr =
        search_within_vector{vec, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, &vec[1]);
  }
}

TEST_CASE("SearchWithinDll") {
  std::list<Book> dll = std::list<Book>();

  SUBCASE("ItemNotFound") {
    dll.push_back(other_book);
    dll.push_back(other_book);
    dll.push_back(other_book);
    const Book* const book_ptr =
        search_within_dll{dll, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, nullptr);
  }

  SUBCASE("ItemFound") {
    dll.push_back(other_book);
    dll.push_back(book);
    dll.push_back(other_book);
    const Book* const book_ptr = 
        search_within_dll{dll, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, &(*std::next(dll.begin())));
  }
}

TEST_CASE("SearchWithinSll") {
  std::forward_list<Book> sll = std::forward_list<Book>();

  SUBCASE("ItemNotFound") {
    sll.push_front(other_book);
    sll.push_front(other_book);
    sll.push_front(other_book);
    const Book* const book_ptr =
        search_within_sll{sll, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, nullptr);
  }

  SUBCASE("ItemFound") {
    sll.push_front(other_book);
    sll.push_front(book);
    sll.push_front(other_book);
    const Book* const book_ptr =
        search_within_sll{sll, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, &(*std::next(sll.begin())));
  }
}

TEST_CASE("SearchWithinBst") {
  std::map<std::string, Book> bst = std::map<std::string, Book>();

  SUBCASE("ItemNotFound") {
    bst[other_book.isbn()] = other_book;
    const Book* const book_ptr =
        search_within_bst{bst, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, nullptr);
  }

  SUBCASE("ItemFound") {
    bst[book.isbn()] = book;
    bst[other_book.isbn()] = other_book;
    const Book* const book_ptr =
        search_within_bst{bst, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, &bst[book.isbn()]);
  }
}

TEST_CASE("SearchWithinHashTable") {
  std::unordered_map<std::string, Book> hash_table =
      std::unordered_map<std::string, Book>();

  SUBCASE("ItemNotFound") {
    hash_table[other_book.isbn()] = other_book;
    const Book* const book_ptr =
        search_within_hash_table{hash_table, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, nullptr);
  }

  SUBCASE("ItemFound") {
    hash_table[book.isbn()] = book;
    hash_table[other_book.isbn()] = other_book;
    const Book* const book_ptr =
        search_within_hash_table{hash_table, book.isbn()}(unused_book);
    CHECK_EQ(book_ptr, &hash_table[book.isbn()]);
  }
}

#endif