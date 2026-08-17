int segpins[7] = {3,7,10,12,13,4,9}, digitpins[4] = {2,5,6,8},dp = 11;  //7SD pins 
int red = A2, yellow = A3, green = A4;   //led pins
int buzzer = A0;   //pin connected with buzzer
int poten = A1;  //pin of the potetiometre
int button = A5;  //pull up button pin
int dt = 1000,i,vol,n,time =0,j;
int numvals[10][7]={
  {1,1,1,1,1,1,0},{0,1,1,0,0,0,0},{1,1,0,1,1,0,1},{1,1,1,1,0,0,1},{0,1,1,0,0,1,1},{1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},{1,1,1,0,0,0,0},{1,1,1,1,1,1,1},{1,1,1,1,0,1,1}
};   //array that contians the truth table required to represent all no. on the 7SD
int best_of_n(int n){
  int rep=0,t=0;
  unsigned long times[n],min,starttime;
  while (rep<n){    //reapeats the timer until the given repetetions
    starttime = millis();
    while (buttonpress()!=1){     //displays the time is milliseconds until the button is pressed and saves it when button is pressed 
      displaynum(millis()-starttime);
      if(buttonpress()==1){
        times[t] = millis() - starttime;
        t++;
        displaynum(rep+1);
        delay(dt);
      }
    }
    buzz();
    if(rep != n-1){   //including if so that it'll not count when rep is 5 i.e it'll not count before displaying the result
      countdown(time);
    }
    rep++;
  }
  min = times[0];
  for (i=0;i<n;i++){
    if (times[i]<min){
      min = times[i];
      Serial.println(min);
    }
  }
  return min;
}     //takes the number of repetetions to do and sets the timer to start everytime the button is pressed
int buttonpress(){
  int b = digitalRead(button);
  return b;
}   //returns 1 when the button is pressed (adviced to be used in a loop)
void buzz(){
  digitalWrite(buzzer,HIGH);
  delay(2);
  digitalWrite(buzzer,LOW);
}    //gives a little click when called
void timesetter(){
  int b=0;
  while(b==0){
    vol = analogRead(poten);
    time = (7./1023.)*vol + 3;
    displaynum(time);
    b = buttonpress();
  }
  countdown(time);
}    //takes the count down time from the user and passes the value to the countdown function
void displaynum(int num){
  int digits[4] =  {(num/1000),(num/100)%10,(num/10)%10,num%10};
  for(i=0;i<4;i++){
    for(j=0;j<4;j++){
      digitalWrite(digitpins[j],LOW);
    }
    for(j=0;j<7;j++){
      digitalWrite(segpins[j],!numvals[digits[i]][j]);
    }
    digitalWrite(digitpins[i],HIGH);
    delay(2);
  }
}   //prints the given number on the 7SD
void countdown(int count){
  int state=0;
  unsigned long starttime = millis(),elapsed =0;
  while(elapsed < count/3){
    displaynum(count-elapsed);
    digitalWrite(red,HIGH);
    elapsed = (millis() - starttime)/1000;
  }
  buzz();
  while(elapsed < 2*count/3){
    displaynum(count-elapsed);
    digitalWrite(yellow,HIGH);
    digitalWrite(red,LOW);
    elapsed = (millis() - starttime)/1000;
  }
  buzz();
  while(elapsed <=count){
    displaynum(count-elapsed);
    digitalWrite(green,HIGH);
    digitalWrite(yellow,LOW);
    elapsed = (millis() - starttime)/1000;
  }
  buzz();
  digitalWrite(green,LOW);
}    //counts down from the time given by the user with indicative lights and a buzz
void setup() {
  for(i=2;i<=13;i++){
    pinMode(i,OUTPUT);
  }
  pinMode(poten,INPUT);
  pinMode(button,INPUT);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(button,LOW);
  Serial.begin(9600);
}
void loop() {
  unsigned long j;
  timesetter();   //taking and initiating the countdown from the user 
  n = 3;
  j = best_of_n(n);
  digitalWrite(red,LOW);
  while (1){
    displaynum(j);
  }
}
