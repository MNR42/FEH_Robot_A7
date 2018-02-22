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

   FEHMotor rightVex (FEHMotor::Motor0,7.2);
   FEHMotor leftVex (FEHMotor::Motor1,7.2);
   FEHMotor backrightVex (FEHMotor::Motor2,7.2);
   FEHMotor backleftVex (FEHMotor::Motor3,7.2);

   AnalogInputPin rightopto(FEHIO::P2_0);
   AnalogInputPin middleopto(FEHIO::P2_1);
   AnalogInputPin leftopto(FEHIO::P2_2);

   void turnRight()
   {

       double start_time=TimeNow();
       while((TimeNow()-start_time)<2)
       {

       rightVex.SetPercent(30);
       backrightVex.SetPercent(30);
       leftVex.SetPercent(30);
       backleftVex.SetPercent(30);

       }
       rightVex.Stop();
       backleftVex.Stop();
       backleftVex.Stop();
       leftVex.Stop();
   }

   void turnLeft()
   {
       double start_time=TimeNow();
       while((TimeNow()-start_time)<2)
       {
       leftVex.SetPercent(-30);
       rightVex.SetPercent(-30);
       backrightVex.SetPercent(-30);
       backleftVex.SetPercent(-30);

       }
       leftVex.Stop();
       backrightVex.Stop();
       rightVex.Stop();
       backleftVex.Stop();
   }

   void Forward(int percent, double time)
   {
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {

       backrightVex.SetPercent(percent);
       backleftVex.SetPercent(-1*percent);
       rightVex.SetPercent(percent);
       leftVex.SetPercent(-1*percent);
       }
       backrightVex.Stop();
       backleftVex.Stop();
       rightVex.Stop();
       leftVex.Stop();
   }

   void Reverse(int percent, double time)
   {

       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {

           backrightVex.SetPercent(-1*percent);
           backleftVex.SetPercent(percent);
           rightVex.SetPercent(-1*percent);
           leftVex.SetPercent(percent);
           }
           backrightVex.Stop();
           backleftVex.Stop();
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
           rightVex.SetPercent(-1*percent);
           backrightVex.SetPercent(percent);
           backleftVex.SetPercent(percent);

           }
           leftVex.Stop();
           backrightVex.Stop();
           rightVex.Stop();
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
       backleftVex.SetPercent(-1*percent);
       backrightVex.SetPercent(-1*percent);
       rightVex.SetPercent(percent);
       leftVex.SetPercent(percent);
       }
       backrightVex.Stop();
       rightVex.Stop();
       leftVex.Stop();
       backleftVex.Stop();
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


    Forward(30,.545);
    Left(30,1.22);
    Forward(30,1.2);
    Reverse(30,1.2);
    Right(30,3.22);
    Forward(30,2.9);
    turnLeft();
    Forward(25,1.2);
    Reverse(25,1.2);
    Left(80,5.6);

   }

  /* void PT1()
   {
    Forward(30,3);
    Left(30, 2);
    Forward(30,2);
    Reverse(30,1);
    Right(30,6);
    Forward(30,3);
    Left(30,3);
    Right(30,3);
    Reverse(30,8);

   }*/

int main(void)
{

    if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
    {
     LCD.WriteLine("!!!");
     FlipJack();
    }



    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

  /* while( true )
    {
        if( LCD.Touch(&x,&y) )
        {
           LCD.WriteLine("....................../´¯/");
           LCD.WriteLine("....................,/¯../");
           LCD.WriteLine(") .................../..../");
           LCD.WriteLine(") ............./´¯/'...'/´¯¯`·¸
            ........../'/.../..../......./¨¯\
            ........('(...´...´.... ¯~/'...')
            .........\.................'...../
            ..........''...\.......... _.·´
            ............\..............(
            ..............\.............\...
            Sleep( 100 );
        }
    }*/
    return 0;
}
