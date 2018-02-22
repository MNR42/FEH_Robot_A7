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

   void turnRight()
   {

       double start_time=TimeNow();
       while((TimeNow()-start_time)<2)
       {

       frontrightVex.SetPercent(30);
       backrightVex.SetPercent(30);
       frontleftVex.SetPercent(30);
       backleftVex.SetPercent(30);

       }
       frontrightVex.Stop();
       backleftVex.Stop();
       backleftVex.Stop();
       frontleftVex.Stop();
   }

   void turnLeft()
   {
       double start_time=TimeNow();
       while((TimeNow()-start_time)<2)
       {
       frontleftVex.SetPercent(-30);
       frontrightVex.SetPercent(-30);
       backrightVex.SetPercent(-30);
       backleftVex.SetPercent(-30);

       }
       frontleftVex.Stop();
       backrightVex.Stop();
       frontrightVex.Stop();
       backleftVex.Stop();
   }

   void Forward(int percent, double time)
   {
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {

       backrightVex.SetPercent(-1*percent);
       backleftVex.SetPercent(percent);
       frontrightVex.SetPercent(-1*percent);
       frontleftVex.SetPercent(percent);
       }
       backrightVex.Stop();
       backleftVex.Stop();
       frontrightVex.Stop();
       frontleftVex.Stop();
   }

   void Reverse(int percent, double time)
   {

       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {

           backrightVex.SetPercent(percent);
           backleftVex.SetPercent(-1*percent);
           frontrightVex.SetPercent(percent);
           frontleftVex.SetPercent(-1*percent);
           }
           backrightVex.Stop();
           backleftVex.Stop();
           frontrightVex.Stop();
           frontleftVex.Stop();
   }

   void MoveLeft(int percent, double time)
   {
       /*
       math for driving sideways
       */
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {
           frontleftVex.SetPercent(-1*percent);
           frontrightVex.SetPercent(-1*percent);
           backrightVex.SetPercent(percent);
           backleftVex.SetPercent(percent);

           }
           frontleftVex.Stop();
           backrightVex.Stop();
           frontrightVex.Stop();
           backleftVex.Stop();

   }

   void MoveRight(int percent, double time)
   {
       /*
       math for driving sideways
       */
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {
       backleftVex.SetPercent(-1*percent);
       backrightVex.SetPercent(-1*percent);
       frontrightVex.SetPercent(percent);
       frontleftVex.SetPercent(percent);
       }
       backrightVex.Stop();
       frontrightVex.Stop();
       frontleftVex.Stop();
       backleftVex.Stop();
   }

   void MoveDiagonalBackRight (int percent, double time){
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {
           frontrightVex.SetPercent(percent);
           backleftVex.SetPercent(-1*percent);

           }
           frontrightVex.Stop();
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
                     frontrightVex.SetPercent(15);
                     frontleftVex.SetPercent(5);
                 break;
                 case(2):
                     frontrightVex.SetPercent(5);
                     frontleftVex.SetPercent(15);
                 break;
                 case(3):
                     frontrightVex.SetPercent(15);
                     frontleftVex.SetPercent(15);
                 break;
             default:
                 LCD.WriteLine("???");

             }


   }
   }

   void FlipJack()
   {


    Forward(30,.545);
    MoveLeft(30,1.22);
    Forward(30,1.2);
    Reverse(30,1.2);
    MoveRight(30,3.22);
    Forward(30,2.9);
    turnLeft();
    Forward(25,1.2);
    Reverse(25,1.2);
    MoveLeft(80,5.6);

   }

   void PT1()
   {
    MoveRight(30, 2);
    Reverse(30, 1);
    MoveDiagonalBackRight(30, 4.5);
    MoveRight(30, 1.0);
    Forward(30, 1.2);
    MoveLeft(30, 3.2);
    Forward(30, 5.0);
    MoveRight(30, 1.0);
    MoveLeft(30, 1.0);
    Forward(30, 1.5);
    MoveLeft(50, 3.6);
   }

int main(void)
{
    int x=5;
    while(x==5)
    {
    if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
    {
     LCD.WriteLine(CdS_cell.Value());
     LCD.WriteLine("!!!");
     PT1();
    }

    }

/*
    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

   while( true )
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
