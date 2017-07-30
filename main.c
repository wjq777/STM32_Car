#include "stm32f10x.h"
#include "delay.h"
#include "math.h"
//#include "stm32f10x_usart.h"
unsigned char re_buff[11],counter=0,angle_low=0,angle_high=0;
float z_angle=0;

void USART1_IRQHandler(void)
{
	
  u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
			
		res=USART_ReceiveData(USART1);
		if(res==0x55)
			counter=0;
		re_buff[counter]=res;
		counter++;
		if(counter==11)
		{
			if(re_buff[0]==0x55&&re_buff[1]==0x53)
			{
				angle_low=re_buff[6];
				angle_high=re_buff[7];
			}
			counter=0;
		}
		
	}
	
}




float getAngle()
{
	z_angle=((short)(angle_high<<8|angle_low))/32768.0*180;
	return z_angle;
}	











/*!!!!!!!!!!!!!!!ÒÔÉÏÎª·½´óÊ¦´úÂë!!!!!!!!!!!!!!!!!!!!*/

int ceshia2;

int control(int x1,int y1,char x2,char y2)//dianji=control(0,0,20,20);
{
double x11=(float)(x1);
double x22=(float)(x2);
double y11=(float)(y1);
double y22=(float)(y2);

int i=0; //??
double a2 ;                // float a2 = atan((y22-y11)/(x22-x11));
double a1;
double a ; //???

	


a1= getAngle();  //float a1 = getAngle();float a1 = getAngle();
a2= acos((x22-x11)/(sqrt((x22-x11)*(x22-x11)+(y22-y11)*(y22-y11))));//a2 = atan((y22-y11)/(x22-x11));

	if((y22-y11)<0)
		a2=-a2;
	
/*if(((x11-x22)>0)&&((y11-y22)<0))
a2=a2+180;
	
if(((x11-x22)<0)&&((y11-y22)<0))
a1=-a1;

if(((x11-x22)<0)&&((y11-y22)>0))
a1=-a1;
*/
a= a2*180.000/3.1415926 +a1;

if(a>30)i=5;
else if(a>10 && a<=30)i=4;
else if(a>-10 && a<=10)i=1;
else if(a<=-10 && a>=-30)i=2;
else i=3;

return i;
}















/*!!!!!!!!!!!!!!ÒÔÉÏÎª³Â´óÊ¦´úÂë!!!!!!!!!!!!!!*/

void My_USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//¢Ù
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);//¢Ú
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_Init(GPIOA,&GPIO_InitStrue);//¢Ú
	
	USART_InitStrue.USART_BaudRate=115200;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStrue);//¢Û
	
	USART_Cmd(USART1,ENABLE);//Ê¹ÄÜ´®¿Ú1
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//¿ªÆô½ÓÊÕÖÐ¶Ï
	
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
	
	
}


 

void My_USART2_Init(void)//´®¿Ú¶þ ÔÄ¶ÁÆ÷
{
	
	GPIO_InitTypeDef GPIO_InitStrue;
USART_InitTypeDef USART_InitStrue;//´®¿ÚÉùÃ÷
NVIC_InitTypeDef NVIC_InitStrue;
	
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//´®¿Ú¶þÊ±ÖÓÊ¹ÄÜ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//¿ÉÒÔ²»ÒªÑ  ´®¿ÚÒ»ÒÑ¾­Ê¹ÄÜ
		GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;//?????????????????
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;//????????????GPIO_Mode_IN_FLOATING
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	//´®¿Ú³õÊ¼»¯  ¿´Ð­Òé£¡£¡¢Û
	USART_InitStrue.USART_BaudRate=115200;//²¨ÌØÂÊ¿´ÊÖ²á
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//178
  USART_InitStrue.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//168
	USART_InitStrue.USART_Parity=USART_Parity_No;//188
	USART_InitStrue.USART_StopBits=USART_StopBits_1;           //187 Ò»¸öÍ£Ö¹Î»
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;                   //186

USART_Init(USART2,&USART_InitStrue);//¢Û

   USART_Cmd(USART2,ENABLE);//´®¿ÚÊ¹ÄÜ
	 
	 
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//¿ªÆô½ÓÊÕÖÐ¶Ï
	
	NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
}





/*----------------------²âÊÔ½×¶Î´®¿ÚÈý½Ó°¢¶û¶ÅÒÁÅµ----------------------*/
void MY_USART3_init(void)// ´®¿ÚÈý À¶ÑÀ£©
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //1.Ê¹ÄÜÏàÓ¦µÄÊ±ÖÓ
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;            //2.³õÊ¼»¯IO¿Ú
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	USART_InitStruct.USART_BaudRate=115200;              //3.³õÊ¼»¯´®¿ÚÏàÓ¦µÄ²ÎÊý
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3, & USART_InitStruct);
	USART_Cmd(USART3,ENABLE);         //4.Ê¹ÄÜ´®¿Ú                     

USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);    //5.¿ªÆô½ÓÊÕÖÐ¶Ï
	NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);              //ÖÐ¶ÏÓÅÏÈ¼¶µÄÉèÖÃ
}
void MY_USART4_init(void)//Á¬½Ó°¢¶û¶ÅÒÁÅµ ¾­¹ýÅÐ¶ÏºóÏò°¢¶û¶ÅÒÁÅµ·¢ËÍ0/1/2/3/4/5
{
	GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); 

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOC, &GPIO_InitStructure);


GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
GPIO_Init(GPIOC, &GPIO_InitStructure);


USART_InitStructure.USART_BaudRate = 115200;
USART_InitStructure.USART_WordLength =USART_WordLength_8b;
USART_InitStructure.USART_StopBits =USART_StopBits_1;
USART_InitStructure.USART_Parity =USART_Parity_No;
USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
USART_InitStructure.USART_Mode = USART_Mode_Rx |USART_Mode_Tx; 

USART_Init(UART4, &USART_InitStructure);

USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

USART_Cmd(UART4, ENABLE);
	
	
}



/*void USART1_IRQHandler(void)   ¼ì²â´®¿ÚÒ»ÓÃ
{
	
	u8 res;
	 if(USART_GetITStatus(USART1,USART_IT_RXNE))
 {
     res= USART_ReceiveData(USART1); //¶Á´®¿ÚÒ»Ö¸Áî


     USART_SendData(USART1,res);   //·¢ËÍÖ¸Áî¸øÔÄ¶ÁÆ÷
	 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É
 
	
  }
}
*/





char Bpoint[4];//ÓÃÊý×éÀ´½ÓÊÜÀ¶ÑÀ·¢À´µÄBµã×ø±ê

int k=0;
int Bx,By;//ÓÃÀ´½ÓÊÜBµãºá×Ý×ø±ê

char p1=0;
void USART3_IRQHandler(void)//´®¿ÚÈýÖÐ¶Ï À¶ÑÀ½ÓÊÜBµãºá×Ý×ø±ê
{
	  
  	u8 res;
	  
	
	
	 if(USART_GetITStatus(USART3,USART_IT_RXNE))
 {  
     res= USART_ReceiveData(USART3); //¶Á´®¿ÚÈýÖ¸Áî
     if(res==0xFE)
		 {k=0;}
		 Bpoint[k]=res;
		 k=k+1;
		 if(Bpoint[2]==0xFF)
		 {if(k==4)
			 {k=0;
				Bx=Bpoint[1];
				By=Bpoint[3];
			 }
		 }
		 
 }
}




char b[16];
int flag=0;
int i=0;
char c[8];//±£´æEPC ÓÃÓÚ¼ÆËã
int x,y;//ºá×Ý×ø±ê
void USART2_IRQHandler(void)
{
	
	u8 res;
	 if(USART_GetITStatus(USART2,USART_IT_RXNE))
 {
	
     res= USART_ReceiveData(USART2); //¶Á´®¿Ú¶þ
	 if(res==0xAA)
	 {i=0;}
	 
	b[i]=res;
		i=i+1; 
	if(b[1]==0x02)
	{
	 if(i==16)
	 {i=0;
	
c[flag]=b[10];
c[flag+1]=b[11];	 
	// USART_SendData(USART3,b[10]);   //·¢ËÍÉÏÎ»»ú	À¶ÑÀ
	/*	 	 while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É
	  USART_SendData(USART3,b[11]);
		 	 while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É
	 */
		  flag=flag+2;
	 }
	 }
 
	
  }
}



char a[]={0xAA,0x00,0x22,0x00,0x00,0x22,0x8E};


	int flag2=1;//-------------------------------------------------¶Á²»µ½±êÇ©µÄ½â¾ö°ì·¨  Ôö¼ÓÒ»¸ö±êÖ¾Î»


void sendInstruction()
{
		for(i=0;i<7;i++)	
	{	USART_SendData(USART2,a[i]);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É}  
		}
}


int main(void)
 {	
	 
	 int dianji=0;
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 delay_init(); 
	 My_USART1_Init();
   My_USART2_Init();
	 MY_USART3_init();
	 MY_USART4_init();
	 while(1)
	 	{
  flag=0;
		
		sendInstruction();	
	

		delay_ms(200);
	switch(flag)
	{
		case 0:break;
		
		
		case 2:x=c[0];y=c[1];break;
		
		
		case 4:x=(c[0]+c[2])/2;y=(c[1]+c[3])/2;break;
	

		case 6:x=(c[0]+c[2]+c[4])/3;y=(c[1]+c[3]+c[5])/3;break; 
		
		case 8:x=(c[0]+c[2]+c[4]+c[6])/4;y=(c[1]+c[3]+c[5]+c[7])/4;break;
			
		default:break;
		
	}
	//Aµã x yÒÑ¾­µÃ³ö
	//Bµãºá×Ý×ø±ê Îª Bx By
	dianji=control(x,y,Bx,By);
	//Í¨¹ý´®¿Ú4·¢ËÍdianji¸ø°¢¶û¶ÅÒÁÅµ
	/*if(flag!=0)//À¶ÑÀ½ÓÊÜÓ¦¸ÃÒ²Òª±êÖ¾Î»*/
	
	
	/*²âÊÔÒÑÍ¨¹ý
	USART_SendData(UART4,Bx);   
		 	 while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
	USART_SendData(UART4,By);   
		 	 while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);
	*/

	
	if(sqrt(((int)x-50)*((int)x-50)+((int)y-50)*((int)y-50))<10)//·¶Î§×îºóÔÙÈ·¶¨
	{  USART_SendData(UART4,0);   
		 	 while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É             }	
			flag=0;
		  flag2=0;
			}
	
	
	if(flag)
	{USART_SendData(UART4,dianji);   
		 	 while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É
	} 
	
	if(flag==0&&flag2==0)
	{USART_SendData(UART4,0);   
		 	 while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É
	} 
	
	if(flag==0&&flag2==1)
	{USART_SendData(UART4,3);   
		 	 while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET);//µÈ´ýÊý¾Ý·¢ËÍÍê³É
	} 
		 
} 
} 
