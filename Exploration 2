#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHLCD.h>

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);
AnalogInputPin rightopto(FEHIO::P2_0);
AnalogInputPin middleopto(FEHIO::P2_1);
AnalogInputPin leftopto(FEHIO::P2_2);

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


void move_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(0);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}
int main(void)
{
    /*
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

    }*/



    int motor_percent = 20; //Input power level here
    int expected_counts = 40;
    int rev=318;//Input theoretical counts here

    float x, y; //for touch screen

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("Shaft Encoder Exploration Test");
    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    move_forward(motor_percent, expected_counts*14);


    move_left(20,(rev*1.5)/2);
    move_forward(motor_percent, expected_counts*10);
    move_right(20,(rev*1.5)/2);
    move_forward(motor_percent, expected_counts*4);
    //see function

    //Sleep(2.0); //Wait for counts to stabilize
    //Print out data
    //LCD.Write("Theoretical Counts: ");
    LCD.WriteLine(expected_counts);
    LCD.Write("Motor Percent: ");
    LCD.WriteLine(motor_percent);
    LCD.Write("Actual LE Counts: ");
    LCD.WriteLine(left_encoder.Counts());
    LCD.Write("Actual RE Counts: ");
    LCD.WriteLine(right_encoder.Counts());

    return 0;
}
