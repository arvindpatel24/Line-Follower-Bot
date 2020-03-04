int left_1 = 0;
int left_2 = 0;
int left_3 = 0;
int left_4 = 0;
int right_1 = 0 ;
int right_2 = 0 ;
int right_3 = 0 ;
int right_4 = 0 ;

int left_junc = 0;
int right_junc = 0;
int bidir_junc = 0;
int nothing = 0;

float average = 0;
int sum = 0;
int ir_count = 0;
int flag, i;
float diff = 0;
int check=0;


#define WHITE 0
#define BLACK 1

#define l4 2
#define l3 3
#define l2 4
#define l1 5
#define r1 6
#define r2 7
#define r3 8
#define r4 9

#define dir1 12
#define dir2 13
#define m1 10
#define m2 11
float set_point = 3500;
float proportional = 0;
float derivative = 0;
float last_proportional = 0;
float integral = 0;
float Kp = 0.08;
//float Ki = 0.03;
float Kd = 1.6;
float pos=0;
void setup() {
  for (i = 2; i <= 9; i++)
    pinMode(i, INPUT);

  pinMode(dir1, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(m2, OUTPUT);
  Serial.begin(9600);
}

void read_sensor()
{ left_1     = digitalRead(l1);
  left_2     = digitalRead(l2);
  left_3     = digitalRead(l3);
  left_4     = digitalRead(l4);
  right_1    = digitalRead(r1);
  right_2    = digitalRead(r2);
  right_3    = digitalRead(r3);
  right_4    = digitalRead(r4);
}
void print_all_ir()
{
  Serial.print(left_4);
  Serial.print("  ");
  Serial.print(left_3);
  Serial.print("  ");
  Serial.print(left_2);
  Serial.print("  ");
  Serial.print(left_1);
  Serial.print("  ");
  Serial.print(right_1);
  Serial.print("  ");
  Serial.print(right_2);
  Serial.print("  ");
  Serial.print(right_3);
  Serial.print("  ");
  Serial.print(right_4);
  Serial.print("             ");
  Serial.print(diff);
  Serial.print("             ");
  Serial.print(left_junc);
  Serial.print("      ");
  Serial.print(right_junc);
  Serial.print("      ");
  Serial.print(bidir_junc);
  Serial.print("             ");
  Serial.println(nothing);
}

float find_diff()
{ sum = 0; ir_count = 0;
  for (i = 1; i <= 8; i++)
  { flag = 0;
    if (digitalRead(i + 1) == WHITE )
    { ir_count++;
      flag = 1;
    }
    if(i>=2 && i <=7)
      sum = sum + 1000 * (i-1) * flag;
  }
  average = sum / ir_count;
  return ((float)average) ;
}

void no_reading()
{ nothing++;
  Serial.println("Nothing me hai");
  while ( (digitalRead(l3) != WHITE && digitalRead(r3) != WHITE) && (( digitalRead(l2) != WHITE && digitalRead(r2) != WHITE ) && (digitalRead(l1) != WHITE && digitalRead(r1) != WHITE)))
    forward();
}

void straight()
{ //Serial.println("ELSE me hi ja raha hai");
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  /*
  positio = find_diff();
  Serial.println("position = ");
  Serial.println(positio);
  proportional = positio – set_point; //replace your position value at set point
  derivative = proportional – last_proportional;
  integral = integral + proportional;
  last_proportional = proportional;
  // Kp = 0.08;
  // Ki = 0.0002;
  // Kd = 1.0;
  diff = proportional * Kp + integral * Ki + derivative * Kd;
  */
  pos = find_diff();
  proportional = pos - set_point;
  derivative = proportional - last_proportional;
  //integral = integral + proportional;
  last_proportional = proportional;
  diff = (proportional* Kp) + (derivative * Kd);
  Serial.println(diff);
  if(diff > 80 )
   diff = 80; 
  if(diff < (-80))
   diff = -80 ; 
  //diff = map(diff,-70,70,-30,30);
  if (diff < 0)
  { analogWrite(m1, 80 + diff);
    analogWrite(m2, 80);
  }
  else if (diff > 0)
  { analogWrite(m1, 80 );
    analogWrite(m2, 80 - diff );
  }
  else
  { analogWrite(m1, 80);
    analogWrite(m2, 80);
  }
  delay(5);
}

void forward()
{ digitalWrite(dir1, LOW);
  analogWrite(m1, 80);
  digitalWrite(dir2, LOW);
  analogWrite(m2, 80);
  delay(1);
}
void stop_all()
{ digitalWrite(dir1, LOW);
  analogWrite(m1, 0);
  digitalWrite(dir2, LOW);
  analogWrite(m2, 0);
  delay(1);
}

void sharp_left()
{ digitalWrite(dir1, HIGH);
  analogWrite(m1, 0);
  digitalWrite(dir2, LOW);
  analogWrite(m2, 100);
  delay(5);
}
void sharp_right()
{ digitalWrite(dir1, LOW);
  analogWrite(m1, 100);
  digitalWrite(dir2, HIGH);
  analogWrite(m2, 0);
  delay(5);
}

void power_left()
{ digitalWrite(dir1, HIGH);
  analogWrite(m1, 80);
  digitalWrite(dir2, LOW);
  analogWrite(m2, 80);
  delay(5);
}
void power_right()
{ digitalWrite(dir1, LOW);
  analogWrite(m1, 80);
  digitalWrite(dir2, HIGH);
  analogWrite(m2, 80);
  delay(5);
}

void go_straight()
{
  while (digitalRead(l4) != BLACK || digitalRead(r4) != BLACK)
    forward();
}

void angle_left()
{ while ( digitalRead(l4) != BLACK  )
    power_left();
  while (digitalRead(l2) != BLACK)
    sharp_left();

}

void angle_right()
{ while ( digitalRead(r4) != BLACK  )
    power_right();
  while (digitalRead(r2) != BLACK)
    sharp_right();

}

void take_left()
{ while (digitalRead(l4) != BLACK || digitalRead(l2) != BLACK)
    sharp_left();
  while (digitalRead(r2) != WHITE )
    sharp_left();
}

void take_right()
{ while (digitalRead(r4) != BLACK || digitalRead(r2) != BLACK)
    sharp_right();
  while (digitalRead(l2) != WHITE )
    sharp_right();
}

void check_from_left()
{ check =0;
  for(i=0;i<30;i++)
  { sharp_left();
    if((digitalRead(l4) == WHITE && digitalRead(r4) == WHITE ) && (digitalRead(l3) == WHITE && digitalRead(r3) == WHITE))
    {  check=1;
       return ;
    }
  }
  stop_all();
  for(i=0;i<30;i++)
  {
  digitalWrite(dir1, HIGH);
  analogWrite(m1, 0);
  digitalWrite(dir2, HIGH);
  analogWrite(m2, 100);
  delay(5);
  }
}

void T_junction()
{ bidir_junc++;
  stop_all();
  delay(1000);
  //if (bidir_junc == 1)
  take_right();
}

void L_junction()
{ left_junc++;
  stop_all();
  delay(1000);
  /*check_from_left();
  if(check == 1)
    T_junction();
  else  
    left_junc++;
    if(left_junc == 1)
      go_straight();
    else if(left_junc == 3)
      angle_left();*/
    if(left_junc == 1 || left_junc == 4)
      go_straight();
    else if(left_junc == 2)
      angle_left();
    else
      take_left();
}

void R_junction()
{ right_junc++;
  stop_all();
  delay(1000);
 /*if(right_junc == 1)
    go_straight();
  else if(right_junc == 3)
    angle_right();
  else*/
    take_right();
}


void loop() {
  read_sensor();
  diff = find_diff();
  print_all_ir();
  if (ir_count == 0)
    no_reading();
  else if ((digitalRead(l4) == WHITE && digitalRead(r4) == WHITE ) && (digitalRead(l3) == WHITE && digitalRead(r3) == WHITE))
    T_junction();
  else if ((digitalRead(l4) == WHITE && digitalRead(r4) == BLACK))
    L_junction();
  else if ((digitalRead(l4) == BLACK && digitalRead(r4) == WHITE))
    R_junction();
  else if (digitalRead(l3) == BLACK && digitalRead(r3) == BLACK)
    straight();
}
