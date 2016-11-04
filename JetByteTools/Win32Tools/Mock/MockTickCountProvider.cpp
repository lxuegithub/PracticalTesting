///////////////////////////////////////////////////////////////////////////////
// File: MockTickCountProvider.cpp
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

#include "MockTickCountProvider.h"

#include "JetByteTools\Win32Tools\Utils.h"

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -save
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Using directives
///////////////////////////////////////////////////////////////////////////////

using JetByteTools::Win32::ToString;

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {
namespace Mock {

///////////////////////////////////////////////////////////////////////////////
// CMockTickCountProvider
///////////////////////////////////////////////////////////////////////////////

CMockTickCountProvider::CMockTickCountProvider()
   :  m_tickCount(0),
      m_mainThreadId(::GetCurrentThreadId())
{
   m_blockedCallEvent.Reset();
}

CMockTickCountProvider::CMockTickCountProvider(
   const DWORD tickCount)
   :  m_tickCount(tickCount),
      m_mainThreadId(::GetCurrentThreadId())
{
   m_blockedCallEvent.Reset();
}


void CMockTickCountProvider::AllowCalls(
   const size_t numCalls)
{
   m_counter.SetValue(numCalls);
}

bool CMockTickCountProvider::AllowCalls(
   const size_t numCalls,
   const DWORD timeoutMillis)
{
   AllowCalls(numCalls);

   return m_counter.WaitForZero(timeoutMillis);
}

bool CMockTickCountProvider::WaitForBlockedCall(
   const DWORD timeoutMillis)
{
   return m_blockedCallEvent.Wait(timeoutMillis);
}

void CMockTickCountProvider::SetTickCount(
   const DWORD tickCount)
{
   ::InterlockedExchange(reinterpret_cast<volatile long *>(&m_tickCount), tickCount);
}

DWORD CMockTickCountProvider::GetTickCount() const
{
   if (m_mainThreadId != ::GetCurrentThreadId())
   {
      CCriticalSection::Owner lock(m_criticalSection);

      if (0 == m_counter.GetValue())
      {
         m_blockedCallEvent.Set();
      }

      m_counter.WaitForNonZero();

      m_blockedCallEvent.Reset();

      LogMessage(_T("GetTickCount: Another Thread: ") + ToString(m_tickCount));

      m_counter.Decrement();
   }
   else
   {
      LogMessage(_T("GetTickCount: Main Thread: ") + ToString(m_tickCount));
   }
   
   return m_tickCount;
}

///////////////////////////////////////////////////////////////////////////////
// CMockTickCountProvider::AutoRelease
///////////////////////////////////////////////////////////////////////////////

CMockTickCountProvider::AutoRelease::AutoRelease(
   CMockTickCountProvider &timer)
   :  m_timer(timer)
{

}

CMockTickCountProvider::AutoRelease::~AutoRelease()
{
   m_timer.AllowCalls(1000);
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32::Mock
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace JetByteTools 

///////////////////////////////////////////////////////////////////////////////
// Lint options
//
//lint -restore
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// End of file: MockTickCountProvider.cpp
///////////////////////////////////////////////////////////////////////////////
