///////////////////////////////////////////////////////////////////////////////
// File: ICriticalSection.cpp
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

#include "JetByteTools/Admin/Admin.h"

#include "ICriticalSection.h"

#include "Exception.h"
#include "DebugTrace.h"

#pragma hdrstop

#if (JETBYTE_DEPRECATE_CRITICAL_SECTION == 0)

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {
namespace Win32 {

///////////////////////////////////////////////////////////////////////////////
// ICriticalSection
///////////////////////////////////////////////////////////////////////////////

void ICriticalSection::EnsureLockedByThisThread(
   const ICriticalSection &crit)
{
   if (!crit.IsLockedByThisThread())
   {
      OutputEx(_T("Thread should hold lock and does not!"));

      if (IsDebuggerPresent())
      {
         DebugBreak();
      }

      throw CException(
         _T("ICriticalSection::EnsureLockedByThisThread()"),
         _T("Thread should hold lock and does not!"));
   }
}

void ICriticalSection::EnsureIsNotLockedByThisThread(
   const ICriticalSection &crit)
{
   if (crit.IsLockedByThisThread())
   {
      OutputEx(_T("Thread should hold NOT lock and does!"));

      if (IsDebuggerPresent())
      {
         DebugBreak();
      }

      throw CException(
         _T("ICriticalSection::EnsureIsNotLockedByThisThread()"),
         _T("Thread should NOT hold lock and does!"));
   }
}

///////////////////////////////////////////////////////////////////////////////
// ICriticalSection::Owner
///////////////////////////////////////////////////////////////////////////////

ICriticalSection::Owner::Owner(
   ICriticalSection &crit)
   : m_crit(crit)
{
   m_crit.Enter();
}

ICriticalSection::Owner::~Owner()
{
   try
   {
      m_crit.Leave();
   }
   JETBYTE_CATCH_AND_LOG_ALL_IN_DESTRUCTORS_IF_ENABLED
}

///////////////////////////////////////////////////////////////////////////////
// ICriticalSection::ConditionalOwner
///////////////////////////////////////////////////////////////////////////////

ICriticalSection::ConditionalOwner::ConditionalOwner(
   ICriticalSection &crit,
   const bool locked)
   :  m_crit(crit),
      m_locked(locked)
{
   if (m_locked)
   {
      m_crit.Enter();
   }
}

ICriticalSection::ConditionalOwner::~ConditionalOwner()
{
   try
   {
      if (m_locked)
      {
         m_crit.Leave();
      }
   }
   JETBYTE_CATCH_AND_LOG_ALL_IN_DESTRUCTORS_IF_ENABLED
}

void ICriticalSection::ConditionalOwner::Leave()
{
   if (m_locked)
   {
      m_locked = false;

      m_crit.Leave();
   }
}

///////////////////////////////////////////////////////////////////////////////
// ICriticalSection::PotentialOwner
///////////////////////////////////////////////////////////////////////////////

ICriticalSection::PotentialOwner::PotentialOwner(
   ICriticalSection &crit)
   :  m_crit(crit),
      m_locked(false)
{
}

ICriticalSection::PotentialOwner::~PotentialOwner()
{
   try
   {
      if (m_locked)
      {
         m_crit.Leave();
      }
   }
   JETBYTE_CATCH_AND_LOG_ALL_IN_DESTRUCTORS_IF_ENABLED
}

void ICriticalSection::PotentialOwner::Enter()
{
   if (m_locked)
   {
      throw CException(_T("ICriticalSection::PotentialOwner::Enter()"), _T("Already locked"));
   }

   m_locked = true;

   m_crit.Enter();
}

bool ICriticalSection::PotentialOwner::TryEnter()
{
   if (m_locked)
   {
      throw CException(_T("ICriticalSection::PotentialOwner::TryEnter()"), _T("Already locked"));
   }

   m_locked = m_crit.TryEnter();

   return m_locked;
}

void ICriticalSection::PotentialOwner::Leave()
{
   if (m_locked)
   {
      m_locked = false;

      m_crit.Leave();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools::Win32
///////////////////////////////////////////////////////////////////////////////

} // End of namespace Win32
} // End of namespace JetByteTools

#else
SuppressLNK4221Warning()
#endif // JETBYTE_DEPRECATE_CRITICAL_SECTION

///////////////////////////////////////////////////////////////////////////////
// End of file: ICriticalSection.cpp
///////////////////////////////////////////////////////////////////////////////
