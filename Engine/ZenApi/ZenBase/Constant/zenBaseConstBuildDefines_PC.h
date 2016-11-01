#pragma once
#ifndef __zenApi_Base_Constant_BuildDefines_PC_h__
#define __zenApi_Base_Constant_BuildDefines_PC_h__

#ifdef _WINDOWS
//#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <WinSock2.h>
#include <windows.h>
#include <Shellapi.h>
#endif

#define	ZEN_EXPORT_OR_RESOURCE_PC	ZEN_PLATFORM_PC
#define	ZEN_EXPORT_PC				ZEN_BUILD_PC_GAMEORTOOL

#define zenInline					__inline
#define zenForceDebugInline			__forceinline
#if !ZEN_BUILD_DEBUG
	#define zenForceInline			__forceinline
#else
	#define zenForceInline			zenInline
#endif

#define zenPreventEmptyFileWarning	namespace { char sbPreventsWarning4221; };	//Prevent warning 4221(no public symbols) that can't be ignored.

#endif
