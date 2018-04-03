
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHRPS.h>
#include <time.h>


/*
 * Initialize motors, sensors, and servos
 */
    AnalogInputPin CdS_cell(FEHIO::P0_0);

    FEHServo servo(FEHServo::Servo0);
     #define min 500
     #define max 2432

    FEHMotor frontrightVex (FEHMotor::Motor3,7.2);
    FEHMotor frontleftVex (FEHMotor::Motor2,7.2);
    FEHMotor backrightVex (FEHMotor::Motor1,7.2);
    FEHMotor backleftVex (FEHMotor::Motor0,7.2);

    AnalogInputPin opto(FEHIO::P1_0);

    DigitalInputPin microswitch_arm(FEHIO::P2_0);

/*
 * Initialize RPS
 */
    void InitializeTouchMenu();
    void InitializeMenu();
    float X();
    float Y();
    float Heading();
    int Time();
    unsigned char CurrentCourse();
    char CurrentRegionLetter();
    int CurrentRegion();

/*
 * Turning fuctions
 */
    void turnRight90()
    {

        double start_time=TimeNow();
        while((TimeNow()-start_time)<2.0)
        {

        frontrightVex.SetPercent(30);
        backrightVex.SetPercent(30);
        frontleftVex.SetPercent(30);
        backleftVex.SetPercent(30);

        }
        frontrightVex.Stop();
        backleftVex.Stop();
        backrightVex.Stop();
        frontleftVex.Stop();
    }

    void turnLeft90()
    {
        double start_time=TimeNow();
        while((TimeNow()-start_time)<2.0)
        {
        frontleftVex.SetPercent(-30);
        frontrightVex.SetPercent(-30);
        backrightVex.SetPercent(-30);
        backleftVex.SetPercent(-30);

        }
        frontrightVex.Stop();
        frontleftVex.Stop();
        backrightVex.Stop();
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
        backrightVex.Stop();
        frontleftVex.Stop();
    }

    void turnLeft(double time)
    {
        double start_time=TimeNow();
        while((TimeNow()-start_time)<time)
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

/*
 * Move in straight line functions
 */
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

/*
 *Overloaded move in straight line fuctions
 */
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

/*
 * Digonal Functions
 */
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

/*
 * Overloaded Digonal functions
 */
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

/*
 * Check RPS
 */
    void CheckRPS(double correctD) {
        //Initialize variables
        double time = 4.0;
        double start_time = 0;

        //Print correct direction/position
        LCD.Clear();
        LCD.WriteLine("Correct position: (x, y, angle)");
        //LCD.WriteLine(correctX);
        //LCD.WriteLine(correctY);
        LCD.WriteLine(correctD);

        //Check direction
        if (RPS.Heading() < correctD) {
            start_time = TimeNow();
            while (RPS.Heading() < correctD || (TimeNow()-start_time)<time) {
                turnLeft(.3);
                Sleep(0.4);
            }
        }
        if (RPS.Heading() > correctD || (TimeNow()-start_time)<time) {
            start_time = TimeNow();
            while (RPS.Heading() > correctD) {
                turnRight(.3);
                Sleep(0.4);
            }
        }

        //Check X

        //Check Y
    }

/*
 * Pick up wrench
 */
    void PickUpWrench() {
        servo.SetDegree(80);
        while (microswitch_arm.Value() == 1){
            Reverse(15, .1);
        }
        servo.SetDegree(77);
        Sleep(1.0);
        servo.SetDegree(180);

    }

/*
 * Spin the wheel
 */
   void SpinWheel() {
       int fuel = RPS.FuelType(); //1 clockwise, 2 counter-clockwise
       int i = 65;
       int i2 = 50;


       //Turn crank
       if (fuel == 1){
           MoveLeft(20, 1.2);
           //servo.SetDegree(i);
           //Sleep(.5);
           MoveRight(20, .6);
           servo.SetDegree(i2);
           MoveRight(20, 2.0);
           Forward(30, 1.4);
       } else if (fuel == 2) {
           MoveRight(20, 1.5);
           //servo.SetDegree(i);
           //Sleep(.5);
           MoveLeft(20, .6);
           servo.SetDegree(i2);
           MoveLeft(20, 2.0);
           Forward(30, 1.4);
       }
       servo.SetDegree(180);
   }


/*
 * Read Light and move accoordingly function
 */
    void PushButton(){
        int color;
        LCD.WriteLine(CdS_cell.Value());
        if (CdS_cell.Value() <.6) {  //Red Light
            LCD.WriteLine("Light is RED");
            MoveRight(30, .7);
            Forward(30, .7);
            Reverse(30, .6);
            MoveLeft(30, 2.4);
            MoveRight(30, .8);
            Forward(30, .3);
        } else if(CdS_cell.Value()>.6 && CdS_cell.Value()<3.3) { //Blue light
            LCD.WriteLine("Light is BLUE");
            MoveLeft(30, .6);
            Forward(30, 1.0);
            Reverse(30, .6);
            MoveLeft(26, .9);
            MoveRight(30, .8);
            Forward(30, .2);
        } else {
            LCD.WriteLine("Button Light not Read");
            MoveLeft(30, 1.6);
            MoveRight(30, .7);
            Forward(30, .2);
        }
    }

/*
 * Position function
 */
    void StartRPSPoition () {
         bool check = true;
         double correctX = 17.2;
         double correctY = 28.6;
         double correctD = 90;

         if(RPS.CurrentRegion() == 6) {
             correctY = 28.0;
         }

         LCD.WriteLine("Correct position:");
         LCD.WriteLine(correctX);
         LCD.WriteLine(correctY);
         LCD.WriteLine("-------------");

         while (check) {
             LCD.WriteRC(RPS.X(), 2, 12);
             LCD.WriteRC(RPS.Y(), 3, 12);
             LCD.WriteRC(RPS.Heading(), 4, 12);
             if (RPS.X() < (correctX + .2) && RPS.X() > (correctX - .2)) {
                 if (RPS.Y() < (correctY + .2) && RPS.Y() > (correctY - .2)) {
                     if (RPS.Heading() < (correctD + .5) && RPS.Heading() > (correctD - .5)) {
                         LCD.WriteLine("The robot is in the correct position :)");
                         check = false;
                     }
                 }
             }
             Sleep(3.0);
         }
     }

/*
 * Find Line Function
 */
    void FindLine() {
        while (opto.Value() <= 3.0){
            MoveLeft(20, .2);
        }
    }

/*
 * Individual Compition Function
 */
    int IndComp(){
        //Clear Screen
        LCD.Clear();

        //Get to the button, read the button light,
            Forward(26, 2.1);
            //CheckRPS(90);
            MoveLeft(30, 1.8);
            Sleep(1.5);
            PushButton();

        //Get to and flip the car jack
            MoveRight(30, 2.1);
            turnLeft90();
            MoveRight(30, .3);
            Reverse(30, .2);
            MoveDiagonalBackRight(40, 4.3);
            MoveRight(30, 1.0);
            Reverse(26, .6);
            MoveRight(30, .3);
            MoveLeft(30, .2);
            Forward(30, 1.6);
            Reverse(30, .3);
            MoveRight(30, .5);

        //Move to and pick up wrench
            MoveLeft(30, 1.0);
            MoveDiagonalFrontLeft(30, .8);
            FindLine();
            Forward(20, .9);
            MoveRight(15, .5);
            PickUpWrench();

        //Move to garage and deposite wrench
            //Get up slope
            Forward(30, .6);
            turnRight90();
            Reverse(30,1.5);
            MoveRight(30,3.0);
            MoveLeft(30, .15);
            Reverse(40,3.0);
            turnRight(1.2);
            MoveDiagonalBackRight(50,3.5);
            turnLeft(1.2);
            MoveRight(30,1.8);
            MoveLeft(30,.3);

            //Get to Garage
            Reverse(30, 2.4);
            turnLeft(1.2);
            MoveLeft(30, 1.5);
            Reverse(30, 1.5);
            Forward(30, .4);
            FindLine();
            MoveRight(30, .3);

            //Drop off Wrench
            servo.SetDegree(110);
            servo.SetDegree(100);
            Reverse(30, 1.5);
            servo.SetDegree(75);
            while(microswitch_arm.Value() == 0){
                servo.SetDegree(100);
                Reverse(30, 1.5);
                if (microswitch_arm.Value() == 0){
                    servo.SetDegree(75);
                }
                Forward(30, .8);
            }
            servo.SetDegree(180);

        //Realign with the line
            Forward(30, .2);
            MoveRight(30, .5);
            FindLine();
            Reverse(30, .4);

        //Move to and turn crank
            //Move to crank
            Forward(40, .6);
            turnRight(2.2);
            MoveLeft(30, 1.0);
            Reverse(30, 2.2);

            //Turn crank
            SpinWheel();

        //Move to and push final button
            Forward(30, 1.4);
            turnRight90();
            Reverse(30, 3.8);
            turnRight(1.2);
            MoveRight(30, 1.5);
            MoveLeft(30, .2);
            Reverse(30, 4.5);
            MoveRight(30, 1.5);
            Forward(30, .2);
            MoveLeft(30, 2.8);
            Forward(30, 8.0);

    }

/*
 * Main function
 */
    int main(void)
    {
        //Clear Screen
        LCD.Clear();

        //Initialize Servo
        servo.SetDegree(180);

        //Initialize the RPS
        RPS.InitializeTouchMenu();

        //CheckRPSPoition(16.9, 28.6, 90);
        StartRPSPoition();

        //Call function when Robot sees the light
        int x=5;
        while(x==5)
        {
        if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
        {
         LCD.WriteLine(CdS_cell.Value());
         LCD.WriteLine("Read Light");
         IndComp();
         x=6;
         LCD.Clear();
         LCD.WriteLine("Finished");
        }

        }
        return 0;
    }
