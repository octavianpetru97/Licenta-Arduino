#include<EEPROM.h>

const unsigned address = 0;
int cont = 0;
String formareVal ;
int a = 0;
char play;
char stopMusic;
char stergere;
char citireSeriala;
int citireButon;
int citireReset;
int valFisier =0 ;
int stareSistem = 0;
int adresa0 = 0;
int adresa1 = 1 ;
int variabilaScrier = 1;

int contorScriere=0;
int varFinal;
int variabilaWait = 0;
int contor = 0;
int wait;
int pinBoxa = 45;
int TamponVariabila = 0;
int variabilaContor = 0;
const int songspeed = 1.5;
int pinButon = 31;
int pinReset = 38;
int pinLed = 48;

void setup() 
{

  Serial.begin(9600); 
  Serial1.begin(9600); 
  pinMode(pinBoxa, OUTPUT);
  pinMode(pinButon,INPUT);
  pinMode(pinReset,INPUT);
  pinMode(pinLed,OUTPUT);

     
    
}

void loop()
{
  
 
    while (Serial1.available()>0) {

      noTone(pinBoxa);

      citireSeriala = (char)Serial1.read();
    
      if((contorScriere > EEPROM.length()) && (citireSeriala == '>'))
      {
       
        Serial1.write("k");
        
        contorScriere = 0;
     
        
        break; 
      }
      else if(contorScriere > EEPROM.length())
      {
        
        break;
      }
      
      else if( (citireSeriala == ',') && (variabilaScrier == 1))
      {
        valFisier = formareVal.toInt();
        
        EEPROM.put(address + (contorScriere * 2) ,valFisier);
        
        contorScriere++;

        formareVal="";
      
        break;
      }
       else if (citireSeriala == '>')
      {
        
        contorScriere++;
        EEPROM.put(address + (contorScriere * 2) ,(int)citireSeriala);
        Serial1.write("n");
        variabilaScrier = 0;
        
        break;
      }
      else if( citireSeriala == 'x')
      {

       stareSistem = 0;
      variabilaScrier = 1;
       noTone(pinBoxa);
       
       for( int i = 0 ; i < EEPROM.length() ; i++)
       {
        if(EEPROM.get(address + (i * 2),varFinal) == 62)
        {
          EEPROM.write(address + (i * 2),0);
          break;
        }
        else
        {
          
          EEPROM.write(i,0);
        } 
       }
       Serial1.write("n");
       contorScriere = 0;
       
        
        break;
      }
      else if( citireSeriala == 'v')
      {
        if(( EEPROM.get(adresa0,adresa0) == 0 ) && (EEPROM.get(adresa1,adresa0) == 0))
        {
           noTone(pinBoxa);
           stareSistem = 0;
        }
        else
        {
           contor = 0;
           stareSistem = 1;
        }
        break;
      }
      else if( citireSeriala == 's')
      {
        stareSistem = 0;
        
        noTone(pinBoxa);
        break;
        
      }
      else
      {
         formareVal = formareVal + citireSeriala;
         
      }

      
       
   }

  citireReset = digitalRead(pinReset);
  if(citireReset == HIGH)
  {
     stareSistem = 0;
     variabilaScrier = 1;
     noTone(pinBoxa);
     contorScriere = 0;
     contor = 0;
     digitalWrite(pinLed, HIGH); 
     
     for( int i = 0 ; i < EEPROM.length() ; i++)
     {
       
          
          EEPROM.write(i,0);
        
     }
     digitalWrite(pinLed, LOW); 
    
  }
  citireButon = digitalRead(pinButon);
  if ( a!=citireButon && citireButon)
  {
    
    stareSistem = !stareSistem;
    contor = 0;
   
  }
  a = citireButon;
 

 if(stareSistem == 1)
  {
      
      if(contor % 2 == 1)
      {
        wait = 0;
        EEPROM.get(address + (contor * 2) ,variabilaWait);
        wait =   variabilaWait * songspeed;
      
        variabilaContor++;
      
      }

     if(contor % 2 == 0)
     {
       TamponVariabila = 0;
       
       EEPROM.get(address + (contor * 2) ,TamponVariabila);
       
       variabilaContor++;
       
     }
     
     if( variabilaContor == 2)
     {
       variabilaContor = 0;
      
        
       tone(pinBoxa,TamponVariabila,wait);
       
     }
     if (EEPROM.get(address + (contor * 2),varFinal) == 62)
     {
     
       contor = 0;
     }
     else
     {
     
      contor = contor + 1;
       
     }
   
     delay(wait);
   
   
  }
  else
  {
    noTone(pinBoxa);
  }


   
      
 }

 










             
