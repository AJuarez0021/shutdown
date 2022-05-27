#ifndef __CTIMER_H
#define __CTIMER_H

#include "CWnd.h"


class CTimer : public CWnd{
private:   

public:
	
	void Create(int nID,int uElapse){	 
     SetTimer(m_hWnd,nID,uElapse,NULL);
	}
    
	int MinToSec(int iMin){
      return iMin * 60;
	}
	int HourToSec(int iHour){
      return iHour * 3600;
	}
	int HourToSec(int iHour,int iMin){
      return (iHour*3600) + MinToSec(iMin);
	}
	void Destroy(int nID){
     KillTimer(m_hWnd,nID);
	}
};

#endif