#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef JETBYTE_TOOLS_THREADED_CALLBACK_TIMER_QUEUE_INCLUDED__
#define JETBYTE_TOOLS_THREADED_CALLBACK_TIMER_QUEUE_INCLUDED__
///////////////////////////////////////////////////////////////////////////////
// File: ThreadedCallbackTimerQueue.h
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2004 JetByte Limited.
//
// JetByte Limited grants you ("Licensee") a non-exclusive, royalty free, 
// licence to use, modify and redistribute this software in source and binary 
// code form, provided that i) this copyright notice and licence appear on all 
// copies of the software; and ii) Licensee does not utilize the software in a 
// manner which is disparaging to JetByte Limited.
//
// This software is provided "as is" without a warranty of any kind. All 
// express or implied conditions, representations and warranties, including
// any implied warranty of merchantability, fitness for a particular purpose
// or non-infringement, are hereby excluded. JetByte Limited and its licensors 
// shall not be liable for any damages suffered by licensee as a result of 
// using, modifying or distributing the software or its derivatives. In no
// event will JetByte Limited be liable for any lost revenue, profit or data,
// or for direct, indirect, special, consequential, incidental or punitive
// damages, however caused and regardless of the theory of liability, arising 
// out of the use of or inability to use software, even if JetByte Limited 
// has been advised of the possibility of such damages.
//
// This software is not designed or intended for use in on-line control of 
// aircraft, air traffic, aircraft navigation or aircraft communications; or in 
// the design, construction, operation or maintenance of any nuclear 
// facility. Licensee represents and warrants that it will not use or 
// redistribute the Software for such purposes. 
//
///////////////////////////////////////////////////////////////////////////////

#include "CallbackTimerQueue.h"
#include "Thread.h"
#include "AutoResetEvent.h"
#include "CriticalSection.h"

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// CThreadedCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

class CThreadedCallbackTimerQueue : 
   public IQueueTimers,
   private CThread
{
   public :

      CThreadedCallbackTimerQueue();

      explicit CThreadedCallbackTimerQueue(
         const DWORD maxTimeout);

      explicit CThreadedCallbackTimerQueue(
         const IProvideTickCount &tickProvider);

      CThreadedCallbackTimerQueue(
         const DWORD maxTimeout,
         const IProvideTickCount &tickProvider);

      ~CThreadedCallbackTimerQueue();

      // Implement IQueueTimers

      virtual Handle SetTimer(
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData);

      virtual bool ResetTimer(
         Handle &handle, 
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData);

      virtual bool CancelTimer(
         Handle &handle);

   private :

      DWORD GetNextTimeout();

      void InitiateShutdown();

      void SignalStateChange();

      // Implement CThread

      virtual int Run();

      mutable CCriticalSection m_criticalSection;

      CAutoResetEvent m_stateChangeEvent;

      volatile bool m_shutdown;

      CCallbackTimerQueue m_timerQueue;

      // No copies do not implement
      CThreadedCallbackTimerQueue(const CThreadedCallbackTimerQueue &rhs);
      CThreadedCallbackTimerQueue &operator=(const CThreadedCallbackTimerQueue &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools 

#endif // JETBYTE_TOOLS_THREADED_CALLBACK_TIMER_QUEUE_INCLUDED__

///////////////////////////////////////////////////////////////////////////////
// End of file: ThreadedCallbackTimerQueue.h
///////////////////////////////////////////////////////////////////////////////