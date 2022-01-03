#include"REG52.H"
#include"12864libs����.h"
#include"string.h"
#include"stdlib.h"
#include<INTRINS.H>
#include"note.h"
#define  mainmusiclines 172
//��������
uchar* code playerlist[]=                                       //��Ϸ����б�
{      
      "ŷ���ο�",
      "������",
      "������",
      "������",
      "��  ��",
      "������",
      "���Ĳ�",
      "������",
      "�ŷ�˶",
      "��  ��"
};
uchar  playernum,playertotal;                                   //��ұ��,�������Ա��
uchar  gamefoward;                                              //��Ϸ������־
uchar  gamemode;                                                //��Ϸ�Ѷȱ�־
uint   HISCORE;                                                 //�߷�
uint   LINES;                                                   //��������
uint   LEVEL;                                                   //�ȼ�
uchar  NEXT;                                                    //��һ��������
uchar  page;                                                    //ҳ��
uchar  xdata rectangle[16][15];                                 //�����������
uchar  numberstring[10];                                        //�����ַ���
uchar  length;                                                  //�ַ�������
uint   code timecnt[]={250,200,150,100,50,25};                 //�����ȼ�
uchar  xdata score[10]={0};                                     //��ҷ���
uchar  playerrank[10];                                          //�����������
struct shapeinformation
{
       uchar  centernum;                                        //���Ŀ���
       uchar  shape[16][2];                                     //��¼��״      
       uchar  statusnum;                                        //״̬����
       uchar  blockcnt;                                         //��������
} present;
struct presentinfomation
{
       uchar  shapenum;                                         //��״���
       char   centerx,centery;                                  //��¼���ĵ�����
       uchar  status;                                           //��״״̬���
} presentshape;                                                 //����ط������xdata
struct shapeinformation code ddd[]=
{
       {
             1,
             {
                  {0,1},{1,1},{2,1},{3,1},
                  {0,0},{0,1},{0,2},{0,3}
             },
             2,
             4
       },

       {
             0,
             {
                  {0,0},{1,0},{0,1},{1,1}
             },
             1,
             4
       },

       {
             1,
             {
                  {0,0},{0,1},{1,1},{2,1},
                  {1,0},{1,1},{1,2},{0,2},
                  {0,0},{1,0},{2,0},{2,1},
                  {0,0},{0,1},{0,2},{1,0}
             },
             4,
             4
       },

       {
             2,
             {
                  {1,0},{0,1},{1,1},{2,1},
                  {1,0},{0,1},{1,1},{1,2},
                  {1,1},{0,0},{1,0},{2,0},
                  {1,1},{0,0},{0,1},{0,2}
             },
             4,
             4
       },

       {
             0,
             {
                  {1,0},{2,0},{0,1},{1,1},
                  {0,1},{0,0},{1,1},{1,2}
             },
             2,
             4
       },

       {
             2,
             {
                  {2,0},{0,1},{1,1},{2,1},
                  {0,0},{1,0},{1,1},{1,2},
                  {0,1},{0,0},{1,0},{2,0},
                  {1,2},{0,0},{0,1},{0,2}
             },
             4,
             4
       },
       
       {
             1,
             {
                  {0,0},{1,0},{1,1},{2,1},
                  {1,0},{0,1},{1,1},{0,2}
             },
             2,
             4
       }
};


//���Ŷ���
sbit   ENTER=P1^0;
sbit   LEFT =P1^1;
sbit   RIGHT=P1^2;
sbit   DOWN =P1^3;
sbit   SHIFT=P1^4;
sbit   BGM_INT0=P0^2;
sbit   BGM_INT1=P0^3;
//��������

void   setup();                                                 //�����ʼ��
void   mainmenu();                                              //��Ϸ������
void   chooseplayer();                                          //ѡ�����
void   choosedifficulty();                                      //ѡ���Ѷ�
void   game();                                                  //��Ϸ����
void   gamesetup();                                             //��Ϸ��ʼ��
void   gameover();                                              //��Ϸ��������
void   showshape(uchar,uchar);                                  //��ӡ��״
void   shownum(uint,uchar);                                     //��ʾ����(����,�����ȵ�)
void   delay1ms(uint);                                          //������ʱ����  
void   delay_1ms(uint);                                         //��ͨ��ʱ
void   resetshape();                                            //������״
void   moveline();                                              //����
void   updateWithoutInput();                                    //�̶��½�
void   updateWithInput();                                       //�ú������enter�����ҡ��¡�shift����
void   Entercommand();                                          //�任��״
void   Leftcommand();                                           //��״����
void   Rightcommand();                                          //��״����
void   Shiftcommand();                                          //��ҳ
void   Downcommand();                                           //����
void   showpage();                                              //��ʾҳ
void   showscore();                                             //���а���ʾ
uint   random(uint,uint,uint);                                  //����ָ����Χ�������
uchar  isdown();                                                //�ж��Ƿ����½�,������Ծ��½�,��������,���򷵻ؼ�
uchar  isover();                                                //�ж���Ϸ�Ƿ����


//��������
void   setup()
{
     //��Ϸ������ʼ��
     uchar i,j;
     HISCORE=0;
     LINES=0;
     LEVEL=1;     
     page=0;
     playernum=0;
     gamefoward=1;
     playertotal=10;
     gamemode=0;
     for(i=0;i<16;i++)
     for(j=0;j<15;j++)
     rectangle[i][j]=0;
     for(i=0;i<playertotal;i++)
     playerrank[i]=i;
}
void   mainmenu()
{
      while(!ENTER);
      LCD12864_init();
      LCD12864_showstring("��ӭ����",0,2);
      LCD12864_showstring("����˹����С��Ϸ",1,0);
      LCD12864_showstring("����С�� Powered",2,0);
      while(!ENTER);
      delay1ms(20);
      while(ENTER)
      {
          LCD12864_showstring("ENTER",3,3);
          LCD12864_pos(3,2);
          LCD12864_write_data(31);
          delay1ms(1000);
          LCD12864_showstring("       ",3,2);
          delay1ms(1000);
      }
      ENTER=1;
}
void   chooseplayer()
{
      while(!ENTER);
      LCD12864_init();
      LCD12864_showstring(" PLAERLISTS",1,1);
      LCD12864_pos(2,0);
      LCD12864_write_data(16);
      while(!ENTER);
      while(ENTER)
      {
           LCD12864_showstring(playerlist[playernum],2,2);
           while(!DOWN)
           {
               playernum=(playernum+1)%playertotal;
               LCD12864_showstring("        ",2,2);
               delay1ms(300);
           }
      }
      ENTER=1;
      delay1ms(20);
}
void   choosedifficulty()
{
      while(!ENTER);
      LCD12864_init();
      LCD12864_showstring("��ѡ����Ϸ�Ѷȣ�",0,0);
      LCD12864_showstring("��",2,2);
      LCD12864_showstring("��ͨ",3,2);
      LCD12864_showstring("����",2,6);
      LCD12864_showstring("����",3,6);
      while(!ENTER);
      LCD12864_pos(gamemode%2+2,gamemode/2*4+1);
      LCD12864_write_data(16);
      while(ENTER)
      {
           while(!DOWN)
           {
                LCD12864_pos(gamemode%2+2,gamemode/2*4+1);
                LCD12864_write_data(' ');
                gamemode=(gamemode+1)%4;
                LCD12864_pos(gamemode%2+2,gamemode/2*4+1);
                LCD12864_write_data(16);
                delay1ms(300);
           }
      }
      ENTER=1;
      delay1ms(20);
}
void   gamesetup()
{
       uchar i,j;
       while(!ENTER);
       delay1ms(20);
       LCD12864_init();
       LCD12864_clear_GDRAM();
       LCD12864_drawrectangle(0,0,59,0,1);
       LCD12864_drawrectangle(59,1,59,63,1);
       LCD12864_showstring("HI-SCORE",0,4);
       LCD12864_showstring("LINES",2,4);
       shownum(HISCORE,1);
       shownum(LINES,3);       
       NEXT=random(rand(),0,6);
       resetshape();

       for(i=0;i<16;i++)
       for(j=0;j<15;j++)
       LCD12864_drawrectangle(j*4,i*4+1,j*4+2,i*4+3,1);

       while(ENTER);

       for(i=0;i<16;i++)
       for(j=0;j<15;j++)
       LCD12864_drawrectangle(j*4,i*4+1,j*4+2,i*4+3,0);

       BGM_INT0=1;
       BGM_INT0=0;

} 
void   resetshape()
{
        
       presentshape.shapenum=NEXT;
       present=ddd[presentshape.shapenum];
       presentshape.centerx=5;
       presentshape.centery=present.shape[present.centernum][1]-present.shape[present.blockcnt-1][1]-1;
       presentshape.status=random(rand(),0,present.statusnum-1);
       NEXT=random(rand(),0,6);
}
void   game()
{
       gamesetup();
       while(gamefoward)
       {
            updateWithInput();
            updateWithoutInput();
       }
       gameover();
} 
void   updateWithoutInput()
{
       if(!isdown())
       {
            moveline();
            if(isover())
            gamefoward=0;
            else
            {
            resetshape();
            showpage();
            }
       }
}
void   updateWithInput()
{
       uint i,j;
       uchar time=gamemode+LEVEL-1<=6?gamemode+LEVEL-1:6;
       //������Ұ���
       for(i=0;i<timecnt[time];i++)
       for(j=0;j<110;j++)
       {
            if(!ENTER)
            {
                Entercommand();
            }
            if(!LEFT)
            {
                Leftcommand();
            }
            if(!RIGHT)
            {
                Rightcommand();
            }
            if(!SHIFT)
            {
                Shiftcommand();
            }
            if(!DOWN)
            {
                Downcommand();
            }
       }
}
void   Entercommand()
{
       uchar i;
       char x,y;
       uchar temp=present.centernum;
       uchar tmp=(presentshape.status+1)%present.statusnum;
       for(i=0;i<present.blockcnt;i++)
       {
            x=present.shape[i+present.blockcnt*tmp][0]-present.shape[temp+present.blockcnt*tmp][0]+presentshape.centerx;
            y=present.shape[i+present.blockcnt*tmp][1]-present.shape[temp+present.blockcnt*tmp][1]+presentshape.centery;
            if(rectangle[y][x]||x<0||x>14||y>15)return;
       }
       showshape(1,0);
       presentshape.status=tmp;
       showshape(1,1);
       while(!ENTER);
       delay_1ms(300);
}
void   Leftcommand() 
{
       char i;
       uchar temp=present.centernum;
       uchar tmp=presentshape.status*present.blockcnt;
       char x,y;
       for(i=0;i<present.blockcnt;i++)
       {
           x=present.shape[i+tmp][0]-present.shape[temp+tmp][0]+presentshape.centerx;
           y=present.shape[i+tmp][1]-present.shape[temp+tmp][1]+presentshape.centery;
           if(x==0||rectangle[y][x-1])return;
       }   
       showshape(1,0);
       presentshape.centerx--;
       showshape(1,1);
       while(!LEFT);
       delay_1ms(300);
}
void   Rightcommand()
{
       char i;
       uchar temp=present.centernum;
       uchar tmp=presentshape.status*present.blockcnt;
       char x,y;
       for(i=0;i<present.blockcnt;i++)
       {
           x=present.shape[i+tmp][0]-present.shape[temp+tmp][0]+presentshape.centerx;
           y=present.shape[i+tmp][1]-present.shape[temp+tmp][1]+presentshape.centery;
           if(x==14||rectangle[y][x+1])return;
       }   
       showshape(1,0);
       presentshape.centerx++;
       showshape(1,1);
       while(!RIGHT);
       delay_1ms(300);
}
void   Shiftcommand()
{
       uchar temp=present.centernum;
       page=1-page;
       showpage();
       while(!SHIFT);
       delay_1ms(300);
}
void   Downcommand() 
{
       while(isdown());
}
void   showpage()
{
       if(page)
       {
          LCD12864_clear_DDRAM();
          LCD12864_drawrectangle(64,48,127,63,0);
          LCD12864_showstring("LEVEL",0,4);
          LCD12864_showstring("NEXT",2,4);
          shownum(LEVEL,1);
          showshape(0,1);
       }
       else
       {
          LCD12864_clear_DDRAM();
          LCD12864_drawrectangle(64,48,127,63,0);
          LCD12864_showstring("HI-SCORE",0,4);
          LCD12864_showstring("LINES",2,4);
          shownum(HISCORE<score[playernum]*10?score[playernum]*10:HISCORE,1);
          shownum(LINES,3); 
       }
}
void   showshape(uchar mode,uchar flag)
{
       uchar i;
       uchar temp=present.centernum;
       uchar tmp=presentshape.status*present.blockcnt;
       char x,y;
       if(mode)
       for(i=0;i<present.blockcnt;i++)
       {
            x=present.shape[i+tmp][0]-present.shape[temp+tmp][0]+presentshape.centerx;
            y=present.shape[i+tmp][1]-present.shape[temp+tmp][1]+presentshape.centery;
            if(y>=0)
            LCD12864_drawrectangle(x*4,y*4+1,x*4+2,y*4+3,flag);
       }
       else
       for(i=0;i<present.blockcnt;i++)
       {
            x=ddd[NEXT].shape[i][0];
            y=ddd[NEXT].shape[i][1];
            LCD12864_drawrectangle(x*8+80,y*8+49,x*8+86,y*8+55,flag);
       }
}
void   moveline()
{
       char i,j,k;
       uchar count=0;
       for(i=15;i>0;i--)
       {
            for(j=0;j<15;j++)
               if(rectangle[i][j]==0)break;
            if(j==15)
            {
                 LINES++;
                 count++;
                 LCD12864_drawrectangle(0,i*4+1,58,i*4+3,0);
                 for(k=i;k;k--)
                 for(j=0;j<15;j++)
                     {
                         rectangle[k][j]=rectangle[k-1][j];
                         LCD12864_drawrectangle(j*4,k*4+1,j*4+2,k*4+3,rectangle[k][j]);
                     }
                 i++;
            }
       }
       LEVEL=LINES/20+1;
       HISCORE+=count*count*10;
}
uchar  isdown()
{
       char i,j;
       uchar temp=present.centernum;
       uchar tmp=presentshape.status*present.blockcnt;
       char  x,y;                                     //ע���������
       for(i=0;i<present.blockcnt;i++)
       {
            x=present.shape[i+tmp][0]-present.shape[temp+tmp][0]+presentshape.centerx;
            y=present.shape[i+tmp][1]-present.shape[temp+tmp][1]+presentshape.centery;
            if(y+1>=0&&(y==15||rectangle[y+1][x]))
            {
                   for(j=present.blockcnt-1;j>=0;j--)
                   {
                        x=present.shape[j+tmp][0]-present.shape[temp+tmp][0]+presentshape.centerx;
                        y=present.shape[j+tmp][1]-present.shape[temp+tmp][1]+presentshape.centery;
                        if(y>=0)
                        rectangle[y][x]=1; 
                   }
                   return 0;
            }
       }
       showshape(1,0);  
       presentshape.centery++;
       showshape(1,1);
       //���ĵ�ǰ��״����
       return 1;
}
uchar  isover()
{
       uchar i;
       uchar temp=present.centernum;
       uchar tmp=presentshape.status*present.blockcnt;
       char y;
       for(i=0;i<present.blockcnt;i++)
          {
              y=present.shape[i+tmp][1]-present.shape[temp+tmp][1]+presentshape.centery;
              if(y<0)return 1;
          }
       return 0;
}
void   gameover()
{
       uchar i,j,k;
       BGM_INT1=1;
       BGM_INT1=0;     
       for(i=0;i<16;i++)
       for(j=0;j<15;j++)
       LCD12864_drawrectangle(j*4,i*4+1,j*4+2,i*4+3,0);
       LCD12864_showstring("  GAME",1,0);
       LCD12864_showstring("  OVER",2,0);
       delay_1ms(2000);
       LCD12864_showstring("      ",1,0);
       LCD12864_showstring("      ",2,0);
       for(i=0;i<16;i++)
       for(j=0;j<15;j++)
       LCD12864_drawrectangle(j*4,i*4+1,j*4+2,i*4+3,1);
       delay_1ms(1000);  
       score[playernum]=HISCORE/10<score[playernum]?score[playernum]:HISCORE/10;
       for(i=0;i<playertotal-1;i++)
       {
             j=i;
             for(k=i+1;k<playertotal;k++)
             if(score[playerrank[k]]>score[playerrank[j]])j=k;
             k=playerrank[j];
             playerrank[j]=playerrank[i];
             playerrank[i]=k;
       }
}
void   showscore()
{
       uchar start=0;
       LCD12864_init();
       LCD12864_showstring("�������",0,2);
       while(ENTER)
       {
            String_numtostring(start+1,numberstring);
            LCD12864_showstring(numberstring,1,0);
            LCD12864_showstring(playerlist[playerrank[start]],1,1);
            shownum(score[playerrank[start]]*10,1);
            String_numtostring(start+2,numberstring);
            LCD12864_showstring(numberstring,2,0);
            LCD12864_showstring(playerlist[playerrank[start+1]],2,1);
            shownum(score[playerrank[start+1]]*10,2);
            if(start+3==10)
            LCD12864_showstring("10",3,0);
            else
            {
              String_numtostring(start+3,numberstring);
              LCD12864_showstring(numberstring,3,0);
            }
            LCD12864_showstring(playerlist[playerrank[start+2]],3,1);
            shownum(score[playerrank[start+2]]*10,3);
            while(!RIGHT)
            {
                 start=start<7?start+1:7;
                 LCD12864_showstring("                                                ",1,0);
                 delay1ms(300);
            }
            while(!LEFT)
            {
                 start=start?start-1:0;  
                 LCD12864_showstring("                                                ",1,0);
                 delay1ms(300);
            }
       }
       ENTER=1;
}
void   shownum(uint num,uchar y)
{
       String_numtostring(num,numberstring);
       length=String_strlen(numberstring);
       if(length%2)
       {
             String_mergestring(" ",numberstring,1,length,numberstring);
             length++;
       }
       LCD12864_showstring(numberstring,y,8-length/2);
}
void   delay1ms(uint x)
{
       uint i,j;
       for(i=0;i<x&&ENTER;i++)
       for(j=0;j<110;j++)
       if(!ENTER){ENTER=0;return;}
}
void   delay_1ms(uint x)
{
       uint i,j;
       for(i=0;i<x;i++)
       for(j=0;j<110;j++)
       ;
}
uint   random(uint seed,uint a,uint b)
{
       srand(seed);
       return rand()%(b-a+1)+a;
}



