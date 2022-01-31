#include <algorithm>
#include <chrono>
#include <cstddef>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "book.hpp"
#include "operations.hpp"
#include "timer.hpp"

namespace {

// Preferred clock
using Clock = std::chrono::steady_clock;

// Create a matrix indexed by Data Structure and Operation that holds a collection of time samples collected to perform the operation.
using OperationName     = std::string;
using DataStructureName = std::string;
using SnapshotInterval  = std::size_t;
using ElapsedTime       = Clock::duration;

// A 3 dimensional collection of elapsed time measurements indexed by interval, data structure, and operation
using TimeMatrix = std::map<SnapshotInterval, std::map<DataStructureName, std::map<OperationName, ElapsedTime>>>;

struct Direction {
  enum value {Grow=1, Shrink=-Grow}; };

  using Utilities::Timer;

  template<typename Iter, typename T = typename Iter::value_type>
  struct SampleData : std::vector<T> {
    using std::vector<T>::vector;                                                                         // inherit constructors
    SampleData(Iter begin, Iter end) : std::vector<T>{begin, end} {
      this->shrink_to_fit();
      std::shuffle(
          this->begin(),
          this->end(),
          std::default_random_engine(std::random_device{}()));
    }
  };

  std::ostream & operator<<( std::ostream & stream, const TimeMatrix & matrix );

  template<class Operation>
  void measure(
      const std::string& structureName,                            // free text name of data structure being measured
      const std::string& operationDescription,                     // free text name of the operation of the data structure being measured
      Operation operation,                                // operation to be measured, expressed as a Functiod
      Direction::value direction = Direction::Grow);            // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)

  template<class Operation, class Preamble>
  void measure(
      const std::string& structureName,                            // free text name of data structure being measured
      const std::string& operationDescription,                     // free text name of the operation of the data structure being measured
      Preamble preamble,                                 // setup work to occur before operation, expressed as a Functiod
      Operation operation,                                // operation to be measured, expressed as a Functiod
      Direction::value direction = Direction::Grow);            // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)

  /*********************************************************************************************************************************
  **  Object Definitions
  *********************************************************************************************************************************/
  TimeMatrix runTimes;                                                 // collection of operation time measurements
  const SampleData sampleData{
      std::istream_iterator<Book>(std::cin),      // define and initialize from standard input a
      std::istream_iterator<Book>()
  };    // collection of data samples
}    // unnamed, anonymous namespace


int main() {
  Timer totalElapsedTime{"Timer:  total elapsed time is ", std::clog};

  //
  // VECTOR MEASUREMENTS
  //

  {
    std::clog << "\n\n\nStarting to collect Vector measurements\n";
    Timer timer{"Timer:  Vector measurements completed in ", std::clog};

    // Insert at the back of a vector
    {
      std::vector<Book> v;
      measure("Vector", "Insert at the back", insert_at_back_of_vector{v});
    }

    // Insert at the front of a vector
    {
      std::vector<Book> v;
      measure("Vector", "Insert at the front", insert_at_front_of_vector{v});
    }

    // Remove from the back of a vector
    {    
      std::vector<Book> v{sampleData.cbegin(), sampleData.cend()};
      measure("Vector", "Remove from the back", remove_from_back_of_vector{v}, Direction::Shrink);
    }

    // Remove from the front of a vector
    {
      std::vector<Book> v{sampleData.cbegin(), sampleData.cend()};
      measure("Vector", "Remove from the front", remove_from_front_of_vector{v}, Direction::Shrink);
    }

    // Search for an element in a vector
    {
      std::vector<Book> v;
      v.reserve(sampleData.size());
      measure(
          "Vector",
          "Search",
          [&](const Book& book) { v.push_back(book); },
          search_within_vector{v, "non-existent"});
    }
  }


  //
  // DOUBLY LINKED LIST MEASUREMENTS 
  //

  {
    std::clog << "\nStarting to collect Doubly Linked List measurements\n";
    Timer timer{"Timer:  Doubly Linked List measurements completed in ", std::clog};

    // Insert at the back of a doubly linked list
    {
      std::list<Book> dll;
      measure("DLL", "Insert at the back", insert_at_back_of_dll{dll});
    }

    // Insert at the front of a doubly linked list
    {
      std::list<Book> dll;
      measure("DLL", "Insert at the front", insert_at_front_of_dll{dll});
    }

    // Remove from the back of a doubly linked list
    {
      std::list<Book> dll{sampleData.cbegin(), sampleData.cend()};
      measure("DLL", "Remove from the back", remove_from_back_of_dll{dll}, Direction::Shrink);
    }

    // Remove from the front of a doubly linked list
    {
      std::list<Book> dll{sampleData.cbegin(), sampleData.cend()};
      measure("DLL", "Remove from the front", remove_from_front_of_dll{dll}, Direction::Shrink);
    }

    // Search for an element in a doubly linked list
    {
      std::list<Book> dll;
      measure(
          "DLL",
          "Search",
          [&](const Book& book) { dll.push_back(book); },
          search_within_dll{dll, "non-existent"});
    }
  }

  //
  // SINGLY LINKED LIST MEASUREMENTS
  //

  {
    std::clog << "\nStarting to collect Singly Linked List measurements\n";
    Timer timer{"Timer:  Singly Linked List measurements completed in ", std::clog};

    // Insert at the back of a singly linked list
    {
      std::forward_list<Book> sll;
      measure("SLL", "Insert at the back", insert_at_back_of_sll{sll});
    }

    // Insert at the front of a singly linked list
    {
      std::forward_list<Book> sll;
      measure("SLL", "Insert at the front", insert_at_front_of_sll{sll});
    }

    // Remove from the back of a singly linked list
    {
      std::forward_list<Book> ssl{sampleData.cbegin(), sampleData.cend()};
      measure("SLL", "Remove from the back", remove_from_back_of_sll{ssl}, Direction::Shrink);
    }

    // Remove from the front of a singly linked list
    {
      std::forward_list<Book> sll{sampleData.cbegin(), sampleData.cend()};
      measure("SLL", "Remove from the front", remove_from_front_of_sll{sll}, Direction::Shrink);
    }

    // Search for an element in a singly linked list
    {
      std::forward_list<Book> sll;
      measure(
          "SLL",
          "Search",
          [&](const Book& book) { sll.push_front(book); },
          search_within_sll{sll, "non-existent"});
    }
  }

  //
  // BINARY SEARCH TREE MEASUREMENTS

  {
    std::clog << "\nStarting to collect Binary Search Tree measurements\n";
    Timer timer{"Timer:  Binary Search Tree measurements completed in ", std::clog};
    
    // Insert into a binary search tree
    {
      std::map<std::string, Book> map;
      measure("BST", "Insert", insert_into_bst{map});
    }

    // Remove from a binary search tree
    {
      std::map<std::string, Book> map;
      for (const Book& book : sampleData) map.emplace(book.isbn(), book);
      measure("BST", "Remove", remove_from_bst{map}, Direction::Shrink);
    }

    // Search for an element in a binary search tree
    {
      std::map<std::string, Book> map;
      measure(
          "BST",
          "Search",
          [&](const Book& book) { map.emplace(book.isbn(), book); },
          search_within_bst{map, "non-existent"});
    }
  }

  //
  // HASH TABLE MEASUREMENTS
  //

  {
    std::clog << "\nStarting to collect Hash Table measurements\n";
    Timer timer{"Timer:  Hash Table measurements completed in ", std::clog};

    // Insert into a hash table
    {
      std::unordered_map<std::string, Book> u_map;
      measure("Hash Table", "Insert", insert_into_hash_table{u_map});
    }

    // Remove from a hash table
    {
      std::unordered_map<std::string, Book> u_map;
      for (const Book& book : sampleData) u_map.emplace(book.isbn(), book);
      measure("Hash Table", "Remove", remove_from_hash_table{u_map}, Direction::Shrink);
    }

    // Search for an element in a hash table
    {
      std::unordered_map<std::string, Book> u_map;
      measure(
          "Hash Table",
          "Search",
          [&](const Book& book) { u_map.emplace(book.isbn(), book); },
          search_within_hash_table{u_map, "non-existent"});
    }
  }

  //
  // REPORT MEASUREMENTS
  //
  std::cout << runTimes << '\n';

  std::clog << '\n'
            << std::string( 80, '-' ) << '\n';
}



/*********************************************************************************************************************************
**  Private definitions
*********************************************************************************************************************************/
namespace {
  template<class Operation>
  void measure( const std::string & structureName,                            // free text name of data structure being measured
                const std::string & operationDescription,                     // free text name of the operation of the data structure being measured
                Operation           operation,                                // operation to be measured, expressed as a Functiod
                Direction::value    direction )                               // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)
  {
    static auto noop = []( auto & ) {};                                       // A no-operation (do nothing) Functiod. Useful when requesting no setup be done prior to measuring an operation.
    measure( structureName, operationDescription, noop, operation, direction );
  }

  // Template function to measure the elapsed time consumed to perform a container's operation
  template<class Operation, class Preamble>
  void measure( const std::string & structureName,                            // free text name of data structure being measured
                const std::string & operationDescription,                     // free text name of the operation of the data structure being measured
                Preamble            preamble,                                 // setup work to occur before operation, expressed as a Functiod defaulted to "do nothing"
                Operation           operation,                                // operation to be measured, expressed as a Functiod
                Direction::value    direction )                               // indicates to record measurements as the container grows (i.e. inserts) or shrinks (i.e. removes)
  {
    struct progressRAII
    {
      progressRAII( const std::string & structureName, const std::string & operationDescription )
      { std::clog << "  starting " << structureName << "'s " << operationDescription << " operation ... "; }

      ~progressRAII()
      { std::clog << "finished"; }

      Timer duration{ " in ", std::clog };
    } progress_raii{structureName, operationDescription};

    constexpr std::size_t SAMPLE_SIZE = 250;                                  // Number of operations to perform before reporting timing data

    std::size_t sampleIndex = (direction == Direction::Grow) ? 0 : sampleData.size();
    for( const auto & element : sampleData )
    {
      preamble( element );                                                    // perform any setup work, but don't include this in the measured time

      // ToDo:  help prevent interruptions, perhaps with "critical section" or "Priority Boost"
      // ToDo:  Remove the function call overhead from the measurement, perhaps with some template or polymorphic std::variant magic
      auto start_time = Clock::now();
      operation( element );                                                   // perform the operation and measure the elapsed wall clock time, subject to the OS's task scheduling
      auto stop_time = Clock::now();

      //if( sampleIndex % SAMPLE_SIZE  ==  0)                                 // uncomment if you want single samples, otherwise it accumulates all the samples over the interval
      runTimes[( ( sampleIndex / SAMPLE_SIZE ) + 1 ) * SAMPLE_SIZE][structureName][operationDescription] += stop_time - start_time;
      sampleIndex += direction;
    }
  }

  std::ostream & operator<<( std::ostream & stream, const TimeMatrix & matrix )
  {
    if( !matrix.empty() )
    {
      // dump the data collected in a tab-separated values (tsv) table, for example:
      //   Size  Vector/insert  Vector/Remove  List/insert  List/remove
      //   10    1              1              23           14
      //   20    3              2              40           37

      // Display the table header
      stream << "Size";
      for( const auto & [structure, operations] : matrix.begin()->second ) for( const auto & [operation, accumulatedTime] : operations )
      {
        stream << ',' << structure << '/' << operation;
      }
      stream << '\n';

      // Display the table data
      for( const auto & [size, structures] : matrix )
      {
        stream << size;
        for( const auto & [structure, operations] : structures )  for( const auto & [operation, accumulatedTime] : operations )
        {
          stream << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>( accumulatedTime ).count();
        }
        stream << '\n';
      }
    }

    return stream;
  }
}  // namespace
