#pragma once
#ifndef JETBYTE_TOOLS_WIN32_LOGGING_CALLBACK_TIMER_INCLUDED__
#define JETBYTE_TOOLS_WIN32_LOGGING_CALLBACK_TIMER_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: LoggingCallbackTimer.h
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

#include "JetByteTools/TestTools/TestLog.h"

#include "JetByteTools/Win32Tools/IQueueTimers.h"
#include "JetByteTools/Win32Tools/AutoResetEvent.h"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {
namespace Mock {

///////////////////////////////////////////////////////////////////////////////
// CLoggingCallbackTimer
///////////////////////////////////////////////////////////////////////////////

/// A mock object that implements IQueueTimers::Timer so that it can be
/// used as a timer for testing implementations of IQueueTimers.
/// \ingroup Win32ToolsMocks

class CLoggingCallbackTimer :
   public IQueueTimers::Timer,
   public JetByteTools::Test::CTestLog
{
   public :

      CLoggingCallbackTimer();

      explicit CLoggingCallbackTimer(
         CTestLog &linkedLog);

      CLoggingCallbackTimer(
         const CLoggingCallbackTimer &rhs) = delete;

      CLoggingCallbackTimer &operator=(
         const CLoggingCallbackTimer &rhs) = delete;

      bool logMessage;

      bool logUserData;

      void DestroyTimerInOnTimer(
         IQueueTimers &timerQueue,
         IQueueTimers::Handle &handle);

      void SetTimerInOnTimer(
         IQueueTimers &timerQueue,
         IQueueTimers::Handle &handle,
         Milliseconds timeout,
         UserData userData /* = 0*/);

      bool WaitForTimer(
         Milliseconds timeout) const;

      unsigned long GetNumTimerEvents() const;

      // Implement IQueueTimers::Timer

      void OnTimer(
         UserData userData) override;

   private :

      CAutoResetEvent m_timerEvent;

      volatile long m_numTimerEvents;

      IQueueTimers *m_pTimerQueue;

      IQueueTimers::Handle m_handle;

      Milliseconds m_timeout;

      UserData m_userData;
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_WIN32_LOGGING_CALLBACK_TIMER_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: LoggingCallbackTimer.h
///////////////////////////////////////////////////////////////////////////////
