#ifndef __CUTILITY_H
#define __CUTILITY_H

#include "CTimer.h"
#include "resource.h"
#include "ImageButton.h"
#include "ImageMenu.h"

#ifndef SHTDN_REASON_MAJOR_OPERATINGSYSTEM 
#define SHTDN_REASON_MAJOR_OPERATINGSYSTEM 0x00020000
#endif

#ifndef SHTDN_REASON_FLAG_PLANNED
#define SHTDN_REASON_FLAG_PLANNED 0x80000000
#endif

#ifndef SHTDN_REASON_MINOR_UPGRADE  
#define SHTDN_REASON_MINOR_UPGRADE 0x00000003
#endif

#define SHUTDOWN  0
#define REBOOT    1

#define IDMENU_ABOUT    10
#define IDMENU_SHOW     11
#define IDMENU_STOP     13
#define IDMENU_CLOSE    14
#define IDMENU_SHUTDOWN 15
#define IDMENU_REBOOT   16
#define IDMENU_EXIT     12

typedef BOOL (WINAPI * PFNLOCK) (void);

class CUtility : public CWnd{
public:
	void Center();
	void SetIconDlg(int nIDIcon);
    bool ExitWin32(int iFlag);
    BOOL LockWorkStation();
	bool SystemShutdown( LPTSTR lpMsg,int iSec,int iFlag);	
	void SetBitmapButton();
	HMENU SetOfficeMenu(HWND hDlg);
};

#endif