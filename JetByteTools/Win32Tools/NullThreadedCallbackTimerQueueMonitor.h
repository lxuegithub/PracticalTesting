#pragma once
#ifndef JETBYTE_TOOLS_WIN32_NULL_THREADED_CALLBACK_TIMER_QUEUE_MONITOR_INCLUDED__
#define JETBYTE_TOOLS_WIN32_NULL_THREADED_CALLBACK_TIMER_QUEUE_MONITOR_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: NullThreadedCallbackTimerQueueMonitor.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2010 JetByte Limited.
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

#include "IMonitorThreadedCallbackTimerQueue.h"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// CNullCallbackTimerQueueMonitor
///////////////////////////////////////////////////////////////////////////////

/// An object that implements IMonitorCallbackTimerQueue and does nothing.
/// \ingroup NullObj
/// \ingroup Monitoring

class CNullThreadedCallbackTimerQueueMonitor : public IMonitorThreadedCallbackTimerQueue
{
   public :

      void OnTimerProcessingContention(
         const ContentionLocation /*location*/) override {}

      void OnTimerProcessingStarted() override {}

      void OnTimerProcessingStopped() override {}

      void OnTimerCreated() override {}

      void OnOneOffTimerSet() override {}

      void OnTimerSet(
         const bool /*wasPending*/) override {}

      void OnTimerUpdated(
         const bool /*wasPending*/,
         const bool /*wasUpdated*/) override {}

      void OnTimer() override {}

      void OnTimerCancelled(
         const bool /*wasPending*/) override {}

      void OnTimerDestroyed(
         const bool /*wasPending*/) override {}

      void OnTimerDeleted() override {}
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_WIN32_NULL_THREADED_CALLBACK_TIMER_QUEUE_MONITOR_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: NullThreadedCallbackTimerQueueMonitor.h
///////////////////////////////////////////////////////////////////////////////
