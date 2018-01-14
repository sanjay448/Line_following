#define mlf 25
#define mlb 24
#define mlp 12
#define mrf 28
#define mrb 29
#define mrp 10
//#define mlen
//#define mren

int mlpwm=0,mrpwm=0,mls=220,mrs=220;
int reading[7];
int dread[7];
int perr=0, derr=0, corr=0, kp=15, kd=10, sen_thr=450,sum=0,err=0,wsum=0;

void setup()
{
  Serial.begin(9600);
  pinMode(mlf, OUTPUT);
  pinMode(mlb, OUTPUT);
  pinMode(mlp, OUTPUT);
  pinMode(mrp, OUTPUT);
  pinMode(mrf, OUTPUT);
  pinMode(mrb, OUTPUT);
  //digitalWrite(mlen,HIGH);
 // digitalWrite(mren,HIGH);
}



    void sensor_read(){
      reading[0]=analogRead(A0);
      reading[1]=analogRead(A1);
      reading[2]=analogRead(A2);
      reading[3]=analogRead(A3);
      reading[4]=analogRead(A4);
      reading[5]=analogRead(A5);
      reading[6]=analogRead(A6);
      for(int l=0; l<7; l++)
    {
      if(reading[l]<sen_thr) dread[l]=0;
      else dread[l]=1;
      }
      }
    
    void calc_error(){
      sum=0;
    for(int l=0; l<7;l++)
      sum=sum+dread[l];
     int wsum=7*dread[0]+4*dread[1]+dread[2]-dread[4]-4*dread[5]-7*dread[6];
    err=wsum/sum;
      }
    
    void motor(){ 
      derr=err-perr;
    corr=kp*err+kd*derr;
    perr=err;
       
    
        mrpwm=mrs+corr;
         mlpwm=mls-corr;
         
      if(mlpwm>254) mlpwm=254;
      else if(mrpwm>254) mrpwm=254;
      else if(mlpwm<0) mlpwm=0;
      else if(mrpwm<0) mrpwm=0;
      digitalWrite(mlf,HIGH);
      digitalWrite(mrf,HIGH);
      digitalWrite(mlb,LOW);
      digitalWrite(mrb,LOW);
      
      analogWrite(mlp,mlpwm);
      analogWrite(mrp,mrpwm);
      }

void line_follow(){
     sensor_read();
     calc_error();
     motor();
      }
      
void loop()
{
 line_follow();
 delay(10);
 }      
