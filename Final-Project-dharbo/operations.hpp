#ifndef _operations_hpp_
#define _operations_hpp_

#include <forward_list>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "book.hpp"

//
// INSERT OPERATIONS
//

struct insert_at_back_of_vector {
  // Function takes a constant Book as a parameter, inserts that book at the
  // back of a vector, and returns nothing.
  void operator()(const Book& book) {

    // Write the lines of code to insert "book" at the back of "my_vector".

    // Add the book to the back of the vector.
    my_vector.push_back(book);
  }

  std::vector<Book>& my_vector;
};

struct insert_at_back_of_dll {
  // Function takes a constant Book as a parameter, inserts that book at the
  // back of a doubly linked list, and returns nothing.
  void operator()(const Book& book) {
    // Write the lines of code to insert "book" at the back of "my_dll".

    // Add the book to the back of the DLL.
    my_dll.push_back(book);
  }

  std::list<Book>& my_dll;
};

struct insert_at_back_of_sll {
  // Function takes a constant Book as a parameter, inserts that book at the
  // back of a singly linked list, and returns nothing.
  void operator()(const Book& book) {
    // Write the lines of code to insert "book" at the back of "my_sll". Since
    // the SLL has no size() function and no tail pointer, you must walk the
    // list looking for the last node.
    //
    // HINT:  Do not attempt to insert after "my_sll.end()".

    // Create iterator for forward list.
    std::forward_list<Book>::iterator iter = my_sll.before_begin();
    // Traverse the SLL, advancing the iterator by one position at a time.
    for (auto& node : my_sll) {
      ++iter;
    }
    // Insert the book after the last position of the iterator.
    my_sll.insert_after(iter, book);
  }

  std::forward_list<Book>& my_sll;
};

struct insert_at_front_of_vector {
  // Function takes a constant Book as a parameter, inserts that book at the
  // front of a vector, and returns nothing.
  void operator()(const Book& book) {
    // Write the lines of code to insert "book" at the front of "my_vector".

    // Insert the book at the front of the vector using insert().
    my_vector.insert(my_vector.begin(), book);
  }

  std::vector<Book>& my_vector;
};

struct insert_at_front_of_dll {
  // Function takes a constant Book as a parameter, inserts that book at the
  // front of a doubly linked list, and returns nothing.
  void operator()(const Book& book) {
    // Write the lines of code to insert "book" at the front of "my_dll".

    // Insert the book to the front of the DLL using push_front().
    my_dll.push_front(book);
  }

  std::list<Book>& my_dll;
};

struct insert_at_front_of_sll{
  // Function takes a constant Book as a parameter, inserts that book at the
  // front of a singly linked list, and returns nothing.
  void operator()(const Book& book) {
    // Write the lines of code to insert "book" at the front of "my_sll"

    // Insert the book at the front of the SLL using push_front().
    my_sll.push_front(book);
  }

  std::forward_list<Book>& my_sll;
};

struct insert_into_bst {
  // Function takes a constant Book as a parameter, inserts that book indexed by
  // the book's ISBN into a binary search tree, and returns nothing.
  void operator()(const Book& book) {
    // Write the lines of code to insert the key (book's ISBN) and value
    // ("book") pair into "my_bst".

    // Use [] operator to insert the isbn as the key and set the value equal to book.
    my_bst[book.isbn()] = book;
  }

  std::map<std::string, Book>& my_bst;
};

struct insert_into_hash_table {
  // Function takes a constant Book as a parameter, inserts that book indexed by
  // the book's ISBN into a hash table, and returns nothing.
  void operator()(const Book& book) {
    // Write the lines of code to insert the key (book's ISBN) and value
    // ("book") pair into "my_hash_table".

    // Use [] operator to insert the isbn as the key and set the value equal to book.
    my_hash_table[book.isbn()] = book;
  }

  std::unordered_map<std::string, Book>& my_hash_table;
};

//
// REMOVE OPERATIONS
//

struct remove_from_back_of_vector {
  // Function takes no parameters, removes the book at the back of a vector, and
  // returns nothing.
  void operator()(const Book& unused) {
    // Write the lines of code to remove the book at the back of "my_vector".
    //
    // Remember, attempting to remove an element from an empty data structure is
    // a logic error. Include code to avoid that.

    // If the vector is empty, throw exception.
    if (my_vector.empty()) {
      throw std::out_of_range("Cannot remove from empty data structure.");
    }
    // Remove the element at the back of the vector.
    my_vector.pop_back();
  }

  std::vector<Book>& my_vector;
};

struct remove_from_back_of_dll {
  // Function takes no parameters, removes the book at the back of a doubly
  // linked list, and returns nothing.
  void operator()(const Book& unused) {
    // Write the lines of code to remove the book at the back of "my_dll".
    //
    // Remember, attempting to remove an element from an empty data structure is
    // a logic error. Include code to avoid that.

    // If the DLL is empty, throw exception.
    if (my_dll.empty()) {
      throw std::out_of_range("Cannot remove from empty data structure.");
    }
    // Remove the node at the back of the DLL.
    my_dll.pop_back();
  }

  std::list<Book>& my_dll;
};

struct remove_from_back_of_sll {
  // Function takes no parameters, removes the book at the back of a singly
  // linked list, and returns nothing.
  void operator()(const Book& unused) {
    // Write the lines of code to remove the book at the back of "my_sll".
    //
    // Remember, attempting to remove an element from an empty data structure is
    // a logic error. Include code to avoid that.
    //
    // Since the SLL has no size() function and no tail pointer, you must walk
    // the list looking for the last node.
    //
    // HINT:  If "my_sll" is empty, simply return. 
    //        Otherwise:
    //        o) Define two iterators called predecessor and current.
    //           Initialize predecessor to the node before the beginning, and
    //           current to the node at the beginning.
    //        o) Advance current to the next node.
    //        o) Walk the list until current is equal to end(), advancing both
    //           predecessor and current each time through the loop.
    //        o) Once current is equal to end(), then remove the node after
    //           predecessor

    // If the SLL is empty, throw exception.
    if (my_sll.empty()) {
      throw std::out_of_range("Cannot remove from empty data structure.");
    }
    // Set predecessor and current iterators.
    std::forward_list<Book>::iterator predecessor = my_sll.before_begin();
    std::forward_list<Book>::iterator current = my_sll.begin();
    // Advance current iterator by 1 position.
    std::advance(current, 1);
    // While current is not out of the SLL, advance current and predecessor by 1.
    while (current != my_sll.end()) {
      std::advance(current, 1);
      std::advance(predecessor, 1);
    }
    // Remove the node after predecessor.
    my_sll.erase_after(predecessor);
  }

  std::forward_list<Book>& my_sll;
};

struct remove_from_front_of_vector {
  // Function takes no parameters, removes the book at the front of a vector,
  // and returns nothing.
  void operator()(const Book& unused) {
    // Write the lines of code to remove the book at the front of "my_vector".
    //
    // Remember, attempting to remove an element from an empty data structure is
    // a logic error. Include code to avoid that.

    // If the vector is empty, throw exception.
    if (my_vector.empty()) {
      throw std::out_of_range("Cannot remove from empty data structure");
    }
    // Remove the element at the beginning of the vector.
    my_vector.erase(my_vector.begin());
  }

  std::vector<Book>& my_vector;
};

struct remove_from_front_of_dll {
  // Function takes no parameters, removes the book at the front of a doubly
  // linked list, and returns nothing.
  void operator()(const Book& unused) {
    // Write the lines of code to remove the book at the front of "my_dll".
    //
    // Remember, attempting to remove an element from an empty data structure is
    // a logic error. Include code to avoid that.

    // If the DLL is empty, throw exception.
    if (my_dll.empty()) {
      throw std::out_of_range("Cannot remove from empty data structure");
    }
    // Remove the first node in the DLL.
    my_dll.pop_front();
  }

  std::list<Book>& my_dll;
};

struct remove_from_front_of_sll {
  // Function takes no parameters, removes the book at the front of a singly
  // linked list, and returns nothing.
  void operator()(const Book& unused) {
    // Write the lines of code to remove the book at the front of "my_sll".
    //
    // Remember, attempting to remove an element from an empty data structure is
    // a logic error. Include code to avoid that.

    // If the SLL is empty, throw exception.
    if (my_sll.empty()) {
      throw std::out_of_range("Cannot remove from empty data structure");
    }
    // Remove the first node in the SLL.
    my_sll.pop_front();
  }

  std::forward_list<Book>& my_sll;
};

struct remove_from_bst {
  // Function takes a constant Book as a parameter, finds and removes from the
  // binary search tree the book with a matching ISBN (if any), and returns
  // nothing. If no Book matches the ISBN, the method does nothing.
  void operator()(const Book& book) {
    // Write the lines of code to remove the book from "my_bst" that has an ISBN
    // matching "book".

    // Find an iterator to a pair with book.isbn() as its key.
    std::map<std::string, Book>::iterator iter = my_bst.find(book.isbn());
    // If the iterator is not past the end, remove that pair.
    if (iter != my_bst.end()) {
      my_bst.erase(iter);
    }
  }

  std::map<std::string, Book>& my_bst;
};

struct remove_from_hash_table {
  // Function takes a constant Book as a parameter, finds and removes from the
  // hash table the book with a matching ISBN (if any), and returns nothing. If 
  // no Book matches the ISBN, the method does nothing.
  void operator()(const Book& book) {
    // Write the lines of code to remove the book from "my_hash_table" that has
    // an ISBN matching "book".

    // Find an iterator to a pair with book.isbn() as its key.
    std::unordered_map<std::string, Book>::iterator iter = 
                                        my_hash_table.find(book.isbn());
    // If the iterator is not past the end, remove that pair.
    if (iter != my_hash_table.end()) {
      my_hash_table.erase(iter);
    }
  }

  std::unordered_map<std::string, Book>& my_hash_table;
};

//
// SEARCH OPERATIONS
//

struct search_within_vector {
  // Function takes no parameters, searches a vector for a book with an ISBN
  // matching the target ISBN, and returns a pointer to that found book if such
  // a book is found, nullptr otherwise.
  Book* operator()(const Book& unused) {
    // Write the lines of code to search for the Book within "my_vector" with an
    // ISBN matching "target_isbn". Return a pointer to that book immediately
    // upon finding it, or a null pointer when you know the book is not in the
    // container.

    // Iterate through the vector. 
    for (int i = 0; i < my_vector.size(); ++i) {
      // If the current isbn matches the target's, then return a pointer to that book.
      if (my_vector[i].isbn() == target_isbn) {
        return &my_vector[i];
      }
    }
    return nullptr;
  }

  std::vector<Book>& my_vector;
  const std::string target_isbn;
};

struct search_within_dll {
  // Function takes no parameters, searches a doubly linked list for a book with
  // an ISBN matching the target ISBN, and returns a pointer to that found book
  // if such a book is found, nullptr otherwise.
  Book* operator()(const Book& unused) {
    // Write the lines of code to search for the Book within "my_dll" with an
    // ISBN matching "target_isbn". Return a pointer to that book immediately
    // upon finding it, or a null pointer when you know the book is not in the
    // container.

    // Traverse the DLL.
    for (auto& book : my_dll) {
      // If the current isbn matches the target's, then return a pointer to that book.
      if (book.isbn() == target_isbn) {
        return &book;
      }
    }
    return nullptr;
  }

  std::list<Book>& my_dll;
  const std::string target_isbn;
};

struct search_within_sll {
  // Function takes no parameters, searches a singly linked list for a book with
  // an ISBN matching the target ISBN, and returns a pointer to that found book
  // if such a book is found, nullptr otherwise.
  Book* operator()(const Book& unused) {
    // Write the lines of code to search for the Book within "my_sll" with an
    // ISBN matching "target_isbn". Return a pointer to that book immediately
    // upon finding it, or a null pointer when you know the book is not in the
    // container.

    // Traverse the SLL.
    for (auto& book : my_sll) {
      // If the current isbn matches the target's, then return a pointer to that book.
      if (book.isbn() == target_isbn) {
        return &book;
      }
    }
    return nullptr;
  }

  std::forward_list<Book>& my_sll;
  const std::string target_isbn;
};

struct search_within_bst {
  // Function takes no parameters, searches a binary search tree for a book with
  // an ISBN matching the target ISBN, and returns a pointer to that found book
  // if such a book is found, nullptr otherwise.
  Book* operator()(const Book& unused) {
    // Write the lines of code to search for the Book within "my_bst" with an
    // ISBN matching "target_isbn". Return a pointer to that book immediately
    // upon finding it, or a null pointer when you know the book is not in the
    // container.
    //
    // NOTE: Do not implement a linear search, i.e., do not loop from beginning
    // to end.

    // If the target isbn is found within the BST.
    if (my_bst.find(target_isbn) != my_bst.end()) {
      // Return a pointer to that book.
      return &my_bst.at(target_isbn);
    }
    return nullptr;
  }

  std::map<std::string, Book>& my_bst;
  const std::string target_isbn;
};

struct search_within_hash_table {
  // Function takes no parameters, searches a hash table for a book with an ISBN
  // matching the target ISBN, and returns a pointer to that found book if such
  // a book is found, nullptr otherwise.
  Book* operator()(const Book& unused) {
    // Write the lines of code to search for the Book within "my_hash_table"
    // with an ISBN matching "target_isbn". Return a pointer to that book
    // immediately upon finding it, or a null pointer when you know the book is
    // not in the container.
    //
    // NOTE: Do not implement a linear search, i.e., do not loop from beginning
    // to end.

    // If the target isbn is found within the Hash Table.
    if (my_hash_table.find(target_isbn) != my_hash_table.end()) {
      // Return a pointer to that book.
      return &my_hash_table.at(target_isbn);
    }
    return nullptr;
  }

  std::unordered_map<std::string, Book>& my_hash_table;
  const std::string target_isbn;
};

#endif
