//Programa: Free Shutdown
//Tipo:     Freeware
//Descripción: Permite apagar o reiniciar la PC de acuerdo al tiempo que se establezca
//Sitios Web:
//Programación en C/C++ con FMOD, SDL, OpenGL y DirectX 
//http://www.programacioncpp.irandohosting.0lx.net
//Free Applications
//http://www.freeapplications.irandohosting.0lx.net
//Compilador: Visual C++ 6.0

#include "CComboBox.h"
#include "CSpin.h"
#include "CUtility.h"
#include "CToolTip.h"
#include "CTrayIcon.h"
#include "hyperlink.h"
#include <stdio.h>

LRESULT CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK AboutProc(HWND,UINT,WPARAM,LPARAM);

#pragma comment(lib,"comctl32.lib")

#define ID_TIMER1 1
#define ID_TIMER2 2
#define ID_TIMER3 3


int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd)
{
 DialogBox(hInst,MAKEINTRESOURCE(IDD_MAIN),NULL,(DLGPROC)DlgProc);
 return 0;
}


LRESULT CALLBACK AboutProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
 CUtility u;
 HYPCTRL hc;
 RECT r;
 switch(uMsg){
   case WM_INITDIALOG:
	    u.SetHWND(hDlg);
		u.SetIconDlg(IDI_ICON8);
		GetClientRect(hDlg,&r);
	    InitHypCtrl(&hc);
		hc.ulStyle	 = ulHover;
		hc.szLink	 = TEXT("http://www.programacioncpp.irandohosting.0lx.net");
		hc.szTooltip = TEXT("Visitar Programación en C/C++ con FMOD, SDL, OpenGL y DirectX");
		CreateHypCtrl(hDlg, &hc,r.bottom/2-92,r.bottom-85, 0, 0);
		hc.ulStyle	 = ulHover;
		hc.szLink	 = TEXT("http://www.freeapplications.irandohosting.0lx.net");
		hc.szTooltip = TEXT("Visitar Free Applications");
		CreateHypCtrl(hDlg, &hc,r.bottom/2-92,r.bottom-65, 0, 0);
		
		u.Center();		
	    return 0;
    case WM_CLOSE:
	    EndDialog(hDlg,0);		
		return 0;      
	case WM_COMMAND:
	    switch(LOWORD(wParam)){	 
		  case ID_ABOUT_OK:
			   EndDialog(hDlg,0);
			   break;
		}
		return 0;
   default:
	    return 0;

 }
 return DefWindowProc(hDlg,uMsg,wParam,lParam);
}

LRESULT CALLBACK DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
 static CTimer    t;
 static CUtility  u;
 static CComboBox c;
 static CTrayIcon     i;
 static CSpin s,s2,s3;
 static CToolTip tt(hDlg);

 static int iHour=0,iMin=0,iSec=0;
 static short iFlag; 
 static bool bTime=false;
 static int hour=0,min=0,seg=0;
 static HMENU hPopupMenu;
 char strTimeText[80]={0};
 char strTime[50]={0};
 char strLocalTime[50]={0};
 std::string strOs;
 SYSTEMTIME st;
 RECT rc;
 SetRectEmpty(&rc);

 switch(uMsg){
   
   case WM_INITDIALOG:	   
	    tt.Create(rc.left,rc.top,rc.right,rc.bottom,0);
		tt.SetToolTip(GetDlgItem(hDlg,IDABOUT),"Muestra información el programa");
        tt.SetToolTip(GetDlgItem(hDlg,IDCANCEL),"Detiene el temporizador");
		tt.SetToolTip(GetDlgItem(hDlg,IDOK),"Inicia el temporizador");
		tt.SetToolTip(GetDlgItem(hDlg,IDSHUTDOWN),"Apaga la PC");
		tt.SetToolTip(GetDlgItem(hDlg,IDCLOSE),"Cierra la sesión de Windows");
		tt.SetToolTip(GetDlgItem(hDlg,IDREBOOT),"Reiniciar la PC");
		tt.SetToolTip(GetDlgItem(hDlg,IDC_RADIO_SHUTDOWN),"Opción para apagar la PC");
		tt.SetToolTip(GetDlgItem(hDlg,IDC_RADIO_REBOOT),"Opción para reiniciar la PC");
		tt.SetToolTip(GetDlgItem(hDlg,IDC_SPIN),"Selecciona la hora manualmente");
        tt.SetToolTip(GetDlgItem(hDlg,IDC_SPIN2),"Selecciona los minutos manualmente");
		tt.SetToolTip(GetDlgItem(hDlg,IDC_SPIN3),"Selecciona los segundos manualmente");
        tt.SetToolTip(GetDlgItem(hDlg,IDC_COMBO1),"Selección de tiempo");
		tt.SetToolTip(GetDlgItem(hDlg,IDC_CHECK_TIME),"Opción para seleccionar el tiempo manualmente");
		strOs=u.GetOS().c_str();
		
		
	    t.SetHWND(hDlg);
		s.SetHWND(hDlg,IDC_SPIN);
		s2.SetHWND(hDlg,IDC_SPIN2);
		s3.SetHWND(hDlg,IDC_SPIN3);
		s.SetRange(0,24);	
		s2.SetRange(0,59);
		s3.SetRange(0,59);
		s.SetBuddy(GetDlgItem(hDlg,IDC_EDIT));
		s2.SetBuddy(GetDlgItem(hDlg,IDC_EDIT2));	
		s3.SetBuddy(GetDlgItem(hDlg,IDC_EDIT3));
		s2.SetPos(0);
		s.SetPos(0);	
		s3.SetPos(0);
		t.Create(ID_TIMER2,1000);
		t.Create(ID_TIMER3,1000);
	    u.SetHWND(hDlg);
		u.SetBitmapButton();
		if(!strcmp("Windows 98",strOs.c_str()) || !strcmp("Windows ME",strOs.c_str()) || !strcmp("Windows 95",strOs.c_str())){
		 EnableWindow(GetDlgItem(hDlg,IDCLOSE),FALSE);
		 ImageButton_SetIcon(GetDlgItem(hDlg, IDCLOSE), IDI_ICON3, IBO_GRAY,IBO_LIGHTEN);
		}
		hPopupMenu=u.SetOfficeMenu(hDlg);
		c.SetHWND(hDlg,IDC_COMBO1);
		c.AddText("5 minutos");	
		c.AddText("10 minutos");
		c.AddText("15 minutos");
		c.AddText("30 minutos");
		c.AddText("45 minutos");
		c.AddText("1 hora");
		c.AddText("1 hora y media");
		c.AddText("2 horas");
		c.AddText("2 horas y media");
		c.AddText("3 horas");
		c.AddText("3 horas y media");
		c.AddText("4 horas");
		c.AddText("4 horas y media");
		c.AddText("5 horas");
		c.AddText("5 horas y media");
		c.AddText("6 horas");
		c.AddText("6 horas y media");
		c.AddText("7 horas");
		c.AddText("8 horas");
		c.AddText("9 horas");
		c.AddText("12 horas");
		c.AddText("15 horas");
		c.AddText("18 horas");
		c.AddText("24 horas");
		c.SetCurSel();	
		u.SetIconDlg(IDI_ICON8);
	    u.Center();
		EnableWindow(GetDlgItem(hDlg,IDCANCEL),FALSE);					       
	    return 0;
   case WM_NOTIFYICONTRAY:	
	   {
		POINT p;
	    GetCursorPos(&p);		  
	    if((UINT)lParam==WM_RBUTTONUP)
		 i.ShowMenu(hPopupMenu,hDlg,p);
	   }  
        return 0;
   case WM_TIMER:
	   switch(wParam){
	     case ID_TIMER1:
		   iSec--;

		   if(iSec >= 60){
            iMin=iSec / 60;
		    iSec=iSec % 60;
		   }
		   if(iMin >= 60){
            iHour=iMin / 60;
		    iMin =iMin % 60;
		   }

		   if(iSec == 0){			
			if(iMin > 0){
			 iSec+=59;
			 iMin--;
			}
		   }

		   if(iMin == 0){		    			
			 if(iHour > 0){
			  iMin+=59;
              iHour--;
			 }
		   }

	       sprintf(strTime,"Tiempo Restante: %02d:%02d:%02d",iHour,iMin,iSec);		   
	       u.SetText(IDC_STATIC_TIME,strTime);
		   i.SetToolTip(hDlg,strTime);
         

		   if(iFlag==SHUTDOWN){		    
			   if(iMin == 0 && iSec == 0 && iHour== 0){		        
				u.ExitWin32(SHUTDOWN);
				t.Destroy(ID_TIMER1);
				PostMessage(hDlg,WM_CLOSE,0,0);
			   }
		      
		   }
		   if(iFlag==REBOOT){		    
			   if(iMin == 0 && iSec == 0 && iHour== 0){		        
				u.ExitWin32(REBOOT);
				t.Destroy(ID_TIMER1);
				PostMessage(hDlg,WM_CLOSE,0,0);
			   }
		      
		   }
              break;
		 case ID_TIMER2:
			  GetLocalTime(&st);			 
			  sprintf(strLocalTime,"Hora Actual: %02d:%02d:%02d",st.wHour,st.wMinute,st.wSecond);			  			  			           
			  u.SetText(IDC_STATIC_TIME2,strLocalTime);
			  break;
		 case ID_TIMER3:			  
			  if(u.CheckButton(IDC_CHECK_TIME)){
			   EnableWindow(GetDlgItem(hDlg,IDC_SPIN),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_SPIN2),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_SPIN3),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_EDIT),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_EDIT2),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_EDIT3),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_COMBO1),FALSE);              
			   bTime=true;
			  }
			  else{
               EnableWindow(GetDlgItem(hDlg,IDC_SPIN),  FALSE);
			   EnableWindow(GetDlgItem(hDlg,IDC_SPIN2), FALSE);
			   EnableWindow(GetDlgItem(hDlg,IDC_SPIN3), FALSE);
			   EnableWindow(GetDlgItem(hDlg,IDC_EDIT),  FALSE);
			   EnableWindow(GetDlgItem(hDlg,IDC_EDIT2), FALSE);
			   EnableWindow(GetDlgItem(hDlg,IDC_EDIT3), FALSE);
			   EnableWindow(GetDlgItem(hDlg,IDC_COMBO1),TRUE);              
			   bTime=false;
			  }
			  break;
	   }
	    return 0;
   case WM_SIZE:
	    if(wParam == SIZE_MINIMIZED){		 
		  i.SetIcon(hDlg,"Da clic derecho para mostrar menu",IDI_ICON8);
		  i.Hide(hDlg);	
		  

		}
		return 0;
   case WM_COMMAND:
	    switch(LOWORD(wParam)){
		  case IDMENU_SHOW:
			   i.Destroy_Icon(hDlg);
		       i.ShowIcon(hDlg);
			   
			   break;
		  case IDMENU_EXIT:
			   EndDialog(hDlg,0);
			   break;
		  case IDMENU_SHUTDOWN:
		  case IDSHUTDOWN:
			   if(u.ShowQuestion("Desea apagar Windows (S/N)?")==IDYES){
				u.ExitWin32(SHUTDOWN);
				PostMessage(hDlg,WM_CLOSE,0,0);
			   }
	           break;
		  case IDMENU_ABOUT:
		  case IDABOUT:
			   DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ABOUT),hDlg,(DLGPROC)AboutProc);
			   break;
		  case IDMENU_REBOOT:
		  case IDREBOOT:
			   if(u.ShowQuestion("Desea reiniciar Windows (S/N)?")==IDYES){
                u.ExitWin32(REBOOT);			   
				PostMessage(hDlg,WM_CLOSE,0,0);
			   }
			   break;
		  case IDMENU_CLOSE:
		  case IDCLOSE:
			   if(u.ShowQuestion("Desea cerrar su sesión de Windows (S/N)?")==IDYES){
			    u.LockWorkStation();
				i.SetIcon(hDlg,"Da clic derecho para mostrar menu",IDI_ICON8);
		        i.Hide(hDlg);	
			   }
			   break;
		  case IDOK:
			   if(bTime){
                 if(u.CheckButton(IDC_RADIO_SHUTDOWN)){					
					if(s.GetPos() == 0 && s2.GetPos() == 0 && s3.GetPos() == 0)
					 u.ShowError("Error debe seleccionar un tiempo valido");					
					else{
                     iSec=t.HourToSec(s.GetPos()) + t.MinToSec(s2.GetPos()) + s3.GetPos();
					 seg=iSec;					 
					 
                     if(seg >= 60){
                       min=seg / 60;
		               seg=seg % 60;
					 }
		             if(min >= 60){
                       hour=min / 60;
		               min =min % 60;
					 }
					 
					 if(hour > 0 && min == 0 && seg == 0)
                      sprintf(strTimeText,"Se apagara en %d hora(s)",hour);
					 else if(hour == 0 && min > 0 && seg > 0)
                      sprintf(strTimeText,"Se apagara en %d minuto(s) y %d segundo(s)",min,seg);
					 else if(hour == 0 && min == 0 && seg > 0)
                      sprintf(strTimeText,"Se apagara en %d segundo(s)",seg);
					 else if(hour == 0 && min > 0 && seg == 0)
					  sprintf(strTimeText,"Se apagara en %d minuto(s)",min);
					 else
					  sprintf(strTimeText,"Se apagara en %d hrs %d min y %d seg",hour,min,seg);

					 u.SetText(IDC_STATIC_TEXT,strTimeText);                     
					 t.Create(ID_TIMER1,1000);
				     iFlag=SHUTDOWN;
					 t.Destroy(ID_TIMER3);
					 SendDlgItemMessage(hDlg,IDC_CHECK_TIME, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
					 EnableWindow(GetDlgItem(hDlg,IDOK),FALSE);					 
				     EnableWindow(GetDlgItem(hDlg,IDC_RADIO_REBOOT),FALSE);
				     EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SHUTDOWN),FALSE);
					 EnableWindow(GetDlgItem(hDlg,IDC_CHECK_TIME),FALSE);
				     EnableWindow(GetDlgItem(hDlg,IDC_COMBO1),FALSE);
					 EnableWindow(GetDlgItem(hDlg,IDC_SPIN),  FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_SPIN2), FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_SPIN3), FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_EDIT),  FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_EDIT2), FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_EDIT3), FALSE);
				     EnableWindow(GetDlgItem(hDlg,IDCANCEL),  TRUE);					 
					 i.SetIcon(hDlg,"Da clic derecho para mostrar menu",IDI_ICON8);
		             i.Hide(hDlg);
					}
				 }
				 else if(u.CheckButton(IDC_RADIO_REBOOT)){
					if(s.GetPos() == 0 && s2.GetPos() == 0 && s3.GetPos() == 0)
					 u.ShowError("Error debe seleccionar un tiempo valido");
					else{
                     iSec=t.HourToSec(s.GetPos()) + t.MinToSec(s2.GetPos()) + s3.GetPos();
					 seg=iSec;					 
					 
                     if(seg >= 60){
                       min=seg / 60;
		               seg=seg % 60;
					 }
		             if(min >= 60){
                       hour=min / 60;
		               min =min % 60;
					 }
					 
					 if(hour > 0 && min == 0 && seg == 0)
                      sprintf(strTimeText,"Se apagara en %d hora(s)",hour);
					 else if(hour == 0 && min > 0 && seg > 0)
                      sprintf(strTimeText,"Se apagara en %d minuto(s) y %d segundo(s)",min,seg);
					 else if(hour == 0 && min == 0 && seg > 0)
                      sprintf(strTimeText,"Se apagara en %d segundo(s)",seg);
					 else if(hour == 0 && min > 0 && seg == 0)
					  sprintf(strTimeText,"Se apagara en %d minuto(s)",min);
					 else
					  sprintf(strTimeText,"Se apagara en %d hrs %d min y %d seg",hour,min,seg);

					 u.SetText(IDC_STATIC_TEXT,strTimeText);             
					 t.Create(ID_TIMER1,1000);
				     iFlag=REBOOT;
					 t.Destroy(ID_TIMER3);
					 SendDlgItemMessage(hDlg,IDC_CHECK_TIME, BM_SETCHECK, (WPARAM)BST_UNCHECKED, 0);
					 EnableWindow(GetDlgItem(hDlg,IDOK),FALSE);					 
				     EnableWindow(GetDlgItem(hDlg,IDC_RADIO_REBOOT),FALSE);
				     EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SHUTDOWN),FALSE);
					 EnableWindow(GetDlgItem(hDlg,IDC_CHECK_TIME),FALSE);
				     EnableWindow(GetDlgItem(hDlg,IDC_COMBO1),FALSE);
					 EnableWindow(GetDlgItem(hDlg,IDC_SPIN),  FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_SPIN2), FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_SPIN3), FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_EDIT),  FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_EDIT2), FALSE);
			         EnableWindow(GetDlgItem(hDlg,IDC_EDIT3), FALSE);
				     EnableWindow(GetDlgItem(hDlg,IDCANCEL),  TRUE);					 
					 i.SetIcon(hDlg,"Da clic derecho para mostrar menu",IDI_ICON8);
		             i.Hide(hDlg);
					}
				 }
				 else
				    u.ShowError("No ha seleccionado ninguna opción\nPor ejemplo Apagar o Reiniciar");
				  
			   }
			   else{
			    if(u.CheckButton(IDC_RADIO_SHUTDOWN)){
				 switch(c.GetCurSel()){
				   case 0:					   					  
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 5 minutos");
					   iSec=t.MinToSec(5);
					   break;
				   case 1:					   
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 10 minutos");
					   iSec=t.MinToSec(10);
					   break;
				   case 2:
                       u.SetText(IDC_STATIC_TEXT,"Se apagara en 15 minutos");					   
					   iSec=t.MinToSec(15);
					   break;
				   case 3:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 30 minutos");					   
					   iSec=t.MinToSec(30);
					   break;
				   case 4:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 45 minutos");					   
					   iSec=t.MinToSec(45);
					   break;
				   case 5:					   
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 1 hora");
					   iSec=t.HourToSec(1);
					   break;
				   case 6:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 1 hora y media");					   
					   iSec=t.HourToSec(1,30);
					   break;
				   case 7:
                       u.SetText(IDC_STATIC_TEXT,"Se apagara en 2 horas");					   
					   iSec=t.HourToSec(2);
					   break;
				   case 8:
                       u.SetText(IDC_STATIC_TEXT,"Se apagara en 2 horas y media");					   
					   iSec=t.HourToSec(2,30);
					   break;
				   case 9:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 3 horas");					   
					   iSec=t.HourToSec(3);
					   break;
				   case 10:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 3 horas y media");					   
					   iSec=t.HourToSec(3,30);
					   break;
				   case 11:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 4 horas");					 
					   iSec=t.HourToSec(4);
					   break;
				   case 12:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 4 horas y media");
					   iSec=t.HourToSec(4,30);
					   break;
				   case 13:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 5 horas");
					   iSec=t.HourToSec(5);
					   break;
				   case 14:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 5 horas y media");
					   iSec=t.HourToSec(5,30);
					   break;
				   case 15:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 6 horas");
					   iSec=t.HourToSec(6);
					   break;
				   case 16:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 6 horas y media");
					   iSec=t.HourToSec(6,30);
					   break;
				   case 17:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 7 horas");
					   iSec=t.HourToSec(7);
					   break;				   
				   case 18:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 8 horas");
					   iSec=t.HourToSec(8);
					   break;
				   case 19:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 9 horas");
					   iSec=t.HourToSec(9);
					   break;
				   case 20:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 12 horas");
					   iSec=t.HourToSec(12);
					   break;
				   case 21:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 15 horas");
					   iSec=t.HourToSec(15);
					   break;
				   case 22:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 18 horas");
					   iSec=t.HourToSec(18);
					   break;
				   case 23:
					   u.SetText(IDC_STATIC_TEXT,"Se apagara en 24 horas");
					   iSec=t.HourToSec(24);
					   break;

				 } 
				 t.Destroy(ID_TIMER3);
				 t.Create(ID_TIMER1,1000);
				 iFlag=SHUTDOWN;
				 
				 EnableWindow(GetDlgItem(hDlg,IDOK),FALSE);				 
				 EnableWindow(GetDlgItem(hDlg,IDC_RADIO_REBOOT),FALSE);
				 EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SHUTDOWN),FALSE);
				 EnableWindow(GetDlgItem(hDlg,IDC_COMBO1),FALSE);
				 EnableWindow(GetDlgItem(hDlg,IDCANCEL),TRUE);
				 EnableWindow(GetDlgItem(hDlg,IDC_CHECK_TIME),FALSE);				 
				 i.SetIcon(hDlg,"Da clic derecho para mostrar menu",IDI_ICON8);
		         i.Hide(hDlg);
				}
			    else if(u.CheckButton(IDC_RADIO_REBOOT)){                
				 switch(c.GetCurSel()){
				   case 0:
					    u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 5 minutos");
						iSec=t.MinToSec(5);
					    break;
				   case 1:
					    u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 10 minutos");
						iSec=t.MinToSec(10);
					    break;
				   case 2:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 15 minutos");
					   iSec=t.MinToSec(15);
					   break;
				   case 3:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 30 minutos");
					   iSec=t.MinToSec(30);
					   break;
				   case 4:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 45 minutos");
					   iSec=t.MinToSec(45);
					   break;
				   case 5:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 1 hora");
					   iSec=t.HourToSec(1);
					   break;
				   case 6:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 1 hora y media");
					   iSec=t.HourToSec(1,30);
					   break;
				   case 7:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 2 horas");
					   iSec=t.HourToSec(2);
					   break;
				   case 8:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 2 horas y media");
					   iSec=t.HourToSec(2,30);
					   break;
				   case 9:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 3 horas");
					   iSec=t.HourToSec(3);
					   break;
				   case 10:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 3 horas y media");
					   iSec=t.HourToSec(3,30);
					   break;
				   case 11:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 4 horas");
					   iSec=t.HourToSec(4);
					   break;
				   case 12:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 4 horas y media");
					   iSec=t.HourToSec(4,30);
					   break;
				   case 13:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 5 horas");
					   iSec=t.HourToSec(5);
					   break;
				   case 14:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 5 horas y media");
					   iSec=t.HourToSec(5,30);
					   break;
				   case 15:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 6 horas");
					   iSec=t.HourToSec(6);
					   break;
				   case 16:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 6 horas y media");
					   iSec=t.HourToSec(6,30);
					   break;
				   case 17:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 7 horas");
					   iSec=t.HourToSec(7);
					   break;				   
				   case 18:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 8 horas");
					   iSec=t.HourToSec(8);
					   break;
				   case 19:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 9 horas");
					   iSec=t.HourToSec(9);
					   break;
				   case 20:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 12 horas");
					   iSec=t.HourToSec(12);
					   break;
				   case 21:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 15 horas");
					   iSec=t.HourToSec(15);
					   break;
				   case 22:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 18 horas");
					   iSec=t.HourToSec(18);
					   break;
				   case 23:
					   u.SetText(IDC_STATIC_TEXT,"Se reiniciara en 24 horas");
					   iSec=t.HourToSec(24);
					   break;

				 }
				 t.Destroy(ID_TIMER3);
				 t.Create(ID_TIMER1,1000);
				 iFlag=REBOOT;
				 EnableWindow(GetDlgItem(hDlg,IDOK),FALSE);				 
				 EnableWindow(GetDlgItem(hDlg,IDC_RADIO_REBOOT),FALSE);
				 EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SHUTDOWN),FALSE);
				 EnableWindow(GetDlgItem(hDlg,IDC_COMBO1),FALSE);
				 EnableWindow(GetDlgItem(hDlg,IDCANCEL),TRUE);
				 EnableWindow(GetDlgItem(hDlg,IDC_CHECK_TIME),FALSE);				 
				 i.SetIcon(hDlg,"Da clic derecho para mostrar menu",IDI_ICON8);
		         i.Hide(hDlg);
				}
			    else
				 u.ShowError("No ha seleccionado ninguna opción\nPor ejemplo Apagar o Reiniciar");
			   }
			   break;
		  case IDCANCEL:
			   t.Destroy(ID_TIMER1);
			   t.Create(ID_TIMER3,1000);
               EnableWindow(GetDlgItem(hDlg,IDOK),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_RADIO_REBOOT),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_RADIO_SHUTDOWN),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_COMBO1),TRUE);
			   EnableWindow(GetDlgItem(hDlg,IDC_CHECK_TIME),TRUE);			    			   			
			   EnableWindow(GetDlgItem(hDlg,IDCANCEL),FALSE);			   
			   u.SetText(IDC_STATIC_TIME,"Tiempo Restante 00:00:00");
			   u.SetText(IDC_STATIC_TEXT,"");
			   iHour=iMin=iSec=0;
			   hour=min=seg=0;
			   c.SetCurSel();
			   s2.SetPos(0);
		       s.SetPos(0);	
		       s3.SetPos(0);
			   break;
		}
	    return 0;
   case WM_CLOSE:
	    EndDialog(hDlg,0);		
		return 0;
   case WM_DESTROY:		    
	    i.Destroy_Icon(hDlg);
	    t.Destroy(ID_TIMER1);
		t.Destroy(ID_TIMER2);
		t.Destroy(ID_TIMER3);
	    PostQuitMessage(0);
	    return 0;
   default:
	    return 0;
	    
 }
  return DefWindowProc(hDlg,uMsg,wParam,lParam);
}
