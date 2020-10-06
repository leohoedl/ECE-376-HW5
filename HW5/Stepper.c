// Stepper.C
// Drive a stepper motor at 100ms/step

// Global Variables
const unsigned char MSG[16] = "HW5.C           ";
unsigned char TABLE[4] = {1, 2, 4, 8};
unsigned char TABLE2[4] = {8, 4, 2, 1};
int N, TIME;

// Subroutine Declarations
#include <pic18.h>
#include "LCD_PortD.C"
char GetKey(void)
{
   int i;
   unsigned char RESULT;
   TRISC = 0xF8;
   RESULT = 0xFF;
   PORTC = 4;
   for (i=0; i<100; i++);
   if (RC6) RESULT = 1;
   if (RC5) RESULT = 4;
   if (RC4) RESULT = 7;
   if (RC3) RESULT = 10;
   PORTC = 2;
   for (i=0; i<100; i++);
   if (RC6) RESULT = 2;
   if (RC5) RESULT = 5;
   if (RC4) RESULT = 8;	
   if (RC3) RESULT = 0;
   PORTC = 1;
   for (i=0; i<100; i++);
   if (RC6) RESULT = 3;
   if (RC5) RESULT = 6;
   if (RC4) RESULT = 9;
   if (RC3) RESULT = 11;
   if (RB0) RESULT = 12;
   if (RB1) RESULT = 13;
   if (RB2) RESULT = 14;
   if (RB3) RESULT = 15;
   if (RB4) RESULT = 16;
   PORTC = 0;
   return(RESULT);
}
      
char ReadKey(void)
{
   char X, Y;
   do {
      X = GetKey();
      }   while(X > 20);
   do {
      Y= GetKey();
      }   while(Y < 20);
   Wait_ms(100);  // debounce
   return(X);
   }        


// Main Routine

void main(void)
{
   int STEP,i,X,Y,TEMP;

   TRISA = 0;
   TRISB = 0;
   TRISC = 0;
   TRISD = 0;
   TRISE = 0;
   ADCON1 = 0x0F;

   STEP = 0;
   X=0;

   LCD_Init();
   LCD_Move(0,0);
   for (i=0; i<16; i++) LCD_Write(MSG[i]);
   Wait_ms(100);
   LCD_Move(1,0);  LCD_Write('X');


while(1){
TEMP = ReadKey();
if (TEMP < 10) X = (X*10) + TEMP;
if (TEMP == 10) {
         Y = X;
         X = 0;
         }  
if (TEMP == 11) {
         X = X / 10;
         } 
LCD_Move(1,4);  LCD_Out(X, 4, 0);
if(Y==1111){
   while(STEP < 50 ) {
      STEP = STEP + 1;
      PORTA = TABLE[STEP % 4];
      LCD_Move(0,11);   LCD_Out(STEP, 2, 0);
      Wait_ms(20);
      }
	Wait_ms(4000);
	while(STEP > 0){
	  STEP = STEP - 1;
      PORTA = TABLE[STEP % 4];
      LCD_Move(0,11);   LCD_Out(STEP, 2, 0);
      Wait_ms(20);
 	}   
	 Y=0;
	 STEP = 0;
	}  
}

}