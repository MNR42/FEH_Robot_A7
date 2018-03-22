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
#include <FEHRPS.h>

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

   AnalogInputPin rightopto(FEHIO::P1_0);
   AnalogInputPin middleopto(FEHIO::P1_2);
   AnalogInputPin leftopto(FEHIO::P1_4);

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
       while((TimeNow()-start_time)<2.2)
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
       while((TimeNow()-start_time)<2.2)
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
    *Overloaded Digonal functions
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
    * Line Following
    */
   void FollowLine(int time)
      {
            bool online;
            int x=5,position;
            double start_time=TimeNow();

            while(x==5)
            {

                LCD.WriteLine("Begin Line following");
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
                    LCD.WriteLine("End Line following");
                }
            }
      }

   void FindLine() {
       while (middleopto.Value() >= .4){
           MoveRight(20, .1);
       }
       MoveRight(30, .3);
   }

   /*
    * Pick up wrench
    */
   void PickUpWrench() {
       servo.SetDegree(82);
       while (microswitch_arm.Value() == 1){
           Reverse(20, .1);
       }
       servo.SetDegree(77);
       Sleep(1.0);
       servo.SetDegree(110);

   }

   /*
    * Pick up wrench
    */
   void SpinWheel() {
       int fuel = RPS.FuelType(); //1 clockwise, 2 counter-clockwise
       int i = 0;

       //Turn crank
       if (fuel == 1){
           MoveLeft(30, .5);
           for (i = 0; i < 70; i+10) {
               servo.SetDegree(i);
               Sleep(.2);
           }
           MoveRight(30, .2);
           Forward(30, .5);
       } else if (fuel == 2) {
           MoveRight(30, .5);
           for (i = 0; i < 70; i+10) {
               servo.SetDegree(i);
               Sleep(.2);
           }
           MoveLeft(30, .2);
           Forward(30, .5);
       }

   }


   /*
    * Read Light and move accoordingly function
    */
   int ReadLight(){
       int color;
       LCD.WriteLine(CdS_cell.Value());
       if (CdS_cell.Value() <1) {  //Red Light
           MoveRight(30, .6);
           color = 0;
       } else if(CdS_cell.Value()>1 && CdS_cell.Value()<2.5) { //Blue light
           MoveLeft(30, .6);
           color = 1;
       } else {
           LCD.WriteLine("???");
       }
       return color; //0 = red ; 1 = blue
   }

   /*
    * Preformance test Functions
    */
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

   void PT3() {
       //Initailize servo
       servo.SetMin(min);
       servo.SetMax(max);
       servo.SetDegree(180);

       //Get to the left of line
       Forward(30, 1.75);
       turnLeft90();
       Reverse(30, 1.0);

       //Find line
       MoveRight(30, 1.0);

       //Pick up Wrench
       PickUpWrench();
       Forward(30, .5);
       turnRight90();

       //Get up slope
       Reverse(30, .6);
       MoveDiagonalBackRight(30, 2.0);
       MoveLeft(30, .2);
       Reverse(70, 2.5);
       turnRight(1.2);
       MoveDiagonalBackRight(40, 1.5);
       turnLeft(.5);
       MoveRight(30, 2.0);

       //Get to Garage
       MoveDiagonalBackLeft(30, 7.0);
       turnLeft(1.2);

       //Drop off Wrench
       servo.SetDegree(100);
       Reverse(30, 4.0);
       if (microswitch_arm.Value() == 0){
           servo.SetDegree(75);
       }
       Forward(30, .8);
       servo.SetDegree(180);

       //Hit the crank
       MoveLeft(30, 2.0);
       MoveDiagonalFrontLeft(30, 3.0);
       MoveLeft(30, 1.0);

       LCD.WriteLine("END :)");

   }

   void PT4 () {
       //Move to hill

       //Go up hill

       //Move to crank

       //Choose position

       //Move accordingly

       //Go back to lower level
   }

   /*
    * Position function
    */
   void StartRPSPoition () {
       bool check = true;
       double correctX = 16.9;
       double correctY = 28.6;
       double correctD = 90;

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
                   if (RPS.Heading() < (correctD + .2) && RPS.Heading() > (correctD - .2)) {
                       LCD.WriteLine("The robot is in the correct position :)");
                       check = false;
                   }
               }
           }
           Sleep(3.0);
       }
   }

   //Note* This function does not take into account feild elements
   void checkRPSPoition (double correctX, double correctY, double correctD) {
       bool checkX = false;
       bool checkY = false;
       bool checkD = false;
       double time = 2.0;
       double start_time = 0;

       LCD.WriteLine("Correct position:");
       LCD.WriteLine(correctX);
       LCD.WriteLine(correctY);
       LCD.WriteLine(correctD);


       //Heading
       while(!((RPS.Heading() < (correctD + .5)) && (RPS.Heading() > (correctD - .5))) &&
             !((RPS.X() < (correctX + .1)) && (RPS.X() > (correctX - .1))) &&
             !((RPS.Y() < (correctY + .1)) && (RPS.Y() > (correctY - .1)))
             ) {
           if (RPS.Heading() < correctD) {
               start_time = TimeNow();
               while (RPS.Heading() < correctD || (TimeNow()-start_time)<time) {
                   turnLeft(.1);
               }
           }
           if (RPS.Heading() > correctD || (TimeNow()-start_time)<time) {
               start_time = TimeNow();
               while (RPS.Heading() > correctD) {
                   turnRight(.1);
               }
           }
       LCD.WriteLine("Correct Heading Found");

       //Fix X and Y if facing 0 degrees
       if(RPS.Heading() < 1 && RPS.Heading() > 359){
           if (RPS.X() < (correctX + .1)) {
               while (RPS.X() < (correctX + .1)) {
                   MoveRight(20, .1);
                   Sleep(.5);
               }
           }
           if (RPS.X() > (correctX + .1)) {
               while (RPS.X() > (correctX + .1)) {
                   MoveLeft(20, .1);
                   Sleep(.5);
               }
           }
           if (RPS.Y() < (correctY - .1)) {
               while (RPS.X() < (correctY + .1)) {
                   Reverse(20, .1);
                   Sleep(.5);
               }
           }
           if (RPS.Y() > (correctY - .1)) {
               while (RPS.X() > (correctY + .1)) {
                   Forward(20, .1);
                   Sleep(.5);
               }
           }
       }

       //Fix X and Y if facing 90 degrees
       if(RPS.Heading() < 91 && RPS.Heading() > 89){
           LCD.WriteLine("Heading 90 degrees");
           if (RPS.X() < (correctX + .1)) {
               start_time = TimeNow();
               while (RPS.X() < correctX || (TimeNow()-start_time)<time) {
                   Forward(20, .1);
                   LCD.WriteRC(RPS.X(), 2, 12);
                   LCD.WriteRC(RPS.Y(), 3, 12);
               }
           }
           if (RPS.X() > correctX) {
               start_time = TimeNow();
               while (RPS.X() > correctX || (TimeNow()-start_time)<time) {
                   Reverse(20, .1);
                   LCD.WriteRC(RPS.X(), 2, 12);
                   LCD.WriteRC(RPS.Y(), 3, 12);
               }
           }
           if (RPS.Y() < correctY) {
               start_time = TimeNow();
               while (RPS.Y() < (correctY + .1)  || (TimeNow()-start_time)<time) {
                   MoveLeft(20, .1);
                   LCD.WriteRC(RPS.X(), 2, 12);
                   LCD.WriteRC(RPS.Y(), 3, 12);
               }
           }
           if (RPS.Y() > correctY) {
               start_time = TimeNow();
               while (RPS.Y() > correctY  || (TimeNow()-start_time)<time) {
                   MoveRight(20, .1);
                   LCD.WriteRC(RPS.X(), 2, 12);
                   LCD.WriteRC(RPS.Y(), 3, 12);
               }
           }
       }

       //Fix X and Y if facing 180 degrees
       if(RPS.Heading() < 179 && RPS.Heading() > 181) {
           if (RPS.X() < (correctX + .1)) {
               while (RPS.X() < (correctX + .1)) {
                   MoveLeft(20, .01);
                   Sleep(.5);
               }
           }
           if (RPS.X() > (correctX + .1)) {
               while (RPS.X() > (correctX + .1)) {
                   MoveRight(20, .01);
                   Sleep(.5);
               }
           }
           if (RPS.Y() < (correctY - .1)) {
               while (RPS.X() < (correctY + .1)) {
                   Forward(20, .01);
                   Sleep(.5);
               }
           }
           if (RPS.Y() > (correctY - .1)) {
               while (RPS.X() > (correctY + .1)) {
                   Reverse(20, .01);
                   Sleep(.5);
               }
           }
       }

       //Fix X and Y if facing 270 degrees
       if(RPS.Heading() < 271 && RPS.Heading() > 269) {
           if (RPS.X() < (correctX + .1)) {
               while (RPS.X() < (correctX + .1)) {
                   Reverse(20, .01);
                   Sleep(.5);
               }
           }
           if (RPS.X() > (correctX + .1)) {
               while (RPS.X() > (correctX + .1)) {
                   Forward(20, .01);
                   Sleep(.5);
               }
           }
           if (RPS.Y() < (correctY - .1)) {
               while (RPS.X() < (correctY + .1)) {
                   MoveRight(20, .01);
                   Sleep(.5);
               }
           }
           if (RPS.Y() > (correctY - .1)) {
               while (RPS.X() > (correctY + .1)) {
                   MoveLeft(20, .01);
                   Sleep(.5);
               }
           }
       }
   }
       LCD.WriteLine("Finished");
   }

   /*
    * Debugging functions
    */
   void ReadValue(){
       int x=5;
       while(x==5){
       LCD.WriteLine(CdS_cell.Value());
       Sleep(1.0);
       }
   }



int main(void)
{
    //initialize the RPS
    RPS.InitializeTouchMenu();

    checkRPSPoition(16.9, 28.6, 90);
    //StartRPSPoition ();

    //Call function when Robot sees the light
    int x=5;
    while(x==5)
    {
    if(CdS_cell.Value()>.2 && CdS_cell.Value()<.6)
    {
     LCD.WriteLine(CdS_cell.Value());
     LCD.WriteLine("!!!");
     PT3();
     x=6;
    }

    }
    return 0;
}
