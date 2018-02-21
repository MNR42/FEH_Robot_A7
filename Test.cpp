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
   DigitalInputPin backright(FEHIO::P1_1);
   DigitalInputPin backleft(FEHIO::P1_3);

   FEHServo servo1(FEHServo::Servo0);
   FEHServo servo2(FEHServo::Servo1);

   FEHMotor rightVex (FEHMotor::Motor3,7.2);
   FEHMotor leftVex (FEHMotor::Motor2,7.2);
   FEHMotor backrightVex (FEHMotor::Motor1,7.2);
   FEHMotor backleftVex (FEHMotor::Motor0,7.2);

   AnalogInputPin rightopto(FEHIO::P2_0);
   AnalogInputPin middleopto(FEHIO::P2_1);
   AnalogInputPin leftopto(FEHIO::P2_2);

   void turnRight()
   {

       double start_time=TimeNow();
       while((TimeNow()-start_time)<2)
       {

       rightVex.SetPercent(-1*20);
       backleftVex.SetPercent(20);

       }
       rightVex.Stop();
       backleftVex.Stop();
   }

   void turnLeft()
   {
       double start_time=TimeNow();
       while((TimeNow()-start_time)<2)
       {
       leftVex.SetPercent(-1*20);
       backrightVex.SetPercent(20);
       }
       leftVex.Stop();
       backrightVex.Stop();
   }

   void Forward(int percent, double time)
   {
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {

       backrightVex.SetPercent(percent);
       backleftVex.SetPercent(percent);
       }
       backrightVex.Stop();
       backleftVex.Stop();
   }

   void Reverse(int percent, double time)
   {

       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {

       rightVex.SetPercent(-1*percent);
       leftVex.SetPercent(-1*percent);

       }
       rightVex.Stop();
       leftVex.Stop();
   }

   void Left(int percent, double time)
   {
       /*
       math for driving sideways
       */
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {
       leftVex.SetPercent(-1*percent);
       backleftVex.SetPercent(percent);
       }
       leftVex.Stop();
       backleftVex.Stop();

   }

   void Right(int percent, double time)
   {
       /*
       math for driving sideways
       */
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {

       backrightVex.SetPercent(percent);
       rightVex.SetPercent(-1*percent);
       }
       backrightVex.Stop();
       rightVex.Stop();
   }

   void FollowLine(double distance)
   {
       bool online;
         int x=5,position;

         while(x==5)
         {

             if(leftopto.Value()>.8 && leftopto.Value()<1.2)
             {
                 position=1;
             }

             else if(rightopto.Value()>.8 && rightopto.Value()<1.2)
             {
                 position=3;
             }
             else if(middleopto.Value()>.8 && middleopto.Value()<1.2)
             {
                 position=2;
             }

             switch(position)
             {
                 case(1):
                     rightVex.SetPercent(15);
                     leftVex.SetPercent(5);
                 break;
                 case(2):
                     rightVex.SetPercent(5);
                     leftVex.SetPercent(15);
                 break;
                 case(3):
                     rightVex.SetPercent(15);
                     leftVex.SetPercent(15);
                 break;
             default:
                 LCD.WriteLine("???");

             }


   }
   }

   void FlipJack()
   {
    Forward(20,3);
    Right(20,4);
    Forward(20,3);
    Left(20,3);

   }

  /* void PT1()
   {
    Forward(20,3);
    Left(20, 2);
    Forward(20,2);
    Reverse(20,1);
    Right(20,6);
    Forward(20,3);
    Left(20,3);
    Right(20,3);
    Reverse(20,8);

   }*/

int main(void)
{
    //if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
    //{
      //  for(int y=3;y>0;y++)
      //  {
      //  LCD.WriteLine("About to start in "+y);
      //  Sleep(1.0);
      //  }
    //FlipJack();
    //}

    FlipJack();

    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    while( true )
    {
        if( LCD.Touch(&x,&y) )
        {
            LCD.WriteLine( "Hello World!" );
            Sleep( 100 );
        }
    }
    return 0;
}
