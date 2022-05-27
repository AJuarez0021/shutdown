#ifndef __CTRAYICON_H
#define __CTRAYICON_H

#include <windows.h>

#define WM_NOTIFYICONTRAY (WM_APP + 1)

class CTrayIcon{
private:
  HICON hIcon;
public:
    void Destroy_Icon(HWND hWnd);
	void ShowIcon(HWND hWnd);
	BOOL SetIcon(HWND hWnd,LPCSTR strTip,UINT nIDIcon);
	void Hide(HWND hWnd){
     ShowWindow(hWnd, SW_HIDE);
	}  
	void ShowMenu(HMENU hPopupMenu,HWND hWnd,POINT p){
       SetForegroundWindow(hWnd);
       TrackPopupMenuEx(hPopupMenu, TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_VERTICAL, p.x,p.y, hWnd, NULL); 
	}
	BOOL SetToolTip(HWND hWnd,LPCSTR strTip);
};

#endif