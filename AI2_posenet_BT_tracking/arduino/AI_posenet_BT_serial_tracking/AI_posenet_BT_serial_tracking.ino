#include <SoftwareSerial.h>
#include<Wire.h>
#include<Servo.h>
/*
1 2 3
4 5 6
7 8 9
*/
//SoftwareSerial I2CBT(10,11);//定義PIN10及PIN11分別為RX及TX腳位
//因為 pin 10,11為pwm腳位在此程式裡有使用pwm(Server.h)會造成 RX TX 亂碼,所以改用 pin 2,4
SoftwareSerial I2CBT(2,4);//定義D2及D4分別為RX及TX腳位
int LED = 13;
int LED1 = 7;
int LED2 = 8;

#define SLAVE_ADDR 0x04
#define left '4'
#define right '6'
#define up '2'
#define down '8'
#define FIRE '5'

#define A 'a'
#define B 'b'
#define C 'c'
#define D 'd'
#define E 'e'
#define F 'f'
#define G 'g'
#define H 'h'
#define I 'i'

#define J 'j'
#define K 'k'
#define L 'l'
#define M 'm'
#define N 'n'
#define O 'o'
#define P 'p'
#define Q 'q'
#define R 'r'


String readwords;


Servo servo_h;
Servo servo_v;
Servo servo_f;

static int pos_h=90;
static int pos_v=90;
static int pos_f=90;



void setup()
{
	Serial.begin(9600);           // start serial for output
        I2CBT.begin(9600);      //bluetooth baud rate
        pinMode(LED, OUTPUT);
        pinMode(7, OUTPUT);  //設定 pin7 為輸出，LED1就接在這（開門）
        pinMode(8, OUTPUT);  //設定 pin8 為輸出，LED2就接在這（關門）
	servo_h.attach(9);			//horizen at 9
	servo_v.attach(10);			//vertical at 10
        servo_f.attach(11);
	servo_h.write(pos_h);
        servo_v.write(pos_v);
        servo_f.write(pos_f);
        
}
void(* resetFunc) (void) = 0;//declare reset function at address 0
void loop()
{
        
        while(Serial.available())  receiveEvent();       
        while(I2CBT.available()) bluetooth(); 
        BT_readwords();
        
           
}

void receiveEvent()
{
	int x = Serial.read();    // receive byte as an integer
	Serial.println(x);         // print the integer

        if(x==A) pos_h =110;
        if(x==B) pos_h =105;
        if(x==C) pos_h =100;
        if(x==D) pos_h =95;
        if(x==E) pos_h =90;
        if(x==F) pos_h =85;
        if(x==G) pos_h =80;
        if(x==H) pos_h =75;
        if(x==I) pos_h =70;
        
        if(x==R) pos_v =90;
        if(x==Q) pos_v =86;
        if(x==P) pos_v =82;
        if(x==O) pos_v =78;
        if(x==N) pos_v =74;
        if(x==M) pos_v =70;
        if(x==L) pos_v =66;
        if(x==K) pos_v =62;
        if(x==J) pos_v =58;
        //must used 2nd arduino board to control FIRE, or pos_h and pos_v will delay
        if(x==FIRE) fire();
        
// /* face tracking and keyboard command
        if(x==up && pos_v<=175) pos_v --;
	if(x==down && pos_v>=5) pos_v ++;
	if(x==left && pos_h>=5) pos_h ++;
	if(x==right && pos_h<=175) pos_h --;
//*/ 
        

 //       pos_h=x;
	servo_h.write(pos_h);
	servo_v.write(pos_v);
        
}

void bluetooth()
{
  delay(10); //Delay added to make thing stable
  char c = I2CBT.read(); //Conduct a serial read
  readwords += c; //build the string- "passward", "d", "e" and "f"
  
}

void BT_readwords()
{
   if (readwords.length() > 0) {
           Serial.println(readwords);
           if (readwords == "aabc") {
      
                         digitalWrite(LED, HIGH);
                         delay(300);
                  }
           else if (readwords == "bbac") 
                  {        //    passwd:"bbac"    
          
                         digitalWrite(LED, LOW);   //熄滅LED
                         delay(300);  
                  }   
           if(readwords=="A") pos_h =110;
           if(readwords=="B") pos_h =105;
           if(readwords=="C") pos_h =100;
           if(readwords=="D") pos_h =95;
           if(readwords=="E") pos_h =90;
           if(readwords=="F") pos_h =85;
           if(readwords=="G") pos_h =80;
           if(readwords=="H") pos_h =75;
           if(readwords=="I") pos_h =70;
        
           if(readwords=="R") pos_v =90;
           if(readwords=="Q") pos_v =86;
           if(readwords=="P") pos_v =82;
           if(readwords=="O") pos_v =78;
           if(readwords=="N") pos_v =74;
           if(readwords=="M") pos_v =70;
           if(readwords=="L") pos_v =66;
           if(readwords=="K") pos_v =62;
           if(readwords=="J") pos_v =58;
           //must used 2nd arduino board to control FIRE, or pos_h and pos_v will delay
           if(readwords=="FIRE") fire();
        
// /* objects tracking and keyboard command
           if(readwords=="2" && pos_v<=175) pos_v --;
           if(readwords=="8" && pos_v>=5) pos_v ++;
           if(readwords=="4" && pos_h>=5) pos_h ++;
           if(readwords=="6" && pos_h<=175) pos_h --;
//*/ 
        

 //        pos_h=readwords;
           servo_h.write(pos_h);
           servo_v.write(pos_v);       
                      
           readwords="";
           }  
}
//*
void fire()
{
  for(pos_f = 30; pos_f < 120; pos_f += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo_f.write(pos_f);              // tell servo to go to position in variable 'pos' 
    delay(2);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos_f = 120; pos_f>=31; pos_f-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo_f.write(pos_f);              // tell servo to go to position in variable 'pos' 
    delay(2);                       // waits 15ms for the servo to reach the position 
  } 
  
}
//*/
