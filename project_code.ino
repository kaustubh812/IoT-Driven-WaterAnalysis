#include <LiquidCrystal.h>
LiquidCrystal lcd(6,7,5,4,3,2);
 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,9);

#include <Wire.h>



/*********************** DS18B20 ***************************/
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 10 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
/***********************************************************/


char res[130];




float tempc=0;

void serialFlush()
{
  while(Serial.available() > 0) 
  {
    char t = Serial.read();
  }
} 

void myserialFlush()
{
  while(mySerial.available() > 0) 
  {
    char t = mySerial.read();
  }
} 


char check(char* ex,int timeout)
{
  int i=0;
  int j = 0,k=0;
  while (1)
  {
    sl:
    if(mySerial.available() > 0)
    {
      res[i] = mySerial.read();
      if(res[i] == 0x0a || res[i]=='>' || i == 100)
      {
        i++;
        res[i] = 0;break;
      }
      i++;
    }
    j++;
    if(j == 30000)
    {
      k++;
     // Serial.println("kk");
      j = 0;  
    }
    if(k > timeout)
    {
      //Serial.println("timeout");
      return 1;
     }
  }//while 1
  if(!strncmp(ex,res,strlen(ex)))
  {
   // Serial.println("ok..");
    return 0;
   }
  else
  {
   // Serial.print("Wrong  ");
   // Serial.println(res);
    i=0;
    goto sl;
   }
} 

char buff[200],k=0;
void upload(unsigned int s1,unsigned int s2,unsigned int s3);
char readserver(void);
void clearserver(void);

const char* ssid = "iotserver";
const char* password = "iotserver123";

void setup() 
{  
  char ret;  

  
  Serial.begin(9600);
  mySerial.begin(9600);
  
  //26.  IOT based industrial safety system using Arduino
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);lcd.print("    Welcome  ");
     delay(2500);   

   wifiinit();
  delay(2500);
  
  sensors.begin(); delay(100);

  lcd.clear();
  lcd.print("T:");//2-3-4,0
  lcd.setCursor(8,0);
  lcd.print("P:");//10,0
  
  lcd.setCursor(0,1);
  lcd.print("C:");//2,1
  lcd.setCursor(7,1);
  lcd.print("Tr:");//10,1
}

char bf3[50];
int g=0,f=0,count=0,lc=0;
int gk=0;

int phv=0,phv1=0;
int condv=0;
int turbv=0;

float tempf=0;

void loop() 
{
 char ctrl=0;
/*
    tempc = analogRead(A5);
    //tempc = (tempc*0.48828125);
    tempc = tempc * (5.0 * 1000.0 / 1024.0);
    tempc = (((tempc/100) * 1.5) - 14);
    lcd.setCursor(2,0);convertl(tempc);    delay(100);
*/
    sensors.requestTemperatures();
    tempc = sensors.getTempCByIndex(0);
    tempf = ((tempc*1.8) + 42); 
    lcd.setCursor(2,0);convertl(tempc);delay(100);//6,7,8,9

    phv1 = analogRead(A1);
    /*
    if(phv1 >=  300){phv1=300;}
    phv = map(phv1,0,300,0,14);
    lcd.setCursor(10,0);convertl(phv);    
    */
         if(phv1 < 100)
          {
            phv1 = 0;
          }
        else
          {
            phv1 = (phv1/100) + 2;
          }
        if(phv1 >= 14){phv1=14;}
    phv = phv1;
    lcd.setCursor(10,0);convertl(phv);
    delay(100);
    
    condv = analogRead(A3);
    condv = (1024 - condv);
    lcd.setCursor(2,1);convertl(condv);    delay(100);

    turbv = analogRead(A2);
    lcd.setCursor(10,1);convertl(turbv);    delay(100);

      delay(500);
       
      count++;
      lcd.setCursor(14,1);convertk(count);
  
      if(count > 30)
        {
         count = 0;
          delay(1000);
         
            upload(tempc,phv,condv,turbv);  
         
          delay(10000); 
        }
      ctrl=0;
     
}
char bf2[50];
void upload(unsigned int s1,unsigned int s2,unsigned int s3,unsigned int s4)
{
  delay(2000);
  lcd.setCursor(15, 1);lcd.print("U");
  myserialFlush();
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"projectsfactoryserver.in\",80");
    
  //http://projectsfactoryserver.in/storedata.php?name=pf5&s1=25&s2=35
  //sprintf(buff,"GET http://embeddedspot.top/iot/storedata.php?name=iot139&s1=%u&s2=%u&s3=%u\r\n\r\n",s1,s2);
  
      delay(8000);
     
      
      memset(buff,0,strlen(buff));   
      sprintf(buff,"GET http://projectsfactoryserver.in/storedata.php?name=server74&s1=%u&s2=%u&s3=%u&s4=%u\r\n\r\n",s1,s2,s3,s4);
//      buff = buff + moss + "\r\n\r\n";
     // strcat(buff,s3);
         
      myserialFlush();
      sprintf(bf2,"AT+CIPSEND=4,%u",strlen(buff));
      mySerial.println(bf2);
      
         delay(5000);
          
          
          myserialFlush();
          mySerial.print(buff);
         
              delay(2000);
              
              mySerial.println("AT+CIPCLOSE");
       lcd.setCursor(15, 1);lcd.print(" ");  
}

void upload1(int s1,const char *s2)
{
  delay(2000);
  lcd.setCursor(15, 1);lcd.print("U");
  myserialFlush();
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"projectsfactoryserver.in\",80");
    
  //http://projectsfactoryserver.in/storedata.php?name=pf5&s1=25&s2=35
  //sprintf(buff,"GET http://embeddedspot.top/iot/storedata.php?name=iot139&s1=%u&s2=%u&s3=%u\r\n\r\n",s1,s2);
  
      delay(8000);
     
      
      memset(buff,0,strlen(buff));
      
      if(s1 == 2){sprintf(buff,"GET http://projectsfactoryserver.in/storedata.php?name=iot18&s2=%s\r\n\r\n",s2);}
      if(s1 == 3){sprintf(buff,"GET http://projectsfactoryserver.in/storedata.php?name=iot18&s3=%s\r\n\r\n",s2);}

     // buff = buff + moss + "\r\n\r\n";
     // strcat(buff,s3);
         
      myserialFlush();
      sprintf(bf2,"AT+CIPSEND=4,%u",strlen(buff));
      mySerial.println(bf2);
      
         delay(5000);
          
          
          myserialFlush();
          mySerial.print(buff);
         
              delay(2000);
              
              mySerial.println("AT+CIPCLOSE");
       lcd.setCursor(15, 1);lcd.print(" ");  
}

char readserver(void)
{
  char t;
  delay(2000);
  lcd.setCursor(15, 1);lcd.print("R");
  myserialFlush();
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"projectsfactoryserver.in\",80");

  //http://projectsfactoryserver.in/last.php?name=amvi001L

      delay(8000);
      memset(buff,0,strlen(buff));
      sprintf(buff,"GET http://projectsfactoryserver.in/last.php?name=iot17L\r\n\r\n");
      myserialFlush();
      sprintf(bf2,"AT+CIPSEND=4,%u",strlen(buff));
      mySerial.println(bf2);
      
         delay(5000);
          
          
          myserialFlush();
          mySerial.print(buff);
          
       //read status
        while(1)
        {
           while(!mySerial.available());
            t = mySerial.read();
           // Serial.print(t);
            if(t == '*' || t == '#')
            {
              if(t == '#')return 0;
              while(!mySerial.available());
               t = mySerial.read();
             //  Serial.print(t);
               delay(1000);
                myserialFlush();
               return t;
            }
        }
              delay(2000);
              
       mySerial.println("AT+CIPCLOSE");
       lcd.setCursor(15, 1);lcd.print(" "); 
       delay(2000);  
return t;
}

void clearserver(void)
{
  delay(2000);
  lcd.setCursor(15, 1);lcd.print("C");
  myserialFlush();
  mySerial.println("AT+CIPSTART=4,\"TCP\",\"projectsfactoryserver.in\",80");

  //sprintf(buff,"GET http://projectsfactoryserver.in/storedata.php?name=iot1&s10=0\r\n\r\n");
      delay(8000);
      memset(buff,0,strlen(buff));
      sprintf(buff,"GET http://projectsfactoryserver.in/storedata.php?name=iot1&s10=0\r\n\r\n");
      myserialFlush();
      sprintf(bf2,"AT+CIPSEND=4,%u",strlen(buff));
      mySerial.println(bf2);
      
         delay(5000);
          
          
          myserialFlush();
          mySerial.print(buff);
          
          delay(2000);
          myserialFlush();
      
              
              
       mySerial.println("AT+CIPCLOSE");
       lcd.setCursor(15, 1);lcd.print(" "); 
       delay(2000);  
}


void wifiinit()
{
 char ret;  
  st:
  mySerial.println("ATE0");
  ret  = check((char*)"OK",50);
  mySerial.println("AT");
  ret  = check((char*)"OK",50);
  if(ret != 0)
  {
    delay(1000);
   goto st; 
  }
  
     lcd.clear();lcd.setCursor(0, 0);lcd.print("CONNECTING");  
  mySerial.println("AT+CWMODE=1");
   ret  = check((char*)"OK",50);
 cagain:
    
  myserialFlush();
  mySerial.print("AT+CWJAP=\"");
  mySerial.print(ssid);
  mySerial.print("\",\"");
  mySerial.print(password);
  mySerial.println("\"");
  if(check((char*)"OK",300))goto cagain;    
  mySerial.println("AT+CIPMUX=1");
  delay(1000);
 

  lcd.clear();lcd.setCursor(0, 0);lcd.print("WIFI READY"); 
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
void convertk(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
  // lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
