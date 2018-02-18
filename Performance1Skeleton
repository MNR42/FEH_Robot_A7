#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>

   AnalogInputPin CdS_cell(FEHIO::P2_0);
   DigitalInputPin frontright(FEHIO::P1_0);
   DigitalInputPin frontleft(FEHIO::P1_2);
   DigitalInputPin backright(FEHIO::P1_1);
   DigitalInputPin backleft(FEHIO::P1_3);
   FEHServo servo(FEHServo::Servo0);
   FEHMotor right_motor (FEHMotor::Motor0,9.0);
   FEHMotor left_motor (FEHMotor::Motor1,9.0);
   AnalogInputPin rightopto(FEHIO::P2_0);
   AnalogInputPin middleopto(FEHIO::P2_1);
   AnalogInputPin leftopto(FEHIO::P2_2);

   void Forward(int percent, double distance)
   {
       /*
       math for driving forward
       */
   }

   void Reverse(int percent, double distance)
   {
       /*
       math for driving backwards
       */
   }

   void Left(int percent, double distance)
   {
       /*
       math for driving sideways
       */
   }

   void Right(int percent, double distance)
   {
       /*
       math for driving sideways
       */
   }

   void FoolowLine(double distance)
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
                     right_motor.SetPercent(15);
                     left_motor.SetPercent(5);
                 break;
                 case(2):
                     right_motor.SetPercent(5);
                     left_motor.SetPercent(15);
                 break;
                 case(3):
                     right_motor.SetPercent(15);
                     left_motor.SetPercent(15);
                 break;
             default:
                 LCD.WriteLine("???");

             }


   }

   void FlipJack()
   {

   }

int main(void)
{
    if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
    {
        FlipJack();
    }

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
