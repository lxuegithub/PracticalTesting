#pragma once
#ifndef JETBYTE_TOOLS_WIN32_MOCK_TIMER_QUEUE_INCLUDED__
#define JETBYTE_TOOLS_WIN32_MOCK_TIMER_QUEUE_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: MockTimerQueue.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2007 JetByte Limited.
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

#include "JetByteTools\TestTools\TestLog.h"

#include "JetByteTools\Win32Tools\IManageTimerQueue.h"
#include "JetByteTools\Win32Tools\AutoResetEvent.h"
#include "JetByteTools\Win32Tools\IRunnable.h"
#include "JetByteTools\Win32Tools\Thread.h"
#include "JetByteTools\Win32Tools\ReentrantLockableObject.h"

#include <list>

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {
namespace Mock {

///////////////////////////////////////////////////////////////////////////////
// CMockTimerQueue
///////////////////////////////////////////////////////////////////////////////

/// A mock object that implements IManageTimerQueue.
/// \ingroup Win32ToolsMocks

class CMockTimerQueue :
   public IManageTimerQueue,
   public JetByteTools::Test::CTestLog
{
   public :

      class TimerExpiryThread : private JetByteTools::Win32::IRunnable
      {
         public :

            explicit TimerExpiryThread(
               CMockTimerQueue &timerQueue);

            void WaitForCompletion() const;

            ~TimerExpiryThread();

         private :

            // Implement IRunnable

            unsigned int Run() override;

            JetByteTools::Win32::CThread m_thread;

            CMockTimerQueue &m_timerQueue;

            /// No copies do not implement
            TimerExpiryThread(const TimerExpiryThread &rhs);
            /// No copies do not implement
            TimerExpiryThread &operator=(const TimerExpiryThread &rhs);
      };

      CMockTimerQueue();

      explicit CMockTimerQueue(
         JetByteTools::Test::CTestLog *pLinkedLog);

      bool waitForOnTimerWaitComplete;

      bool includeHandleValuesInLogs;

      void OnTimer();

      bool IsTimerSet() const;

      void SetNextTimeout(
         const Milliseconds nextTimeout);

      bool WaitForNextTimeout(
         const Milliseconds timeout) const;

      bool WaitForOnTimer(
         const Milliseconds timeout);

      // Implement IManageTimerQueue

      Milliseconds GetNextTimeout() override;

      bool BeginTimeoutHandling() override;

      void HandleTimeout() override;

      void EndTimeoutHandling() override;

      // Implement IQueueTimers

      Handle CreateTimer() override;

      bool SetTimer(
         const Handle &handle,
         Timer &timer,
         const Milliseconds timeout,
         const UserData userData) override;

      bool CancelTimer(
         const Handle &handle) override;

      bool DestroyTimer(
         Handle &handle) override;

      bool DestroyTimer(
         const Handle &handle) override;

      void SetTimer(
         Timer &timer,
         const Milliseconds timeout,
         const UserData userData) override;

      Milliseconds GetMaximumTimeout() const override;

   private :

      mutable JetByteTools::Win32::CReentrantLockableObject m_lock;

      CAutoResetEvent m_nextTimeoutEvent;

      CAutoResetEvent m_onTimerEvent;

      CAutoResetEvent m_onTimerWaitCompleteEvent;

      long m_nextTimer;

      struct TimerDetails
      {
         TimerDetails(
            const Handle &handle_,
            Timer &timer_,
            UserData userData_)
            :  handle(handle_),
               timer(timer_),
               userData(userData_)
         {
         }

         const Handle handle;

         Timer &timer;

         UserData userData;
      };

      typedef std::list<TimerDetails> SetTimers;

      SetTimers m_setTimers;

      const Milliseconds m_maxTimeout;

      Milliseconds m_nextTimeout;

      /// No copies do not implement
      CMockTimerQueue(const CMockTimerQueue &rhs);
      /// No copies do not implement
      CMockTimerQueue &operator=(const CMockTimerQueue &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace JetByteTools

#endif // JETBYTE_TOOLS_WIN32_MOCK_TIMER_QUEUE_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: MockTimerQueue.h
///////////////////////////////////////////////////////////////////////////////
