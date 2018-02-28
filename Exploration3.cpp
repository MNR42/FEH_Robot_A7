#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHLCD.h>
#include<FEHSD.h>

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);
AnalogInputPin rightopto(FEHIO::P2_0);
AnalogInputPin middleopto(FEHIO::P2_1);
AnalogInputPin leftopto(FEHIO::P2_2);


void move_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(0);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}


void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(0);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

int main(void)
{
    int rev=318;
    int x=5;
    int motor_percent = 20;
    int expected_counts = 40;
    float touch_x, touch_y;

    float XPosition,YPosition,Heading;
    RPS.InitializeTouchMenu();



    //Call this function to initialize the RPS to a course



    //Wait for touchscreen to be pressed
    LCD.WriteLine("Press Screen to Start");
    while(!LCD.Touch(&touch_x, &touch_y));


    LCD.Clear();
    SD.OpenLog();

    //Write initial screen info
   LCD.WriteRC("RPS Test Program",0,0);
   LCD.WriteRC("X Position:",2,0);
   LCD.WriteRC("Y Position:",3,0);
   LCD.WriteRC("   Heading:",4,0);

   LCD.WriteRC(" Fuel Type:",6,0);


       LCD.WriteRC(RPS.X(),2,12); //update the x coordinate
       LCD.WriteRC(RPS.Y(),3,12); //update the y coordinate
       LCD.WriteRC(RPS.Heading(),4,12); //update the heading
       LCD.WriteRC(RPS.FuelType(),6,12);

       XPosition=RPS.X();
       YPosition=RPS.Y();
       Heading=RPS.Heading();
       SD.Printf("FLOAT:%f,FLOAT:%f,FLOAT:%f\n",XPosition,YPosition,Heading);


       move_forward(motor_percent, expected_counts*9);

       LCD.WriteRC(RPS.X(),2,12); //update the x coordinate
       LCD.WriteRC(RPS.Y(),3,12); //update the y coordinate
       LCD.WriteRC(RPS.Heading(),4,12); //update the heading
       LCD.WriteRC(RPS.FuelType(),6,12);


       XPosition=RPS.X();
       YPosition=RPS.Y();
       Heading=RPS.Heading();
       SD.Printf("FLOAT:%f,FLOAT:%f,FLOAT:%f\n",XPosition,YPosition,Heading);



       move_left(20,(rev*1.35)/2);
      // move_forward(motor_percent, expected_counts*8);

       LCD.WriteRC(RPS.X(),2,12); //update the x coordinate
       LCD.WriteRC(RPS.Y(),3,12); //update the y coordinate
       LCD.WriteRC(RPS.Heading(),4,12); //update the heading
       LCD.WriteRC(RPS.FuelType(),6,12);


       XPosition=RPS.X();
       YPosition=RPS.Y();
       Heading=RPS.Heading();
       SD.Printf("FLOAT:%f,FLOAT:%f,FLOAT:%f\n",XPosition,YPosition,Heading);



       move_left(20,(rev*1.35)/2);
       move_forward(motor_percent, expected_counts*3);



       x=6; //wait for a 10ms to avoid updating the screen too quickly


    //we will never get here because of the infinite while loop
    return 0;
}
