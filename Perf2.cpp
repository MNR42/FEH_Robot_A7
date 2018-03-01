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


  FEHServo servo1(FEHServo::Servo0);
  FEHServo servo2(FEHServo::Servo1);

  FEHMotor frontrightVex (FEHMotor::Motor0,7.2);
  FEHMotor frontleftVex (FEHMotor::Motor1,7.2);
  FEHMotor backrightVex (FEHMotor::Motor2,7.2);
  FEHMotor backleftVex (FEHMotor::Motor3,7.2);

  AnalogInputPin rightopto(FEHIO::P1_4);
  AnalogInputPin middleopto(FEHIO::P1_2);
  AnalogInputPin leftopto(FEHIO::P1_0);


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

   void MoveDiagonalFrontLeft (int percent, double time){
          double start_time=TimeNow();
          while((TimeNow()-start_time)<time)
          {
              frontrightVex.SetPercent(-1*percent);
              backleftVex.SetPercent(percent);

              }
              frontrightVex.Stop();
              backleftVex.Stop();
      }
   void MoveDiagonalFrontLeft (int percent){
          double start_time=TimeNow();

              frontrightVex.SetPercent(-1*percent);
              backleftVex.SetPercent(percent);

              frontrightVex.Stop();
              backleftVex.Stop();
      }

   void MoveDiagonalFrontRight (int percent, double time){
          double start_time=TimeNow();
          while((TimeNow()-start_time)<time)
          {
              frontleftVex.SetPercent(percent);
              backrightVex.SetPercent(-1*percent);

              }
              frontrightVex.Stop();
              backleftVex.Stop();
      }

   void MoveDiagonalFrontRight (int percent){
          double start_time=TimeNow();

              frontleftVex.SetPercent(percent);
              backrightVex.SetPercent(-1*percent);


              frontrightVex.Stop();
              backleftVex.Stop();
      }

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

   void Forward(int percent)
   {
       double start_time=TimeNow();

       backrightVex.SetPercent(percent);
       backleftVex.SetPercent(-1*percent);
       frontrightVex.SetPercent(percent);
       frontleftVex.SetPercent(-1*percent);

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

   void Left(int percent, double time)
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
       frontrightVex.SetPercent(percent);
       frontleftVex.SetPercent(percent);
       }
       backrightVex.Stop();

       frontrightVex.Stop();
       frontleftVex.Stop();
       backleftVex.Stop();
   }

   void FollowLine()
   {
       bool online;
         int x=5,position;

         while(x==5)
         {

             if(leftopto.Value()>0 && leftopto.Value()<2)
             {
                 position=1;
             }

             else if(rightopto.Value()>0 && rightopto.Value()<2)
             {
                 position=3;
             }
             else if(middleopto.Value()>0 && middleopto.Value()<2)
             {
                 position=2;
             }

             switch(position)
             {
                 case(1):
                    MoveDiagonalFrontLeft(10);
                 break;
                 case(2):
                    MoveDiagonalFrontRight(10);
                 break;
                 case(3):
                    Forward(10);
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

   void ToButton()
   {
   LCD.WriteLine(CdS_cell.Value());
   Forward(30, 2.0);
   LCD.WriteLine(CdS_cell.Value());
   Left(30, 2.05);
   LCD.WriteLine(CdS_cell.Value());
   Sleep(3.0);


   }

int main(void)
{
    int x=5;
    FollowLine();
    //ToButton();
    /*
    if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
    {
     LCD.WriteLine("!!!");
     FlipJack();
    }
*/




    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );


    return 0;
}
