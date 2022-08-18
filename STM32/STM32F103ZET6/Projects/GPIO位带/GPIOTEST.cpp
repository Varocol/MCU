#include "Libraries.h"
int main()
{
     GPIO_InitTypeDef GPIO_Common_In_Struct = 
     {
         GPIO_Pin_7,
         GPIO_Speed_50MHz,
         GPIO_Mode_IPU
     };
     GPIO a = GPIO(GPIOA,GPIO_Common_In_Struct);
     a.Init();
     GPIO_InitTypeDef GPIO_Common_Out_Struct = 
     {
         GPIO_Pin_7,
         GPIO_Speed_50MHz,
         GPIO_Mode_Out_PP
     };
     a.Update(GPIOA,GPIO_Common_Out_Struct);
     GPIO_Common_Out_Struct.GPIO_Pin=GPIO_Pin_12;
     a.Update(GPIOB,GPIO_Common_Out_Struct);
     PBout(12)=1;
     while(1)
     {
         if(!PAin(7))
         {
             PBout(12)=0;
         }
         else if(PAin(7))
         {
             PBout(12)=1;
         }
     }
}