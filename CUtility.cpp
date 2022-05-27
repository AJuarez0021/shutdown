#include "CUtility.h"


HMENU CUtility::SetOfficeMenu(HWND hDlg)
{
    	
  HMENU hMenu=CreateMenu();
  HMENU hPopupMenu=CreateMenu(); 
  IMITEMIMAGE imi;
  AppendMenu(hPopupMenu,MF_STRING,IDMENU_ABOUT,TEXT("Acerca de..")); 
  AppendMenu(hPopupMenu,MF_STRING,IDMENU_CLOSE,TEXT("Cerrar Sesión")); 
  AppendMenu(hPopupMenu,MF_STRING,IDMENU_SHUTDOWN,TEXT("Apagar")); 
  AppendMenu(hPopupMenu,MF_STRING,IDMENU_REBOOT,TEXT("Reiniciar"));   
  AppendMenu(hPopupMenu,MF_STRING,IDMENU_SHOW,TEXT("Mostrar"));
  AppendMenu(hPopupMenu, MF_SEPARATOR, 0,0);
  AppendMenu(hPopupMenu,MF_STRING,IDMENU_EXIT,TEXT("Salir"));
  AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hPopupMenu,TEXT("Menu"));
  ImageMenu_Create(hDlg, hMenu);
  ImageMenu_SetStyle(OFFICE2007);

  imi.mask = IMIMF_LOADFROMRES|IMIMF_ICON;
  imi.hInst = GetModuleHandle(NULL);          
  
  imi.itemID = IDMENU_ABOUT;
  imi.imageStr = MAKEINTRESOURCE(IDI_ICON4);
  ImageMenu_SetItemImage(&imi);

  imi.itemID = IDMENU_EXIT;
  imi.imageStr = MAKEINTRESOURCE(IDI_ICON5);
  ImageMenu_SetItemImage(&imi);

  imi.itemID = IDMENU_CLOSE;
  imi.imageStr = MAKEINTRESOURCE(IDI_ICON3);
  ImageMenu_SetItemImage(&imi);

  imi.itemID = IDMENU_SHUTDOWN;
  imi.imageStr = MAKEINTRESOURCE(IDI_ICON8);
  ImageMenu_SetItemImage(&imi);

  imi.itemID = IDMENU_REBOOT;
  imi.imageStr = MAKEINTRESOURCE(IDI_ICON2);
  ImageMenu_SetItemImage(&imi);
 
  imi.itemID = IDMENU_SHOW;
  imi.imageStr = MAKEINTRESOURCE(IDI_ICON7);
  ImageMenu_SetItemImage(&imi);


  ImageMenu_SetMenuTitleProps(GetSubMenu(hMenu,0), TEXT("Free Shutdown"), TRUE);
  ImageMenu_SetMenuTitleBkProps(GetSubMenu(hMenu,0), RGB(255,237,213), RGB(255,186,94), TRUE, TRUE);
  return hPopupMenu;

}
void CUtility::SetBitmapButton()
{
  ImageButton_EnableXPThemes();
  ImageButton_Create(m_hWnd, IDSHUTDOWN);
  ImageButton_Create(m_hWnd, IDREBOOT);
  ImageButton_Create(m_hWnd, IDCLOSE);
  ImageButton_Create(m_hWnd, IDOK);
  ImageButton_Create(m_hWnd, IDCANCEL);
  ImageButton_Create(m_hWnd, IDABOUT);
  ImageButton_SetIcon(GetDlgItem(m_hWnd, IDSHUTDOWN), IDI_ICON8, 0,0);
  ImageButton_SetIcon(GetDlgItem(m_hWnd, IDREBOOT),   IDI_ICON2, 0,0);
  ImageButton_SetIcon(GetDlgItem(m_hWnd, IDCLOSE),    IDI_ICON3, 0,0);
 

}

BOOL CUtility::LockWorkStation()
{
 HINSTANCE  hLibrary;
 PFNLOCK pfnLock; 
 BOOL bRes=FALSE;
 hLibrary = LoadLibrary (TEXT ("USER32.DLL"));
 if(hLibrary!=NULL){
  pfnLock = (PFNLOCK)GetProcAddress (hLibrary, "LockWorkStation");
  if (NULL != pfnLock)
   bRes=pfnLock();

  FreeLibrary (hLibrary);
 }
 return bRes;
}

bool CUtility::ExitWin32(int iFlag)
{
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx( &osvi );
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT){        
        HANDLE hToken;
        TOKEN_PRIVILEGES tkp;

        if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
            return false;

        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

        if (GetLastError() != ERROR_SUCCESS)
            return false;
    }

   if(iFlag==SHUTDOWN){
	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED))           
      return false; 
   }
   else if(iFlag==REBOOT){
     if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE | SHTDN_REASON_FLAG_PLANNED))           
      return false; 
   }
   else
	 return false;

   return true;
}

void CUtility::Center()
{   
    RECT r;
	GetClientRect(m_hWnd,&r);
	int iWidth		= r.right;
	int iHeight	    = r.bottom;

	RECT ScreenRect;
	GetWindowRect (GetDesktopWindow(), &ScreenRect);
	SetWindowPos (m_hWnd, HWND_TOP, (((ScreenRect.right + ScreenRect.left) / 2) - (iWidth / 2)),
				 (((ScreenRect.bottom + ScreenRect.top) / 2) - (iHeight / 2)),
				  0, 0, SWP_NOCOPYBITS | SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CUtility::SetIconDlg(int nIDIcon)
{   
    HICON hIcon;    
    hIcon=LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(nIDIcon));
    SendMessage(m_hWnd,WM_SETICON,ICON_BIG, (LPARAM) hIcon);
    SendMessage(m_hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);  
}

bool CUtility::SystemShutdown( LPTSTR lpMsg,int iSec,int iFlag)
{
   HANDLE hToken;              
   TOKEN_PRIVILEGES tkp;      
   BOOL fResult;              
 
 
 
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return false; 
 
 
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);  
   tkp.PrivilegeCount = 1;     
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 

 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
 
  
 
   if (GetLastError() != ERROR_SUCCESS) 
      return false; 
 
   
   BOOL bReboot=(iFlag == REBOOT) ? TRUE :  FALSE;
   fResult = InitiateSystemShutdown( 
      NULL,     
      lpMsg,   
      iSec,      
      TRUE,   
      bReboot);   
 
   if (!fResult) 
      return false; 
 
 
   tkp.Privileges[0].Attributes = 0; 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0); 
 
   return true; 
}

