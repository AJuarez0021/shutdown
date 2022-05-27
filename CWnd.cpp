#include "CWnd.h"

using namespace std;


string CWnd::GetOS() 
{
   string strOs="";
   OSVERSIONINFOEX osvi;
   BOOL bOsVersionInfoEx;
   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
      return "Desconocido";

   if(osvi.dwMajorVersion == 4)
   {
           
	     switch (osvi.dwMinorVersion)
		 {
          case 0:
           if(osvi.dwPlatformId ==VER_PLATFORM_WIN32_WINDOWS)
			   strOs+="Windows 95";		   
		   else       
			   strOs+="Windows NT 4.0";		   
           break;
          case 10:       
		   strOs+="Windows 98";
           break;
          case 90:          
		   strOs+="Windows ME";
           break;
          default:   
		   strOs+="Desconocido";
		   break;
		 }
   }
   else if(osvi.dwMajorVersion == 3)
   {
       strOs="Windows NT 3.51";
   }
   else
   {  
     
	   strOs="Desconocido";
   }
   return strOs;
}