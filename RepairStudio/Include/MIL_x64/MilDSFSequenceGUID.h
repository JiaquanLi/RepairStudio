/************************************************************************/
/*
*
* Filename     :  MilDSFSequenceGUID.H
* Revision     :  10.00.2734
* Content      :  This file contains the GUIDs relative to the  
*                 Matrox Image Compression Filter.
*
* Comments     :  Some defines may be here but not yet
*                 implemented in the library.
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2014.
* All Rights Reserved
*************************************************************************/

#pragma once

// {B218240E-DC4B-477B-83A7-57611302555D}
DEFINE_GUID(CLSID_MilSequenceEncode, 
            0xb218240e, 0xdc4b, 0x477b, 0x83, 0xa7, 0x57, 0x61, 0x13, 0x2, 0x55, 0x5d);

// {80B8662C-1FD1-438D-BE7B-FA580B30F31C}
DEFINE_GUID(CLSID_MilSequenceDecode, 
            0x80b8662c, 0x1fd1, 0x438d, 0xbe, 0x7b, 0xfa, 0x58, 0xb, 0x30, 0xf3, 0x1c);


// {D83CE998-4E95-42F0-9BE0-9C32A2954C1A}
DEFINE_GUID(IID_IMilSequenceEncode, 
            0xd83ce998, 0x4e95, 0x42f0, 0x9b, 0xe0, 0x9c, 0x32, 0xa2, 0x95, 0x4c, 0x1a);

// {570480A1-1D35-4822-997D-01C683A0C5F3}
DEFINE_GUID(IID_IMilSequenceDecode, 
            0x570480a1, 0x1d35, 0x4822, 0x99, 0x7d, 0x1, 0xc6, 0x83, 0xa0, 0xc5, 0xf3);
