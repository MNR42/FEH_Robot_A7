#include <FEHLCD.h>
#include <time.h>
//#include <unistd.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>

   AnalogInputPin CdS_cell(FEHIO::P0_0);
   DigitalInputPin frontright(FEHIO::P1_0);
   DigitalInputPin frontleft(FEHIO::P1_2);
   DigitalInputPin backright(FEHIO::P0_0);
   DigitalInputPin backleft(FEHIO::P1_3);

   FEHServo servo1(FEHServo::Servo0);
   FEHServo servo2(FEHServo::Servo1);

   FEHMotor frontrightVex (FEHMotor::Motor0,7.2);
   FEHMotor frontleftVex (FEHMotor::Motor1,7.2);
   FEHMotor backrightVex (FEHMotor::Motor2,7.2);
   FEHMotor backleftVex (FEHMotor::Motor3,7.2);

   AnalogInputPin rightopto(FEHIO::P2_0);
   AnalogInputPin middleopto(FEHIO::P2_1);
   AnalogInputPin leftopto(FEHIO::P2_2);


int main(void)
{
    float x,y;
    int count = 0;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

   while( true && count <= 3)
    {
        if( LCD.Touch(&x,&y) && count == 0)
        {
           LCD.WriteLine("Front right positive");
           frontrightVex.SetPercent(40);
           Sleep(2);
           LCD.WriteLine("Front right negative");
           frontrightVex.SetPercent(-40);
           count++;
        }
        if( LCD.Touch(&x,&y) && count == 1)
        {
           LCD.WriteLine("Front left positive");
           frontleftVex.SetPercent(40);
           Sleep(2);
           LCD.WriteLine("Front left negative");
           frontleftVex.SetPercent(-40);
           count++;
        }
        if( LCD.Touch(&x,&y) && count == 2)
        {
           LCD.WriteLine("Back right positive");
           backrightVex.SetPercent(40);
           Sleep(2);
           LCD.WriteLine("Back right negative");
           backrightVex.SetPercent(-40);
           count++;
        }
        if( LCD.Touch(&x,&y) && count == 3)
        {
           LCD.WriteLine("Back left positive");
           backleftVex.SetPercent(40);
           Sleep(2);
           LCD.WriteLine("Back left negative");
           backleftVex.SetPercent(-40);
           count++;
        }
    }
    return 0;
}

