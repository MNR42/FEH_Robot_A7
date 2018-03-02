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


   //Turning fuctions

   void turnRight90()
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

   void turnLeft90()
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

   void turnRight(double time)
   {

       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
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

   void turnLeft(double time)
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

   //Move in straight line functions

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

   //Overloaded move in straight line fuctions

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

   //Digonal Functions

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

   void MoveDiagonalBackLeft (int percent, double time){
       double start_time=TimeNow();
       while((TimeNow()-start_time)<time)
       {
           frontleftVex.SetPercent(-1*percent);
           backrightVex.SetPercent(percent);

           }
           frontrightVex.Stop();
           backleftVex.Stop();
   }

   //Overloaded Digonal functions

   void MoveDiagonalFrontLeft (int percent){
             double start_time=TimeNow();

                 frontrightVex.SetPercent(-1*percent);
                 backleftVex.SetPercent(percent);

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

   //Line Following

   void FollowLine(int time)
      {
            bool online;
            int x=5,position;
            double start_time=TimeNow();

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
                       MoveDiagonalFrontLeft(25);
                    break;
                    case(2):
                       MoveDiagonalFrontRight(25);
                    break;
                    case(3):
                       Forward(10);
                    break;
                default:
                    LCD.WriteLine("???");

                }
                if(TimeNow() - start_time >= time){
                    x=6;
                }
            }
      }

   //Read Light and move accoordingly function
   int ReadLight(){
       int color;
       LCD.WriteLine(CdS_cell.Value());
       if (CdS_cell.Value() <1) {
           MoveRight(30, .6);
           color = 0;
       } else if(CdS_cell.Value()>1 && CdS_cell.Value()<2.5) {
           MoveLeft(30, .6);
           color = 1;
       } else {
           LCD.WriteLine("???");
       }
       return color;
   }

   //Test Functions
   void FlipJack()
   {


    Forward(30,.545);
    MoveLeft(30,1.22);
    Forward(30,1.2);
    Reverse(30,1.2);
    MoveRight(30,3.22);
    Forward(30,2.9);
    turnLeft90();
    Forward(25,1.2);
    Reverse(25,1.2);
    MoveLeft(80,5.6);

   }

   void PT1()
   {
    MoveRight(30, 2.0);
    Reverse(30, 1.0);
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

   void PT2()
   {
       Forward(30, 2.0);
       MoveLeft(30, 2.1);
       LCD.WriteLine(CdS_cell.Value());
       int x = ReadLight();
       if (x==0) {
           LCD.WriteLine("This is red MAX");
       } else if (x==1){
           LCD.WriteLine("This is blue MAX");
       }
       Forward(30,1);
       Reverse(30, .5);
       MoveRight(30, 5.5);
       if (x == 0) {
           MoveLeft(30, .5);
           Forward(30, .3);
           MoveRight(30, .75);
           MoveLeft(30, .5);
           turnRight(.25);
           MoveLeft(30, 1.85);
       } else {
           MoveLeft(30, .5);
           turnRight(.3);
           MoveLeft(30, 1.5);
       }
       Reverse(30, 6);
   }

   void ReadValue(){
       int x=5;
       while(x==5){
       LCD.WriteLine(CdS_cell.Value());
       Sleep(1.0);
       }
   }

int main(void)
{
    //PT2();
    int x=5;
    while(x==5)
    {
    if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
    {
     LCD.WriteLine(CdS_cell.Value());
     LCD.WriteLine("!!!");
     PT2();
     x=6;
    }

    }
    return 0;
}
