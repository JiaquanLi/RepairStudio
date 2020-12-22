/************************************************************************/
/*
*
* Filename     :  MilDSFSequence.H
* Revision     :  10.00.2734
* Content      :  This file contains the interface structure required for 
*                 Matrox Image Compression Filter.
*
* Comments     :  Some defines may be here but not yet
*                 implemented in the library.
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2014.
* All Rights Reserved
*************************************************************************/

#pragma once
#pragma warning(disable:4995)

#include <initguid.h>
#include "MilDSFSequenceGUID.h"

#include <mil.h>

/////////////////////////////////////////////////////////////////
//
// Interface         : IMilSequenceEncode
//
// Synopsis          : Access the encoding context
//
// Comments          : Control and Inquire functions are equivalent to
//                     MseqControl and MseqInquire except you do not have to
//                     specify a MIL_ID for the sequence context.
//
/////////////////////////////////////////////////////////////////
DECLARE_INTERFACE_(IMilSequenceEncode, IBaseFilter)
   {
   STDMETHOD_(void, Control)
      ( THIS_
      MIL_INT64 ControlType,
      MIL_DOUBLE ControlValue
      )  PURE;

   STDMETHOD_(void, Control)
      ( THIS_
      MIL_INT64 ControlType,
      MIL_INT32 ControlValue
      )  PURE;

   STDMETHOD_(void, Control)
      ( THIS_
      MIL_INT64 ControlType,
      MIL_INT64 ControlValue
      )  PURE;

   STDMETHOD_(MIL_INT, Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_DOUBLE* UserVarPtr
      )  PURE;

   STDMETHOD_(MIL_INT, Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_INT32* UserVarPtr
      )  PURE;

   STDMETHOD_(MIL_INT, Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_INT64* UserVarPtr
      )  PURE;

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
   STDMETHOD_(MIL_INT, Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_UINT32* UserVarPtr
      )  PURE;

   STDMETHOD_(MIL_INT, Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_UINT64* UserVarPtr
      )  PURE;
#endif // M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED

   STDMETHOD (InitParam)
      ( THIS_
      MIL_UINT32 OutputFormat,
      MIL_INT64 InitFlag
      )  PURE;

   STDMETHOD(GetInitFlag)
      ( THIS_
      MIL_INT64* pInitFlag
      )  PURE;
   };


DECLARE_INTERFACE_(IMilSequenceDecode, IBaseFilter)
   {
   STDMETHOD(Control)
      ( THIS_
      MIL_INT64 ControlType,
      MIL_DOUBLE ControlValue
      )  PURE;

   STDMETHOD(Control)
      ( THIS_
      MIL_INT64 ControlType,
      MIL_INT32 ControlValue
      )  PURE;

   STDMETHOD(Control)
      ( THIS_
      MIL_INT64 ControlType,
      MIL_INT64 ControlValue
      )  PURE;

   STDMETHOD(Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_DOUBLE* UserVarPtr
      )  PURE;

   STDMETHOD(Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_INT32* UserVarPtr
      )  PURE;

   STDMETHOD(Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_INT64* UserVarPtr
      )  PURE;

#if M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED
   STDMETHOD(Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_UINT32* UserVarPtr
      )  PURE;

   STDMETHOD(Inquire)
      ( THIS_
      MIL_INT64 InquireType,
      MIL_UINT64* UserVarPtr
      )  PURE;
#endif // M_MIL_SAFE_TYPE_SUPPORTS_UNSIGNED

   STDMETHOD (InitParam)
      ( THIS_
      MIL_UINT32 OutputFormat,
      MIL_INT64 InitFlag
      )  PURE;

   STDMETHOD(GetInitFlag)
      (THIS_
      MIL_INT64* pInitFlag
      )  PURE;
   };
