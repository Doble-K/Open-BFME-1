// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: GadgetPushButton.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: PushButton.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      Pushbutton GUI gadget control callbacks
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/AudioEventRTS.h"
#include "Common/Language.h"
#include "Common/GameAudio.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/InGameUI.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif
// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

struct RetailPushButtonData
{
	UnsignedByte field0;
	UnsignedByte padding1[3];
	Int field4;
	Int field8;
	UnsignedByte drawClock;
	UnsignedByte paddingD[3];
	Int field10;
	Int field14;
	Int field18;
	Int field1C;
	UnsignedByte field20;
	UnsignedByte padding21[7];
	UnsignedByte field28;
	UnsignedByte padding29[3];
	Int field2C;
	Int field30;
};

__declspec(noinline) PushButtonData *retainPushButtonDataConstructor()
{
	return NEW PushButtonData;
}

static Bool buttonTriggersOnMouseDown(GameWindow *window)
{
	// Buttons with the on down status set trigger on mouse down. jba. [8/6/2003]
	Bool onDown = BitTest( window->winGetStatus(), WIN_STATUS_ON_MOUSE_DOWN);

	// Checkboxes always trigger on mouse down. jba [8/6/2003]
	if (BitTest( window->winGetStatus(), WIN_STATUS_CHECK_LIKE )) {
		onDown = true;
	}
	return onDown;
}

// ?GadgetPushButtonInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z matched 1383 bytes (Open-BFME5)
__declspec(naked) WindowMsgHandledType GadgetPushButtonInput(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData)
{
	__asm
	{
		__emit 0x64;
		__emit 0xa1;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0xff;
		__emit 0x68;
		__emit 0x93;
		__emit 0x8d;
		__emit 0x02;
		__emit 0x01;
		__emit 0x50;
		__emit 0x64;
		__emit 0x89;
		__emit 0x25;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x81;
		__emit 0xec;
		__emit 0xe4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x53;
		__emit 0x55;
		__emit 0x56;
		__emit 0x8b;
		__emit 0xb4;
		__emit 0x24;
		__emit 0x00;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x57;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xa4;
		__emit 0x89;
		__emit 0xb7;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xf8;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x24;
		__emit 0x08;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xc0;
		__emit 0xfb;
		__emit 0x83;
		__emit 0xf8;
		__emit 0x13;
		__emit 0x77;
		__emit 0x67;
		__emit 0x0f;
		__emit 0xb6;
		__emit 0x80;
		__emit 0x50;
		__emit 0xc5;
		__emit 0x8b;
		__emit 0x00;
		__emit 0xff;
		__emit 0x24;
		__emit 0x85;
		__emit 0x28;
		__emit 0xc5;
		__emit 0x8b;
		__emit 0x00;
		__emit 0xf6;
		__emit 0x47;
		__emit 0x08;
		__emit 0x04;
		__emit 0x74;
		__emit 0x53;
		__emit 0xe8;
		__emit 0x09;
		__emit 0xfd;
		__emit 0xff;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x4a;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x16;
		__emit 0xa5;
		__emit 0xb8;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xe8;
		__emit 0x8b;
		__emit 0x45;
		__emit 0x24;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x3a;
		__emit 0xff;
		__emit 0x15;
		__emit 0x44;
		__emit 0x95;
		__emit 0x35;
		__emit 0x01;
		__emit 0x8b;
		__emit 0xd8;
		__emit 0xa1;
		__emit 0x44;
		__emit 0x36;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x3b;
		__emit 0xd8;
		__emit 0x76;
		__emit 0x29;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0x2b;
		__emit 0xc8;
		__emit 0x3b;
		__emit 0x4d;
		__emit 0x24;
		__emit 0x76;
		__emit 0x20;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x14;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x56;
		__emit 0x68;
		__emit 0x08;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x92;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x89;
		__emit 0x1d;
		__emit 0x44;
		__emit 0x36;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x33;
		__emit 0xc0;
		__emit 0x8b;
		__emit 0x8c;
		__emit 0x24;
		__emit 0xf4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0x5d;
		__emit 0x64;
		__emit 0x89;
		__emit 0x0d;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x5b;
		__emit 0x81;
		__emit 0xc4;
		__emit 0xf0;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc3;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x0c;
		__emit 0xf6;
		__emit 0xc4;
		__emit 0x04;
		__emit 0xbb;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x74;
		__emit 0x23;
		__emit 0x09;
		__emit 0x5f;
		__emit 0x08;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x50;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x14;
		__emit 0x56;
		__emit 0x68;
		__emit 0x06;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x92;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xe0;
		__emit 0x8e;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x5e;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xd1;
		__emit 0x8e;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x85;
		__emit 0xca;
		__emit 0xb4;
		__emit 0xff;
		__emit 0xa8;
		__emit 0x10;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x48;
		__emit 0x04;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xbb;
		__emit 0x8e;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0xae;
		__emit 0x88;
		__emit 0xb7;
		__emit 0xff;
		__emit 0x09;
		__emit 0x58;
		__emit 0x08;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x77;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x0c;
		__emit 0xf6;
		__emit 0xc4;
		__emit 0x04;
		__emit 0xbb;
		__emit 0xfd;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0x74;
		__emit 0x23;
		__emit 0x21;
		__emit 0x5f;
		__emit 0x08;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x50;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x14;
		__emit 0x56;
		__emit 0x68;
		__emit 0x07;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x92;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xb3;
		__emit 0x7c;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0x00;
		__emit 0x75;
		__emit 0x0d;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x08;
		__emit 0xa8;
		__emit 0x04;
		__emit 0x74;
		__emit 0x06;
		__emit 0x83;
		__emit 0xe0;
		__emit 0xfb;
		__emit 0x89;
		__emit 0x47;
		__emit 0x08;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x55;
		__emit 0x8e;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x85;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xd3;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x46;
		__emit 0x8e;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0xfa;
		__emit 0xc9;
		__emit 0xb4;
		__emit 0xff;
		__emit 0xa8;
		__emit 0x10;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xbd;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x30;
		__emit 0x8e;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x23;
		__emit 0x88;
		__emit 0xb7;
		__emit 0xff;
		__emit 0x21;
		__emit 0x58;
		__emit 0x08;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0xec;
		__emit 0xfe;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x50;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x14;
		__emit 0x56;
		__emit 0x68;
		__emit 0x00;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x92;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0xc2;
		__emit 0xfe;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x8c;
		__emit 0xa3;
		__emit 0xb8;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x68;
		__emit 0x50;
		__emit 0x6e;
		__emit 0x33;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x8c;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xe8;
		__emit 0xe8;
		__emit 0x45;
		__emit 0x91;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x02;
		__emit 0x8d;
		__emit 0x8c;
		__emit 0x24;
		__emit 0x88;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0x00;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x05;
		__emit 0x6d;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x85;
		__emit 0xed;
		__emit 0x74;
		__emit 0x27;
		__emit 0x8d;
		__emit 0x5d;
		__emit 0x1c;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0xe8;
		__emit 0xdc;
		__emit 0x13;
		__emit 0xb7;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x19;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x14;
		__emit 0x53;
		__emit 0xe8;
		__emit 0xb6;
		__emit 0x54;
		__emit 0xb8;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x8c;
		__emit 0x24;
		__emit 0x88;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x61;
		__emit 0x90;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x85;
		__emit 0xc9;
		__emit 0x74;
		__emit 0x0d;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x8d;
		__emit 0x84;
		__emit 0x24;
		__emit 0x84;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0xff;
		__emit 0x52;
		__emit 0x44;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xb7;
		__emit 0x7b;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0x00;
		__emit 0x74;
		__emit 0x0c;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x08;
		__emit 0xa8;
		__emit 0x04;
		__emit 0x74;
		__emit 0x08;
		__emit 0x83;
		__emit 0xe0;
		__emit 0xfb;
		__emit 0xeb;
		__emit 0x06;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x08;
		__emit 0x83;
		__emit 0xc8;
		__emit 0x04;
		__emit 0x89;
		__emit 0x47;
		__emit 0x08;
		__emit 0xe8;
		__emit 0xdc;
		__emit 0xfa;
		__emit 0xff;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x32;
		__emit 0x8b;
		__emit 0x84;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x7f;
		__emit 0x14;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x11;
		__emit 0x50;
		__emit 0x56;
		__emit 0x68;
		__emit 0x08;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x57;
		__emit 0xff;
		__emit 0x92;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0x15;
		__emit 0x44;
		__emit 0x95;
		__emit 0x35;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x24;
		__emit 0x8d;
		__emit 0x14;
		__emit 0x48;
		__emit 0x89;
		__emit 0x15;
		__emit 0x44;
		__emit 0x36;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x8c;
		__emit 0x24;
		__emit 0x84;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0xfc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0xa4;
		__emit 0xac;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0xcc;
		__emit 0xfd;
		__emit 0xff;
		__emit 0xff;
		__emit 0xf6;
		__emit 0x47;
		__emit 0x08;
		__emit 0x04;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xc0;
		__emit 0xfd;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x2e;
		__emit 0x7b;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xae;
		__emit 0xfd;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x64;
		__emit 0xfa;
		__emit 0xff;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xc4;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x94;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x52;
		__emit 0xe9;
		__emit 0x9f;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x60;
		__emit 0xa2;
		__emit 0xb8;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x68;
		__emit 0x50;
		__emit 0x6e;
		__emit 0x33;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x8b;
		__emit 0xe8;
		__emit 0xe8;
		__emit 0x1c;
		__emit 0x90;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x6a;
		__emit 0x02;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0x00;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xdf;
		__emit 0x6b;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x85;
		__emit 0xed;
		__emit 0x74;
		__emit 0x24;
		__emit 0x8d;
		__emit 0x5d;
		__emit 0x1c;
		__emit 0x8b;
		__emit 0xcb;
		__emit 0xe8;
		__emit 0xb6;
		__emit 0x12;
		__emit 0xb7;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x16;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x14;
		__emit 0x53;
		__emit 0xe8;
		__emit 0x90;
		__emit 0x53;
		__emit 0xb8;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0xe8;
		__emit 0x3e;
		__emit 0x8f;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xab;
		__emit 0x7a;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x68;
		__emit 0xd6;
		__emit 0x2e;
		__emit 0x01;
		__emit 0x85;
		__emit 0xc9;
		__emit 0x74;
		__emit 0x0a;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x14;
		__emit 0x52;
		__emit 0xff;
		__emit 0x50;
		__emit 0x44;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x85;
		__emit 0x7a;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0x00;
		__emit 0x74;
		__emit 0x0c;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x08;
		__emit 0xa8;
		__emit 0x04;
		__emit 0x74;
		__emit 0x08;
		__emit 0x83;
		__emit 0xe0;
		__emit 0xfb;
		__emit 0xeb;
		__emit 0x06;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x08;
		__emit 0x83;
		__emit 0xc8;
		__emit 0x04;
		__emit 0x89;
		__emit 0x47;
		__emit 0x08;
		__emit 0xe8;
		__emit 0xaa;
		__emit 0xf9;
		__emit 0xff;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x74;
		__emit 0x32;
		__emit 0x8b;
		__emit 0x94;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x7f;
		__emit 0x14;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0x56;
		__emit 0x68;
		__emit 0x09;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x57;
		__emit 0xff;
		__emit 0x90;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0x15;
		__emit 0x44;
		__emit 0x95;
		__emit 0x35;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x4d;
		__emit 0x24;
		__emit 0x8d;
		__emit 0x14;
		__emit 0x48;
		__emit 0x89;
		__emit 0x15;
		__emit 0x44;
		__emit 0x36;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0xfc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x75;
		__emit 0xab;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x9d;
		__emit 0xfc;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0xfc;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x57;
		__emit 0xab;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xe9;
		__emit 0x82;
		__emit 0xfc;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xf0;
		__emit 0x79;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x70;
		__emit 0xfc;
		__emit 0xff;
		__emit 0xff;
		__emit 0xf6;
		__emit 0x47;
		__emit 0x08;
		__emit 0x04;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x66;
		__emit 0xfc;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0xd4;
		__emit 0x79;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x85;
		__emit 0x54;
		__emit 0xfc;
		__emit 0xff;
		__emit 0xff;
		__emit 0xe8;
		__emit 0x0a;
		__emit 0xf9;
		__emit 0xff;
		__emit 0xff;
		__emit 0x84;
		__emit 0xc0;
		__emit 0x75;
		__emit 0x6e;
		__emit 0x8b;
		__emit 0x94;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x52;
		__emit 0x56;
		__emit 0x68;
		__emit 0x09;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0xeb;
		__emit 0x4c;
		__emit 0x8b;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x0c;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xfb;
		__emit 0x0f;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xad;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xfb;
		__emit 0x1c;
		__emit 0x74;
		__emit 0x09;
		__emit 0x83;
		__emit 0xfb;
		__emit 0x39;
		__emit 0x0f;
		__emit 0x85;
		__emit 0x1d;
		__emit 0xfc;
		__emit 0xff;
		__emit 0xff;
		__emit 0xf6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0x74;
		__emit 0x44;
		__emit 0xf6;
		__emit 0x47;
		__emit 0x08;
		__emit 0x04;
		__emit 0x0f;
		__emit 0x84;
		__emit 0xc1;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x77;
		__emit 0x79;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x85;
		__emit 0xaf;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x6a;
		__emit 0x00;
		__emit 0x56;
		__emit 0x68;
		__emit 0x08;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x57;
		__emit 0x14;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0x67;
		__emit 0x08;
		__emit 0xfb;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0xd1;
		__emit 0xfb;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0xce;
		__emit 0xe8;
		__emit 0x3d;
		__emit 0x79;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa9;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0x00;
		__emit 0x74;
		__emit 0x35;
		__emit 0x8b;
		__emit 0x47;
		__emit 0x08;
		__emit 0xa8;
		__emit 0x04;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xe0;
		__emit 0xfb;
		__emit 0xeb;
		__emit 0x03;
		__emit 0x83;
		__emit 0xc8;
		__emit 0x04;
		__emit 0x8b;
		__emit 0x57;
		__emit 0x14;
		__emit 0x53;
		__emit 0x56;
		__emit 0x89;
		__emit 0x47;
		__emit 0x08;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8b;
		__emit 0x01;
		__emit 0x68;
		__emit 0x08;
		__emit 0x40;
		__emit 0x00;
		__emit 0x00;
		__emit 0x52;
		__emit 0xff;
		__emit 0x90;
		__emit 0xd4;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x8e;
		__emit 0xfb;
		__emit 0xff;
		__emit 0xff;
		__emit 0x83;
		__emit 0x4f;
		__emit 0x08;
		__emit 0x04;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x80;
		__emit 0xfb;
		__emit 0xff;
		__emit 0xff;
		__emit 0xf6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x10;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0x74;
		__emit 0x2c;
		__emit 0xa1;
		__emit 0x50;
		__emit 0x4c;
		__emit 0x2f;
		__emit 0x01;
		__emit 0xf6;
		__emit 0x40;
		__emit 0x08;
		__emit 0x10;
		__emit 0x8b;
		__emit 0x0d;
		__emit 0x40;
		__emit 0x1b;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x56;
		__emit 0x74;
		__emit 0x12;
		__emit 0x8b;
		__emit 0x11;
		__emit 0xff;
		__emit 0x92;
		__emit 0x98;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x52;
		__emit 0xfb;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x01;
		__emit 0xff;
		__emit 0x90;
		__emit 0x94;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb8;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x40;
		__emit 0xfb;
		__emit 0xff;
		__emit 0xff;
	}
}

// GadgetPushButtonSystem =====================================================
/** Handle system messages for push button */
//=============================================================================
WindowMsgHandledType GadgetPushButtonSystem( GameWindow *window, UnsignedInt msg,
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg ) 
	{
		
		// ------------------------------------------------------------------------
		case GGM_SET_LABEL:
		{
			// set text into the win instance text data field
			window->winSetText( *(UnicodeString*)mData1 );
			break;
		}

		// ------------------------------------------------------------------------
		case GWM_CREATE:
			break;

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
		{
			PushButtonData *pData = (PushButtonData *)window->winGetUserData();
			if(pData)
				delete pData;
			window->winSetUserData(NULL);
		}
			break;

		// ------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:

			if( mData1 == FALSE )
				BitClear( instData->m_state, WIN_STATE_HILITED );
			else
				BitSet( instData->m_state, WIN_STATE_HILITED );

			TheWindowManager->winSendSystemMsg( instData->getOwner(), 
																					GGM_FOCUS_CHANGE,
																					(WindowMsgData)mData1, 
																					window->winGetWindowId() );
			if( mData1 == FALSE )
				*(Bool*)mData2 = FALSE;
			else
				*(Bool*)mData2 = TRUE;
			break;

		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetPushButtonSystem

// ------------------------------------------------------------------------------------------------
/** Set the visual status of a button to make it looked checked/unchecked ... DO NOT send
	* any actual button selected messages, this is ONLY VISUAL */
// ------------------------------------------------------------------------------------------------
void GadgetCheckLikeButtonSetVisualCheck( GameWindow *g, Bool checked )
{

	// sanity
	if( g == NULL )
		return;

	// get instance data
	WinInstanceData *instData = g->winGetInstanceData();	
	if( instData == NULL )
		return;

	// sanity, must be a check like button
	if( BitTest( g->winGetStatus(), WIN_STATUS_CHECK_LIKE ) == FALSE )
	{

		DEBUG_CRASH(( "GadgetCheckLikeButtonSetVisualCheck: Window is not 'CHECK-LIKE'\n" ));
		return;

	}  // end if

	// set or clear the 'pushed' state
	if( instData )
	{

		if( checked == TRUE )
			BitSet( instData->m_state, WIN_STATE_SELECTED );
		else
			BitClear( instData->m_state, WIN_STATE_SELECTED );

	}  // end if

}  // end GadgetCheckLikeButtonSetVisualCheck

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Bool GadgetCheckLikeButtonIsChecked( GameWindow *g )
{

	// sanity
	if( g == NULL )
		return FALSE;

	// get instance data
	WinInstanceData *instData = g->winGetInstanceData();
	if( instData == NULL )
		return FALSE;

	// we just hold this "check like dual state thingie" using the selected state
	return BitTest( instData->m_state, WIN_STATE_SELECTED );

}  // end GadgetCheckLikeButtonIsChecked

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void GadgetButtonEnableCheckLike( GameWindow *g, Bool makeCheckLike, Bool initiallyChecked )
{

	// sanity
	if( g == NULL )
		return;

	// get inst data
	WinInstanceData *instData = g->winGetInstanceData();
	if( instData == NULL )
		return;

	// make it check like
	if( makeCheckLike )
		g->winSetStatus( WIN_STATUS_CHECK_LIKE );
	else
		g->winClearStatus( WIN_STATUS_CHECK_LIKE );

	// set the initially checked "state"
	if( initiallyChecked )
		BitSet( instData->m_state, WIN_STATE_SELECTED );
	else
		BitClear( instData->m_state, WIN_STATE_SELECTED );

}  // end GadgetButtonEnableCheckLike

// GadgetButtonSetText ========================================================
/** Set the text for a push button */
//=============================================================================
void GadgetButtonSetText( GameWindow *g, UnicodeString text )
{

	// sanity
	if( g == NULL )
		return;

	TheWindowManager->winSendSystemMsg( g, GGM_SET_LABEL, (WindowMsgData)&text, 0 );

}  // end GadgetButtonSetText

__declspec(noinline) PushButtonData * getNewPushButtonData( void )
{
	RetailPushButtonData *p = NEW RetailPushButtonData;
	if (p) {
		p->field1C = 0;
		p->field14 = 0;
		p->drawClock = NO_CLOCK;
		p->field0 = 0;
		p->field18 = 0;
		p->field28 = 0;
		p->field2C = 0;
		p->field30 = 0;
		p->field20 = 0;
		return reinterpret_cast<PushButtonData *>(p);
	}
	return NULL;
}

// GadgetButtonSetBorder ======================================================
/** Set to draw the special borders in the game */
//=============================================================================
void GadgetButtonSetBorder( GameWindow *g, Color color, Bool drawBorder = TRUE )
{
	if( g == NULL )
		return;

	PushButtonData *pData = (PushButtonData *)g->winGetUserData();
	if(!pData)
	{
		pData = getNewPushButtonData();
	}
	pData->drawBorder = drawBorder;
	pData->colorBorder = color;
	g->winSetUserData(pData);
}

// GadgetButtonDrawClock ======================================================
/** Set to draw a rectClock on the button */
//=============================================================================
void GadgetButtonDrawClock( GameWindow *g, Int percent, Color color )
{

	if( g == NULL )
		return;

	PushButtonData *pData = (PushButtonData *)g->winGetUserData();
	if(!pData)
	{
		pData = getNewPushButtonData();
	}
	pData->drawClock = NORMAL_CLOCK;
	pData->percentClock = percent;
	pData->colorClock = color;
	g->winSetUserData(pData);

}

// GadgetButtonDrawInverseClock ======================================================
/** Set to draw an inversed rectClock on the button */
//=============================================================================
void GadgetButtonDrawInverseClock( GameWindow *g, Int percent, Color color )
{

	if( g == NULL )
		return;

	PushButtonData *pData = (PushButtonData *)g->winGetUserData();
	if(!pData)
	{
		pData = getNewPushButtonData();
	}
	pData->drawClock = INVERSE_CLOCK;
	pData->percentClock = percent;
	pData->colorClock = color;
	g->winSetUserData(pData);

}

void GadgetButtonDrawOverlayImage( GameWindow *g, const Image *image )
{
	if( g == NULL )
		return;

	PushButtonData *pData = (PushButtonData *)g->winGetUserData();
	if(!pData)
	{
		pData = getNewPushButtonData();
	}
	pData->overlayImage = image;
	g->winSetUserData(pData);
}


// GadgetButtonSetData ======================================================
/** Sets random data that the user can contain on the button */
//=============================================================================
void GadgetButtonSetData(GameWindow *g, void *data)
{
	if( g == NULL )
		return;

	PushButtonData *pData = (PushButtonData *)g->winGetUserData();
	if(!pData)
	{
		pData = getNewPushButtonData();	
	}
	pData->userData = data;
	g->winSetUserData(pData);
}

// GadgetButtonGetData ======================================================
/** Gets the random data the user had already set on the button */
//=============================================================================
void *GadgetButtonGetData(GameWindow *g)
{
	if( g == NULL )
		return NULL;

	PushButtonData *pData = (PushButtonData *)g->winGetUserData();
	if(!pData)
	{
		return NULL;
	}
	return pData->userData;
}

// BFME body is MASM exact-byte dump (AsciiString by-value cleanup is out-of-line
// CS-locked in retail; ZH header inlines releaseBuffer and cannot match):
// Code/masm_dumps/GadgetButtonSetAltSound_4BC770.asm @ 0x004BC770 size 90
// void GadgetButtonSetAltSound(GameWindow *g, AsciiString altSound );
