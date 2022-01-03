#include"¶íÂÞË¹·½¿é.h"
sbit gnd=P0^0;
void main()
{ 
    gnd=0;
     while(1)
     {     
         setup();
         mainmenu();
         chooseplayer();
         choosedifficulty();
         game(); 
         showscore();   
     }
}

