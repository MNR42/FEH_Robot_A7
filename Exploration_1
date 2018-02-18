#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>

void bothforward(double percent)
{

}

int main(void)
{

    AnalogInputPin CdS_cell(FEHIO::P2_0);
    DigitalInputPin frontright(FEHIO::P1_0);
    DigitalInputPin frontleft(FEHIO::P1_2);
    DigitalInputPin backright(FEHIO::P1_1);
    DigitalInputPin backleft(FEHIO::P1_3);
    FEHServo servo(FEHServo::Servo0);
    FEHMotor right_motor (FEHMotor::Motor0,9.0);
    FEHMotor left_motor (FEHMotor::Motor1,9.0);
    int x=5;

    //Part 1
    /*
    while(x=5)
    {
        LCD.WriteLine(CdS_cell.Value());
        Sleep(2.0);
    }*/

    //Part 2
    //servo.TouchCalibrate();

    servo.SetMin(500);
    servo.SetMax(2412);

    /*
    while(x=5)
    {
        if((CdS_cell.Value()>0 && CdS_cell.Value()<1))
        {
           servo.SetDegree(180);
           Sleep(1.0);
        }
        else
        {
            servo.SetDegree(0);
        }
    }*/

    //part 3

    while(x==5)
    {
        right_motor.SetPercent(30);
        left_motor.SetPercent(30);
        if(frontright.Value()==0 || frontleft.Value()==0)
        {
            left_motor.Stop();
            right_motor.Stop();
            x=4;
        }

    }
    while(x==4)
    {
        left_motor.SetPercent(-30);
        if(backleft.Value()==0)
        {
            left_motor.Stop();
            x=5;
        }


    }
    while(x==5)
    {
        right_motor.SetPercent(-30);
        if(backright.Value()==0)
        {
            right_motor.Stop();
            x=4;
        }


    }

    while(x==4)
    {
        right_motor.SetPercent(30);
        left_motor.SetPercent(30);
        if(frontright.Value()==0 || frontleft.Value()==0)
        {
            left_motor.Stop();
            right_motor.Stop();
            x=5;
        }

    }

    while(x==5)
    {
        right_motor.SetPercent(-30);
        if(backright.Value()==0)
        {
            right_motor.Stop();
            x=4;
        }


    }

    while(x==4)
    {
        left_motor.SetPercent(-30);
        if(backleft.Value()==0)
        {
            left_motor.Stop();
            x=5;
        }


    }

    while(x==5)
    {
        right_motor.SetPercent(30);
        left_motor.SetPercent(30);
        if(frontright.Value()==0 || frontleft.Value()==0)
        {
            left_motor.Stop();
            right_motor.Stop();
            x=4;
        }

    }

    return 0;
}
