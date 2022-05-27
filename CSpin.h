#ifndef __CSPIN_H
#define __CSPIN_H

#include <windows.h>
#include <commctrl.h>


class CSpin{
private:
   HWND m_hSpin;
public:
	CSpin(HWND hDlg,int nID){
     m_hSpin=GetDlgItem(hDlg,nID);
	 INITCOMMONCONTROLSEX iccx;
     iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
     iccx.dwICC=ICC_UPDOWN_CLASS;
     InitCommonControlsEx(&iccx);
	}
	CSpin(){
     m_hSpin=NULL;
	 INITCOMMONCONTROLSEX iccx;
     iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
     iccx.dwICC=ICC_UPDOWN_CLASS;
     InitCommonControlsEx(&iccx);
	}
	void SetHWND(HWND hDlg,int nID){
     m_hSpin=GetDlgItem(hDlg,nID);
	}
	HWND GetHWND() const{
     return m_hSpin;
	}
	void SetPos(int nPos){
     SendMessage(m_hSpin,UDM_SETPOS,(WPARAM)0,(LPARAM)MAKELONG (nPos, 0));
	}
	int GetPos(){
      return SendMessage(m_hSpin,UDM_GETPOS,(WPARAM)0,(LPARAM)0);
	}

	int GetRange(){
	   return SendMessage(m_hSpin,UDM_GETRANGE,(WPARAM)0,(LPARAM)0);
	}
	void SetRange(int iMin,int iMax){
      SendMessage(m_hSpin,UDM_SETRANGE,(WPARAM)0,(LPARAM)MAKELONG(iMax,iMin));
	}
	void SetBuddy(HWND hDlg){
     SendMessage(m_hSpin,UDM_SETBUDDY,reinterpret_cast<WPARAM>(hDlg),(LPARAM)0);
	}
	void SetBase(int nBase){
	 SendMessage(m_hSpin,UDM_SETBASE,(WPARAM)nBase,(LPARAM)0);
	}
};



#endif