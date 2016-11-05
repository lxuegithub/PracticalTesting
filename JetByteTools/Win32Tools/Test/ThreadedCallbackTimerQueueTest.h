#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef JETBYTE_TOOLS_WIN32_TEST_THREADED_CALLBACK_TIMER_QUEUE_TEST_INCLUDED__
#define JETBYTE_TOOLS_WIN32_TEST_THREADED_CALLBACK_TIMER_QUEUE_TEST_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: ThreadedCallbackTimerQueueTest.h 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2004 JetByte Limited.
//
// This software is provided "as is" without a warranty of any kind. All 
// express or implied conditions, representations and warranties, including
// any implied warranty of merchantability, fitness for a particular purpose
// or non-infringement, are hereby excluded. JetByte Limited and its licensors 
// shall not be liable for any damages suffered by licensee as a result of 
// using the software. In no event will JetByte Limited be liable for any 
// lost revenue, profit or data, or for direct, indirect, special, 
// consequential, incidental or punitive damages, however caused and regardless 
// of the theory of liability, arising out of the use of or inability to use 
// software, even if JetByte Limited has been advised of the possibility of 
// such damages.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools 
{
   namespace Test
   {
      class CTestMonitor;
   }
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Test
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {
namespace Test {

///////////////////////////////////////////////////////////////////////////////
// CThreadedCallbackTimerQueueTest
///////////////////////////////////////////////////////////////////////////////

/// \test
/// \ingroup Win32ToolsTests

class CThreadedCallbackTimerQueueTest
{
   public :

      static void TestAll(
         JetByteTools::Test::CTestMonitor &monitor);

      static void TestConstructBestForPlatform();
      static void TestConstructTickCount64();
      static void TestConstructHybridTickCount64();
      static void TestConstructCustomQueue();
      static void TestConstructWithTimerWheel();

      static void TestBeginShutdown();
      static void TestWaitForShutdownToComplete();

      static void TestTimer();
      static void TestTimerWithLock();
      static void TestTimerNoLock();
      static void TestTimerTickCount64();
      static void TestTimerTickCount64NoLock();
      static void TestTimerHybridTickCount64();
      static void TestTimerHybridTickCount64NoLock();
      static void TestTimerTimerWheel();
      static void TestTimerTimerWheelNoLock();

      static void TestMultipleTimersTickCount64();
      static void TestMultipleTimersTickCount64NoLock();
      static void TestMultipleTimersHybridTickCount64();
      static void TestMultipleTimersHybridTickCount64NoLock();
      static void TestMultipleTimersTimerWheel();
      static void TestMultipleTimersTimerWheelNoLock();
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Test
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Test
} // End of namespace Win32
} // End of namespace JetByteTools 

#endif // JETBYTE_TOOLS_WIN32_TEST_THREADED_CALLBACK_TIMER_QUEUE_TEST_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: ThreadedCallbackTimerQueueTest.h
///////////////////////////////////////////////////////////////////////////////
