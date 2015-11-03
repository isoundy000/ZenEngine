#pragma once
#ifndef __LibFramework_Window_Viewport_PC_h__
#define __LibFramework_Window_Viewport_PC_h__

//! @todo Clean : rename namespace to follow new naming
namespace FWnd
{
	//=================================================================================================
	//! @brief		Window wrapper for each OS
	//! @details	
	//=================================================================================================	
	class Window
	{
	ZENClassDeclareNoParent(Window)
	enum eThreadStatus{keThread_Starting, keThread_Error, keThread_Running, keThread_Ended};
	public:	
								Window(const WCHAR* _zWindowName, zVec2U16 _ClientSize);
		bool					Initialize();
		virtual void			SetSize(const zVec2U16 _vSize){mvSize = _vSize;}
		zVec2U16				GetSize()const {return mvSize;}
		HWND					GetHandle(){return mhMainWindow;}
	protected:		
		static DWORD WINAPI		WndThread( LPVOID lpParam );
		static LRESULT CALLBACK WndEventCallback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		
		std::atomic<zVec2U16>	mvSize;
		WCHAR					mzWindowName[64];
		HWND					mhMainWindow;
		HANDLE					mhMainWindowThread;			//!< Handle on main window thread (process windows messages)
		HINSTANCE				mhWindowInstance;			//!< Handle on main window instance (belongs to main windows thread)
		volatile eThreadStatus	meMainWindowThreadStatus;	//!< Status of the Main window thread (main thread should only read from it)
	};
}
#endif
