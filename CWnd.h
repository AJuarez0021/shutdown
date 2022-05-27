#include <windows.h>
#include <commctrl.h>
#include <string>
class CWnd{
protected:
    HWND m_hWnd;
public:
	CWnd(HWND hWnd=NULL){
      m_hWnd=hWnd;
	  InitCommonControls();	
	}
	void SetHWND(HWND hWnd){
      m_hWnd=hWnd;
	}
	HWND GetHWND() const{
      return m_hWnd;
	}
	HINSTANCE GetInstance() const{
      return (HINSTANCE) GetWindowLong(m_hWnd, GWL_HINSTANCE );
	}
	void ShowError(LPCSTR strText){
     MessageBox(m_hWnd,strText,"Free Shutdown",MB_ICONERROR);
	}
	void ShowInformation(LPCSTR strText){
     MessageBox(m_hWnd,strText,"Free Shutdown",MB_ICONINFORMATION);
	}
	int ShowQuestion(LPCSTR strText){
      return MessageBox(m_hWnd,strText,"Free Shutdown",MB_YESNO|MB_ICONQUESTION);
	}
	void SetText(int nID,LPCSTR strText){
     SetDlgItemText(m_hWnd,nID,strText);
	}
	std::string GetOS();
	bool CheckButton(int nID){
     if(SendDlgItemMessage(m_hWnd,nID, BM_GETCHECK, 0, 0) == BST_CHECKED)
		return true;
	 return false;
	}
	
};
