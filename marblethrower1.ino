/*MarbleThrower
Toiminta: liukukytkimellä valitaan manuaalinen tai automaattinen laukaisu.
Manuaalitilassa painonapin ensimmäisellä painalluksella katapultti ladataan,
toisella painalluksella tapahtuu laukaisu.
Automaattitilassa napin painalluksella katapultti ladataan,
jonka jälkeen määritetyn etäisyyden alittuessa tapahtuu laukaisu.
Automaatti ja manuaalitilan välillä voidaan vaihtaa lennosta, 
katapultin latauksen tila tallennetaan muuttujaan.
Niin automaatti- kuin manuaalitilassa ledit ilmaisevat kun kohde on
kantaman sisällä. Potentiometrillä katapulttia voidaan kääntää alustallaan.
*/

#include <Servo.h>

Servo servo1; 
Servo servo2;
Servo servo3;

int buttonPin = 2; //lataus/laukaisu nappi pinniin 2
int buttonState = 0; // muuttuja painonapin tilalle
int switchPin = 10; //moden valitseva kytkin pinniin 10
int knobPin = A0; //analog pin johon potentiometri (knob) on kytketty
int val; //muuttuja analog pinnin arvolle 
int mode; // muuttuja automaatti/manuaali tiloille
int trigPin = 8; // Triggerpin Ultrasonic Sensor
int echoPin = 9; // Echopin Ultrasonic Sensor
long duration; // muuttuja ääniaallon kulun kestolle
int distance; // muuttuja etäisyydelle
int ledPin1 = 11; // Led 1 pinniin 11
int ledPin2 = 12; // Led 2 pinniin 12
int ledPin3 = 13; //Led 3 pinniin 13
int loaded = false; // muuttuja latauksen tilalle
int dist3 = 150; // etäisyys 3 150cm
int dist2 = 90; // etäisyys 2 90cm
int dist1 = 40; // etäisyys 1, laukaisu etäisyys, 40cm

void setup() {
  
	Serial.begin(9600);
  	pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  	pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  	pinMode(buttonPin, INPUT); //napin tila pinnistä 2 sisään
  	pinMode(switchPin, INPUT); //napin tila pinnistä 10 sisään
  	pinMode(ledPin1, OUTPUT); // LedPinnit outputiksi
  	pinMode(ledPin2, OUTPUT);
  	pinMode(ledPin3, OUTPUT);
  	servo1.attach(3); //servo1 pinniin 3
  	servo2.attach(5); //servo2 pinniin 5
  	servo3.attach(6); //servo3 pinniin 6
	servo1.write(0);
  	servo2.write(0);
}

void loop() {
  
  	mode = digitalRead(switchPin); // liukukytkimellä on valittu automaatti/manuaali
  	//Serial.print(mode);
  	if (mode == HIGH) { 
    	rotation();
    	ultraSonic();
    	automatic();
  	}
  	else {
    	rotation();
    	ultraSonic();
    	manual();
    }
}

void rotation() { // alustan käännölle funktio
  	val = analogRead(knobPin); //lukee analogipinnin arvon 
  	val = map(val, 0, 1023, 0, 175); // skaalaa potentiometrin arvot servolle (yli 175astetta menevät arvot saivat servon "tärisemään")
  	servo3.write(val); // kääntää servoa potentiometrin arvon mukaan
  	delay(15); // odottaa että servo kerkää tilaan
}

void ultraSonic() { // ultraäänelle funktio
  
  	digitalWrite(trigPin, LOW); //tyhjätään triggerPinin tila
    delay(2);
  	digitalWrite(trigPin, HIGH); //Triggerpiniin signaali 10ms
  	delay(10);
  	digitalWrite(trigPin, LOW); //signaali poikki triggerpinistä
  	duration = pulseIn(echoPin, HIGH); //luetaan echoPin mikrosekunteina duration muuttujaan
  	distance = duration * 0.034 / 2; // Lasketaan etäisyys keston perusteella. Jako kahdella, edes takaisin
  	Serial.print(distance);
  	Serial.println(" cm");
  
  	if (distance > dist2 && distance < dist3) { //jos etäisyys on välillä dist2-dist3 syttyy led1
    	digitalWrite(ledPin1, HIGH);
    	digitalWrite(ledPin2, LOW);
    	digitalWrite(ledPin3, LOW);
  	}
  	else if (distance > dist1 && distance <= dist2) { //jos etäisyys on väillä dist1-dist2 syttyy led1 ja led2
    	digitalWrite(ledPin1, HIGH);
    	digitalWrite(ledPin2, HIGH);
    	digitalWrite(ledPin3, LOW);
  	}
  	else if (distance <= dist1) { //jos etäisyys on < dist1 syttyy led1, led2 ja led3
    	digitalWrite(ledPin1, HIGH);
    	digitalWrite(ledPin2, HIGH);
    	digitalWrite(ledPin3, HIGH);
  	}
  	else {
    	digitalWrite(ledPin1, LOW);
    	digitalWrite(ledPin2, LOW);
    	digitalWrite(ledPin3, LOW);
  	}
}

void manual() { // manuaaliselle käytölle funktio

  	int i; // i vain manual funktiossa
	buttonState = digitalRead(buttonPin); //stateen luetaan pinni 2
	//Serial.print(buttonState);
  	if (buttonState == HIGH && loaded == false) { //jos nappia painetaan ja ei ole valmiiksi ladattu, käännetään servo1 180 astetta
    	for (i = 0; i < 180; i++) { 
      		servo1.write(i);              
      		delay(10);                      
    	}
      	loaded = true;
   		delay(1000); //kuminauhan lataavan servon käännön jälkeen odotetaan sekunti
    }
    else if (buttonState == HIGH && loaded == true) { //jos nappia painetaan kun katapultti on ladattu, laukaisu
    	for (i = 0; i < 90; i++) { //ja käännetään servo2 90 astetta, laukaisu
      		servo2.write(i);              
      		delay(10);                      
    	}
    	delay(1000); //laukaisun jälkeen sekunti viivettä
    	for (i = 180; i > 0; i--) { //ja käännetään servo1 takasin alkupisteeseen
            servo1.write(i);               
            delay(10);                      
    	}
      	loaded = false;
    	delay(1000); //sekunnin viive ja käännetään servo2 lukitsevaan asentoon
    	for (i = 90; i > 0; i--) { 
    		servo2.write(i);               
    		delay(10); 
    	}
  	}
  	else {
  	}
}

void automatic() { // automaattiselle laukaisulle funktio

  	int i; // i vain automatic funktiossa
  	buttonState = digitalRead(buttonPin); //stateen luetaan pinni 2
  	if (buttonState == HIGH && loaded == false) { //jos nappia painetaan ja ei ole valmiiksi ladattu,  käännetään servo1 180 astetta
  		for (i = 0; i < 180; i++) { 
      		servo1.write(i);              
      		delay(10);
        }
    	loaded = true;
        delay(1000); //kuminauhan lataavan servon käännön jälkeen odotetaan sekunti
    }
    else if (loaded == true && distance < dist1) { //jos etäisyys alle dist1 käännetään servo1 180 astetta
		for (i = 0; i < 90; i++) { //ja käännetään servo2 90 astetta, laukaisu
      		servo2.write(i);              
      		delay(10);
        }
		delay(1000); //laukaisun jälkeen sekunti viivettä
    	for (i = 180; i > 0; i--) { //ja käännetään servo1 takasin alkupisteeseen
      		servo1.write(i);               
      		delay(10);                      
    	}
      	loaded = false;
    	delay(1000); //sekunnin viive ja käännetään servo2 lukitsevaan asentoon
    	for (i = 90; i > 0; i--) { 
    		servo2.write(i);               
    		delay(10); 
    	}
    }
  	else {
    }
}