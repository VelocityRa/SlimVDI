/*================================================================================*/
/* Copyright (C) 2009, Don Milne.                                                 */
/* All rights reserved.                                                           */
/* See LICENSE.TXT for conditions on copying, distribution, modification and use. */
/*================================================================================*/

#include "mem.h"

#include "djwarning.h"
#include <stdarg.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// #include <windef.h>
// #include <winbase.h>

/*.....................................................*/

PUBLIC PVOID
Mem_Alloc(UINT flags, UINT size)
{
   HANDLE hMem;
   UINT mflags = 0;
   if (flags & MEMF_ZEROINIT) mflags |= GMEM_ZEROINIT;
   if (flags & MEMF_DDESHARE) mflags |= GMEM_DDESHARE;
   if (!(flags & MEMF_FIXED)) mflags |= GMEM_MOVEABLE;
   hMem = GlobalAlloc(mflags,size);
   if (hMem) return GlobalLock(hMem);
   return NULL;
}

/*.....................................................*/

PUBLIC PVOID
Mem_ReAlloc(PVOID p, UINT flags, UINT size)
{
   if (p) {
      HANDLE hMem = GlobalHandle(p);
      UINT mflags = 0;
      if (flags & MEMF_ZEROINIT) mflags |= GMEM_ZEROINIT;
      if (flags & MEMF_DDESHARE) mflags |= GMEM_DDESHARE;
      GlobalUnlock(hMem);
      hMem = GlobalReAlloc(hMem,size,mflags|GMEM_MOVEABLE);
      if (hMem) return GlobalLock(hMem);
   } else {
      return Mem_Alloc(flags,size);
   }
   return NULL;
}

/*.....................................................*/

PUBLIC PVOID
Mem_Free(PVOID p)
{
   if (p) {
      HANDLE hMem = GlobalHandle(p);
      GlobalUnlock(hMem);
      GlobalFree(hMem);
   }
   return NULL;
}

/*.....................................................*/

PUBLIC void
Mem_Copy(PVOID pDest, CPVOID pSrc, UINT nBytes)
{
   CopyMemory(pDest, pSrc, nBytes);
}

/*.....................................................*/

PUBLIC void
Mem_Move(PVOID pDest, CPVOID pSrc, UINT nBytes)
{
   MoveMemory(pDest, pSrc, nBytes);
}

/*.....................................................*/

PUBLIC void
Mem_Zero(PVOID pDest, UINT nBytes)
{
   ZeroMemory(pDest, nBytes);
}

/*.....................................................*/

PUBLIC void
Mem_Fill(PVOID pDest, UINT nBytes, BYTE FillByte)
{
   FillMemory(pDest, nBytes, FillByte);
}

/*.....................................................*/

PUBLIC int
Mem_Compare(CPVOID pBlock1, CPVOID pBlock2, UINT nBytes)
{
   CPCHAR s1 = (CPCHAR)pBlock1;
   CPCHAR s2 = (CPCHAR)pBlock2;
   int d,c1,c2;
   for (; nBytes; nBytes--) {
      c1 = *s1++;
      c2 = *s2++;
      d = c1-c2;
      if (d!=0) return d;
   }
   return 0;
}

/*.....................................................*/

/* end of mem.c */

