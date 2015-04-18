char inChar;
int i = 0;
int val = 0;
int flag = 0, flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
int Bval = 0, Xval = 0, Yval = 0, Zval = 0, ten = 0;
int neg = 1;
int leftWheel = 0, rightWheel = 0;

void setup() {
  
  Serial.begin(9600);
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
 
  while (Serial.available() > 0 && flag < 5) 
  {
    inChar = Serial.read();
    
            //FOR B
            if(inChar == 98 && flag1 == 0) 
            {
              Serial.read();
              val = Serial.read();
        
              if(val<58 && val>47)
              {
                Bval = val - 48;
                flag += 1;
                flag1 = 1;
              }
              
            }
            
            //FOR X
            if(inChar == 120 && flag2 == 0) 
            {
              Serial.read();
              val = Serial.read();
              
              if(val == 45) 
              {
                neg = -1;
                val = Serial.read();
              }
        
              if(val<58 && val>47)
              {
                Xval = neg*(val - 48);
                flag += 1;
                flag2 = 1;
                neg = 1;
              }
              
              else ;
              
            }
            
            //FOR Y
            if(inChar == 121 && flag3 == 0) 
            {
              Serial.read();
              val = Serial.read();
              
              if(val == 45) 
              {
                neg = -1;
                val = Serial.read();
              }
        
              if(val<58 && val>47)
              {
                Yval = neg*(val - 48);
                flag += 1;
                flag3 = 1;
                neg = 1;
              }

            }
            
            //FOR Z
            if(inChar == 122 && flag4 == 0) 
            {
              Serial.read();
              val = Serial.read();
              
              if(val == 45) 
              {
                neg = -1;
                val = Serial.read();
              }
        
              if(val<58 && val>47)
              {
                Zval = neg*(val - 48);
                flag += 1;
                flag4 = 1;
                neg = 1;
              }
              
            }
     
  }
  
  flag = 0;
  flag1 = 0;
  flag2 = 0;
  flag3 = 0;
  flag4 = 0;
  
  /*
  Serial.print("B command: ");
  Serial.println(Bval);
  Serial.print("X speed: ");
  Serial.println(Xval);
  Serial.print("Y speed: ");
  Serial.println(Yval);
  Serial.print("Z speed: ");
  Serial.println(Zval);
  */
  
  //left and right
  if(Yval < 0)
  {
    rightWheel -= Yval;
  }
  else if(Yval > 0)
  {
    leftWheel += Yval;
  }
  else;

  //forward and backward
  leftWheel -= Xval;
  rightWheel -= Xval;
  
  //check max out
  if(leftWheel > 9) leftWheel = 9;
  if(leftWheel < -9) leftWheel = -9;
  if(rightWheel > 9) rightWheel = 9;
  if(rightWheel < -9) rightWheel = -9;
  
  //map to PWM value
  /*
  leftWheel = (float)leftWheel/9.0*255;
  rightWheel = (float)rightWheel/9.0*255;
  leftWheel = (float)leftWheel;
  rightWheel = (float)rightWheel;
  */
  
  leftWheel = map(leftWheel, 0, 9, 0, 255);
  rightWheel = map(rightWheel, 0, 9, 0, 255);
  
  //print it
  Serial.println("Left speed: ");
  Serial.println(leftWheel);
  Serial.println("Right speed: ");
  Serial.println(rightWheel);
  
  //update and then clear motors
  motorUpdate(leftWheel, rightWheel);
  leftWheel = 0;
  rightWheel = 0;

}



//drive function
void motorUpdate(int left, int right)
{
  if (left > 0)
  {
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    analogWrite(9, -left);
  }
  else
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(9, left);
  }
  
  if (right < 0)
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    analogWrite(10, -right);
  }
  else
  {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    analogWrite(10, right);
  }

  
}






