#include "CTrayIcon.h"


void CTrayIcon::ShowIcon(HWND hWnd)
{
 ShowWindow(hWnd,SW_RESTORE);
 UpdateWindow(hWnd);
}

BOOL CTrayIcon::SetToolTip(HWND hWnd,LPCSTR strTip)
{
 NOTIFYICONDATA tnid;
 tnid.cbSize = sizeof(NOTIFYICONDATA); 
 tnid.hWnd = hWnd; 
 tnid.uID = 0;
 tnid.uFlags = NIF_TIP ;
 lstrcpyn(tnid.szTip,strTip,strlen(strTip)+1); 
 return Shell_NotifyIcon(NIM_MODIFY, &tnid);

}
BOOL CTrayIcon::SetIcon(HWND hWnd,LPCSTR strTip,UINT nIDIcon)
{
 NOTIFYICONDATA tnid;
 tnid.cbSize = sizeof(NOTIFYICONDATA); 
 tnid.hWnd = hWnd; 
 tnid.uID = 0;
 tnid.uFlags = NIF_MESSAGE | NIF_TIP | NIF_ICON; 
 tnid.uCallbackMessage = WM_NOTIFYICONTRAY; 
 tnid.hIcon = LoadIcon (reinterpret_cast<HINSTANCE>(GetWindowLong( hWnd, GWL_HINSTANCE )), MAKEINTRESOURCE(nIDIcon)); 
 lstrcpyn(tnid.szTip,strTip,strlen(strTip)+1); 
 return Shell_NotifyIcon(NIM_ADD, &tnid);
}

void CTrayIcon::Destroy_Icon(HWND hWnd)
{
 NOTIFYICONDATA tnid;
 tnid.cbSize = sizeof(NOTIFYICONDATA); 
 tnid.hWnd = hWnd; 
 tnid.uID = 0; 
 Shell_NotifyIcon(NIM_DELETE, &tnid);
 DestroyIcon(hIcon);
}
