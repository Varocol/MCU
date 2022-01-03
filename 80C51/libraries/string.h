#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
/*��������*/
void  String_numtostring(uint,uchar*);                           //����ת�����ַ���
//void  String_doubletostring(double,uchar*);                    //С��ת�����ַ���(�˺��������򲻵��ѵ�ʱ�����,��Ϊ��ռ�ڴ棡����)      
void  String_mergestring(uchar*,uchar*,uchar,uchar,uchar*);      //�ϲ��ַ���
void  String_strcpy(uchar*,uchar*,uint);                         //�����ַ���
uchar String_strlen(uchar*);                                     //�����ַ�������

/*��������*/
void  String_numtostring(uint num,uchar *p)
{
     uint i,temp,count;
     i=0;
     temp=0;
     count=num==0?1:0;
     while(num)
     {
         temp=temp*10+num%10;
         num/=10;
         count++;
     }
     for(;count--;i++)
     {
         p[i]=temp%10+'0';
         temp/=10;
     }
     p[i]='\0';
}
/*void  String_doubletostring(double x,uchar*p)
{
      double ZS,XS;
      uchar i,cnt;
      ZS=(long)x;
      cnt=ZS==0?1:0;
      while(ZS>=1)
          {
              ZS/=10;
              cnt++;
          }
      for(i=0;cnt--;i++)
      {
          ZS*=10;
          p[i]=(long)ZS+'0';
          ZS-=(long)ZS;
      }
      p[i++]='.';
      XS=x-(long)x;
      if(XS==0)
      {
          p[i++]='0';
      }
      for(;XS>0;i++)
      {
          XS*=10;
          p[i]=(long)XS+'0';
          XS-=(long)XS;
      }
      p[i]='\0';
}*/
void  String_mergestring(uchar*a,uchar*b,uchar len1,uchar len2,uchar*c)
{
      uchar temp[21],i;
      for(i=0;i<len1;i++)
      {
          temp[i]=a[i];
      }
      for(;i<len1+len2;i++)
      {
          temp[i]=b[i-len1];
      }
      for(i=0;i<len1+len2;i++)
      {
          c[i]=temp[i];
      }
      c[i]='\0';
}
void  String_strcpy(uchar*a,uchar*b,uint len)
{
      uchar i;
      for(i=0;i<len;i++)
      {
          a[i]=b[i];
      }
      a[i]='\0';
}
uchar String_strlen(uchar*a)
{
       uchar i=0;
       while(a[i]!='\0')
       i++;
       return i;
}