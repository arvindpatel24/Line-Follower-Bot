int left = 0;
int mid = 0;
int right = 0;
#define lir 11
#define mir 12
#define rir 13

#define ltf 3
#define rtf 5
#define rtf 10
#define rtb 9

void setup() {
  pinMode(lir, INPUT);
  pinMode(mir, INPUT);
  pinMode(rir, INPUT);

  pinMode(ltf, OUTPUT);
  pinMode(ltb, OUTPUT);
  pinMode(rtf, OUTPUT);
  pinMode(rtb, OUTPUT); 
}

void loop() {
  left = digitalRead(lir);
  right = digitalRead(rir);
  mid = digitalRead(mir);

  analogWrite(ltb,0);
  analogWrite(rtb,0);

  analogWrite(ltf, 100*( mid || 1-left )*(1-left));
  analogWrite(rtf, 100*( mid || 1-right )*(1-right));

  delay(10);
}
