/***********************************************************************************************************************************
** Class TimerType - A class of objects that keeps track of CPU time used since the object was created or last reset
**                   and reports that time in Resolution units.  It implicitly converts to Resolution units so it can
**                   be used like this:
**
**      Timer t;                                       // begin timing some operation, or
**      Timer t("The consumed time is:  ")             // begin timing some operation and provide results message, or
**      Timer t("The consumed time is:  ", std::clog)  // begin timing some operation, provide results message, and provide where to write message
**      ...
**      std::cout << t;                                // print out how much CPU time has elapsed in Resolution units
**
**  If a results message was provided at construction, that message and time duration is emitted at destruction
**
***********************************************************************************************************************************/

#ifndef _timer_hpp_
#define _timer_hpp_

#include <chrono>     // steady_clock, duration_cast<>(), hh_mm_ss(), now(), time_point
#include <iostream>
#include <string>
#include <utility>    // move()
#include <ratio>      // nano, micro, milli


/***********************************************************************************************************************************
// C++20 workarounds during migration - remove this section when C++20 is adopted and sufficiently supported
//
// Note:  MSVC requires the compiler switch /Zc:__cplusplus, otherwise the value of __cplusplus is always 199711
***********************************************************************************************************************************/
#if __cplusplus/100 < 2020  // Not using C++20
  namespace std::chrono
  {
    template<class Duration>
    class hh_mm_ss
    {
      public:
        hh_mm_ss( const Duration & duration ) : _duration { duration } {}
        constexpr std::chrono::hours        hours     () const noexcept { return std::chrono::duration_cast<std::chrono::hours>       ( _duration                                   ); }
        constexpr std::chrono::minutes      minutes   () const noexcept { return std::chrono::duration_cast<std::chrono::minutes>     ( _duration - hours()                         ); }
        constexpr std::chrono::seconds      seconds   () const noexcept { return std::chrono::duration_cast<std::chrono::seconds>     ( _duration - hours() - minutes()             ); }
        constexpr std::chrono::milliseconds subseconds() const noexcept { return std::chrono::duration_cast<std::chrono::milliseconds>( _duration - hours() - minutes() - seconds() ); }

      private:
        Duration _duration;
    };
  } // namespace std::chrono
#endif

// GCC version 11.1.1 and Clang version 12.0.0 do not yet define operator<<(std::ostream &, std::chrono::hh_mm__ss &).
//     Update this as new versions are released that still do not implement the function
#if __cplusplus/100 < 2020    ||                                                                                                \
    ( defined( __clang__ ) && ( __clang_major__ * 1'000'000 + __clang_minor__ * 1'000 + __clang_patchlevel__ <= 12'000'000 ) ) || \
    ( defined(__GNUC__ )   && (__GNUC__         * 1'000'000 + __GNUC_MINOR__  * 1'000 + __GNUC_PATCHLEVEL__  <= 11'001'001))
  namespace // anonymous
  {
    template<class Duration>
    std::ostream & operator<<( std::ostream & os, const std::chrono::hh_mm_ss<Duration> & t )
    {
      return os << t.hours     ().count() << ':'
                << t.minutes   ().count() << ':'
                << t.seconds   ().count() << "."
                << t.subseconds().count();
    }
  } // anonymous namespace
#endif










namespace Utilities
{
  template< typename Resolution, typename Clock = std::chrono::high_resolution_clock>
  class TimerType
  {
    public:
      // Note:  Constructing the message parameter object and then moving its contents to the _message attribute happens before the
      //        clock starts and is not included in the timed results.  Unfortunately, the message parameter object's destructor is
      //        called after the clock starts and is included in the time results.
      TimerType( std::string message, std::ostream& stream = std::cout )
        : _message{ std::move(message) }, _stream{ &stream }
      {}


      // Note:  This constructor avoids the overhead of destroying the message parameter
      TimerType( std::ostream & stream = std::cout )
        : _stream{ &stream }
      {}


      ~TimerType() noexcept
      {
        std::chrono::nanoseconds duration = Clock::now() - _start;
        if( !_message.empty() )
        {
          using namespace std::chrono_literals;

          ( *_stream ) << _message;

          if     ( duration < 1us )  ( *_stream ) <<                                                                        (duration).count() << " nanoseconds (ns)\n";
          else if( duration < 1ms )  ( *_stream ) << std::chrono::duration_cast< std::chrono::duration<double, std::micro> >(duration).count() << " microseconds (us)\n";
          else if( duration < 1s  )  ( *_stream ) << std::chrono::duration_cast< std::chrono::duration<double, std::milli> >(duration).count() << " milliseconds (ms)\n";
          else if( duration < 100s)  ( *_stream ) << std::chrono::duration_cast< std::chrono::duration<double            > >(duration).count() << " seconds\n";
          else                       ( *_stream ) << std::chrono::hh_mm_ss<std::chrono::nanoseconds>{duration}                                 << " (hh:mm:ss.ss)\n";
        }
      }

      // Implicit casting operator
      operator typename Resolution::rep() const
      { return std::chrono::duration_cast<Resolution>( Clock::now() - _start ).count(); }


      void reset()
      { _start = Clock::now(); }



    private:
      std::string                _message;
      std::ostream*              _stream   = nullptr;             // storing the stream as a pointer instead of a reference allows
                                                                  // the compiler to synthesize the copy and copy assignment functions.
      typename Clock::time_point _start    = Clock::now();        // physically the last attributes to ensure the clock starts after everything else
  };




  // Let's create a couple default timer types
  using TimerNS  = TimerType< std::chrono::nanoseconds  >;
  using TimerUS  = TimerType< std::chrono::microseconds >;
  using TimerMS  = TimerType< std::chrono::milliseconds >;
  using Timer    = TimerType< std::chrono::seconds      >;
  using TimerMin = TimerType< std::chrono::minutes      >;


}  // namespace Utilities

#endif


/***********************************************************************************************************************************
** (C) Copyright 2021 by Thomas Bettens. All Rights Reserved.
**
** DISCLAIMER: The participating authors at California State University's Computer Science Department have used their best efforts
** in preparing this code. These efforts include the development, research, and testing of the theories and programs to determine
** their effectiveness. The authors make no warranty of any kind, expressed or implied, with regard to these programs or to the
** documentation contained within. The authors shall not be liable in any event for incidental or consequential damages in
** connection with, or arising out of, the furnishing, performance, or use of these libraries and programs.  Distribution without
** written consent from the authors is prohibited.
***********************************************************************************************************************************/

/**************************************************
** Last modified:  23-June-2021  (Added nano seconds, optimized when clock starts and stops)
** Last Verified:  23-June-2021
** Verified with:  MS Visual Studio 2019 Version 16.10.2 (C++20)
**                 GCC version 11.1.1 20210510 (-std=c++20 ),
**                 Clang version 12.0.0 (-std=c++20 -stdlib=libc++)
***************************************************/