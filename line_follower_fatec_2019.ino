const int esqExt = A0;               //sensores analógicos
const int esq = A1;
const int cen = A2;
const int dir = A3;
const int dirExt = A4;
int LFSensor[6] = {0, 0, 0, 0, 0};
  //int LFSensorPin[] = {3, 5, 6, 9, 10};
  //int LFSensorVals[6] = {0, 0, 0, 0, 0};
int valSensor0 = 0;
int valSensor1 = 0;
int valSensor2 = 0;
int valSensor3 = 0;
int valSensor4 = 0;
int erro = 0;
int erroanterior = 0;
float P;
float D;
float PD;
int para;
int rightMotorSpeed = 5;
int leftMotorSpeed = 6;
int val1 = 1; //<=500 == 1 == linha branca
int val2 = 0;
float I =0;
int sp = 550;

void setup() {
  pinMode(dirExt, INPUT);
  pinMode(dir, INPUT);
  pinMode(cen, INPUT);
  pinMode(esqExt, INPUT);
  pinMode(esq, INPUT);
  pinMode(leftMotorSpeed, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  valSensor0 = analogRead(esqExt);
  valSensor1 = analogRead(esq);
  valSensor2 = analogRead(cen);
  valSensor3 = analogRead(dir);
  valSensor4 = analogRead(dirExt);
  
  if(valSensor0 <= sp)
    {
      LFSensor [0] = val1;
    }
  if(valSensor1 <=sp)
    {
      LFSensor [1] = val1;
    }
  if(valSensor2 <=sp)
    {
      LFSensor [2] = val1;
    }
  if(valSensor3 <=sp)
    {
      LFSensor [3] = val1;
    }
  if(valSensor4 <=sp)
    {
      LFSensor [4] = val1;
    }  
  if(valSensor0 >=sp)
    {
      LFSensor [0] = val2;
    }
  if(valSensor1 >=sp)
    {
      LFSensor [1] = val2;
    }
  if(valSensor2 >=sp)
    {
      LFSensor [2] = val2;
    }
  if(valSensor3 >=sp)
    {
      LFSensor [3] = val2;
    }
  if(valSensor4 >=sp)
    {
      LFSensor [4] = val2;
    }
    if ((       LFSensor [0] == 1) && (LFSensor [1] == 1) && (LFSensor [2] == 1) && (LFSensor [3] == 1) && (LFSensor [4] == 1 ))
    {
      analogWrite(5,leftMotorSpeed);
      analogWrite(6,rightMotorSpeed);
      delay(700);                                                       
      para = 1;
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      delay(13000);
      }
       if ((       LFSensor [0] == 0) && (LFSensor [1] == 0) && (LFSensor [2] == 0) && (LFSensor [3] == 0) && (LFSensor [4] == 0 ))
    {
      

      para = 0;
      }
       
 

    if ((       LFSensor [0] == 0) && (LFSensor [1] == 0) && (LFSensor [2] == 0) && (LFSensor [3] == 0) && (LFSensor [4] == 1 ))
    {
      erro = 4;
      para = 0;
      }

if ((LFSensor [0] == 0) && (LFSensor [1] == 0) && (LFSensor [2] == 0) && (LFSensor [3] == 1) && (LFSensor [4] == 1))
    { 
      erro = 3;
      para = 0;
    }

if ((LFSensor [0] == 0) && (LFSensor [1] == 0) && (LFSensor [2] == 0) && (LFSensor [3] == 1) && (LFSensor [4] == 0)) 
{
  erro = 2;
  para = 0;
}

if ((LFSensor [0] == 0) && (LFSensor [1] == 0) && (LFSensor [2] == 1) && (LFSensor [3] == 1) && (LFSensor [4] == 0)) 
{
  erro = 1;
  para = 0;
}

if ((LFSensor [0] == 0) && (LFSensor [1] == 0) && (LFSensor [2] == 1) && (LFSensor [3] == 0) && (LFSensor [4] == 0)) 
{
  erro = 0;
  para = 0;
}

if ((LFSensor [0] == 0) && (LFSensor [1] == 1) && (LFSensor [2] == 1) && (LFSensor [3] == 0) && (LFSensor [4] == 0)) 
{
  erro = -1;
  para = 0;
}

if ((LFSensor [0] == 0) && (LFSensor [1] == 1) && (LFSensor [2] == 0) && (LFSensor [3] == 0) && (LFSensor [4] == 0)) 
{
  erro = -2;
  para = 0;
}

if ((LFSensor [0] == 1) && (LFSensor [1] == 1) && (LFSensor [2] == 0) && (LFSensor [3] == 0) && (LFSensor [4] == 0)) 
{
  erro = -3;
  para = 0;
}

if ((LFSensor [0] == 1) && (LFSensor [1] == 0) && (LFSensor [2] == 0) && (LFSensor [3] == 0) && (LFSensor [4] == 0)) 
{
  erro = -4;
  para = 0;
}
if(para == 1)
{
  
  leftMotorSpeed = 0;
    
   rightMotorSpeed = 0;
   delay(5000);
}
else
{
   P = erro;
   I=I+erro;
   D = erro - erroanterior;

   PD = (20 * P) + (I*0.08)+ (22 * D);

  erroanterior = erro;

   leftMotorSpeed = 100 - PD;
    
   rightMotorSpeed = 100 + PD;
   
}


analogWrite(5,leftMotorSpeed);
analogWrite(6,rightMotorSpeed);
Serial.print (LFSensor[0]);
Serial.print (";");
Serial.print (LFSensor[1]);
Serial.print (";");
Serial.print (LFSensor[2]);
Serial.print (";");
Serial.print (LFSensor[3]);
Serial.print (";");
Serial.println (LFSensor[4]);   
Serial.print ("L");
Serial.println (leftMotorSpeed);
Serial.print ("R");
Serial.println (rightMotorSpeed);
//Serial.write (valSensor1);

 
}
