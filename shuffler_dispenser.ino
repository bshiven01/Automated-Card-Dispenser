#include <Servo.h>  
#include <Stepper.h>
using namespace std;
Servo myservo_1; 
Servo myservo_2;



const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper_1(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper_2(stepsPerRevolution, 4, 5, 6, 7);



int t_tow=500;            // Time to move tower from one level to another
int t_card=500;           // Time to move one card from deck to tower
// int card_no=1;            
// int batch=13;              // Cards per slot in each shift of tower
// int pos=0;
// int max_cards=10;         // deck size
// int servo_time=2;         // time taken by servo to throw card
// int dis_time=50;
// int angle=90;             // Servo angle rotation for throwing card
float levels[] = {1,2,4,3,1};     // Random level choice
float teeth_per_rev = 10;    // Teeth of timing belt per revolution of stepper motor
float teeth_per_mm = 1.0/6.0;      // Teeth per mm on timing belt
float storey_height = 8;           // Height of one level in the tower in millimeter
float steps_per_level = storey_height * teeth_per_mm / teeth_per_rev * stepsPerRevolution;
float planet = 15;
float ring = 70; 
float gr = ring / planet;

float shift_revolution = 0;

void setup() {
  // put your setup code here, to run once:
  myservo_1.attach(2);      // attach the signal pin of servo to pin 9 of arduino
  myservo_2.attach(3);      // attach the signal pin of servo to pin 10 of arduino
  Serial.begin(9600);
  // set the speed at 60 rpm:
  myStepper_1.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //randomly filling tower
  for(int i = 1; i <= 4; i++)
  {
    float levels_to_move = levels[i] - levels[i-1];
    float steps_to_move = levels_to_move * steps_per_level;
    myStepper_1.step(steps_to_move);


    for(int j = 0; j < 13; j++)
    {
      for (float pos = 0; pos <= 90; pos += 1) { 
        myservo_1.write(pos);                      // tell servo to go to position in variable 'pos'
        // delay(1);                       // wait for the servo to reach the position
      }
    }

  }
  delay(10);

  //emptying tower
    for(int i = 1; i <= 4; i++)
  {
    for (float pos = 0; pos <= 180; pos += 1) { 
        myservo_2.write(pos);                      // tell servo to go to position in variable 'pos'
        // delay(1);                       // wait for the servo to reach the position
      }
    for (float pos = 180; pos >= 0; pos -= 1) { 
        myservo_2.write(pos);                      // tell servo to go to position in variable 'pos'
        // delay(1);                       // wait for the servo to reach the position
      }
      delay(10);
    float levels_to_move = 1;
    float steps_to_move = levels_to_move * steps_per_level;
    myStepper_1.step(steps_to_move);    
    

  }
  //back to level 1
  float steps_to_move = (-3) * steps_per_level;
  myStepper_1.step(steps_to_move);    


  // Dealing cards to 4 players

  for(int i = 1; i <= 52; i++)
  {
    steps_to_move = gr / 4 * 200;
    myStepper_2.step(steps_to_move); 

    for (float pos = 0; pos <= 90; pos += 1) 
    { 
      myservo_1.write(pos);
    }

  }





}
