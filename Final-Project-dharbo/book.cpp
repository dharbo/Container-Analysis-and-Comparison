#include "book.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

//
// Constructors, Assignments, and Destructor
//

Book::Book(const std::string& title,
           const std::string& author,
           const std::string& isbn, 
           double price) : title_(title), author_(author), isbn_(isbn), price_(price) {}

Book::Book(const Book& other) = default;

Book& Book::operator=(const Book& rhs) = default;

// Destructor
Book::~Book() noexcept = default;

//
//  Accessors
//

const std::string& Book::isbn() const {
  // Gets isbn_
  return isbn_;
}

const std::string& Book::title() const {
  // Gets title_
  return title_;
}

const std::string& Book::author() const {
  // Gets author_
  return author_;
}

double Book::price() const {
  // Gets price_
  return price_;
}

std::string Book::isbn() {
  // Gets isbn_
  return isbn_;
}

std::string Book::title() {
  // Gets title_
  return title_;
}

std::string Book::author() {
  // Gets author_
  return author_;
}

//
// Modifiers
//

Book& Book::isbn(const std::string& new_isbn) {
  // Set and return the book's new isbn_
  isbn_ = new_isbn;
  return *this;
}

Book& Book::title(const std::string& new_title) {
  // Set and return the book's new title_
  title_ = new_title; 
  return *this;
}

Book& Book::author(const std::string& new_author) {
  // Set and return the book's new author_
  author_ = new_author;
  return *this;
}

Book& Book::price(double new_price) {
  // Set and return the book's new price_
  price_ = new_price;
  return *this;
}

//
// Relational Operators
//

bool Book::operator==(const Book& rhs) const noexcept {
  // Checks if lhs is == rhs
  return (title_ == rhs.title_ && author_ == rhs.author_   
    && isbn_ == rhs.isbn_ && price_ == rhs.price_);
}

bool Book::operator!=(const Book& rhs) const noexcept {
  // Checks if lhs is != rhs
  return !(*this == rhs);
}

bool Book::operator<(const Book& rhs) const noexcept {
  // Checks if lhs is < rhs
  if (isbn_ != rhs.isbn_) {
    return isbn_ < rhs.isbn_;
  }
  if (author_ != rhs.author_) {
    return author_ < rhs.author_;
  }
  if (title_ != rhs.title_) {
    return title_ < rhs.title_;
  } 
  if (price_ != rhs.price_) {
    return price_ < rhs.price_;
  }
  return false;
}

bool Book::operator<=(const Book& rhs) const noexcept {
  // Checks if lhs is <= rhs
  return *this < rhs || *this == rhs;
}

bool Book::operator>(const Book& rhs) const noexcept {
  // Checks if lhs is > rhs
  return rhs < *this;
}

bool Book::operator>=(const Book& rhs) const noexcept {
  // Checks if lhs is >= rhs
  return *this > rhs || *this == rhs;
}

//
// Insertion and Extraction Operators
//

std::istream & operator>>(std::istream& stream, Book& book) {
  // Input stream
  Book temp_book;
  char delimiter = ',';
  stream >> std::quoted(temp_book.isbn_) >> delimiter >> std::quoted(temp_book.title_)
    >> delimiter >> std::quoted(temp_book.author_) >> delimiter >> temp_book.price_;
  if (stream) {
    book = std::move(temp_book);
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Book& book) {
  // Output stream
  stream << std::quoted(book.isbn_)
      << ","
      << std::quoted(book.title_)
      << ","
      << std::quoted(book.author_)
      << ","
      << (book.price_)
      << std::endl;
  return stream;
}