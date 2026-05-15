#include <LiquidCrystal.h>
#include <Servo.h>

// Pini LCD: RS=12, E=11, D4=5, D5=4, D6=3, D7=2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo bariera;

// Pini Senzori
const int trigIntrare = 7;
const int echoIntrare = 6;
const int trigIesire = 9;
const int echoIesire = 8;

int locuriDisponibile = 5; 

void setup() { // se executa o sg data la pornire
  lcd.begin(16, 2);
  bariera.attach(10);
  bariera.write(0); // bariera porneste inchisa
  
  pinMode(trigIntrare, OUTPUT);
  pinMode(echoIntrare, INPUT);
  pinMode(trigIesire, OUTPUT);
  pinMode(echoIesire, INPUT);
  
  lcd.print("Parcare UPT AC");
  delay(2000);
  actualizeazaDisplay();
}

long citesteDistanta(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH) * 0.034 / 2;
}

void actualizeazaDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Locuri: ");
  lcd.print(locuriDisponibile);
  lcd.setCursor(0, 1);
  lcd.print("BINE ATI VENIT!");
}

void loop() {
  long d1 = citesteDistanta(trigIntrare, echoIntrare);
  long d2 = citesteDistanta(trigIesire, echoIesire);

  // LOGICA INTRARE (Senzor Stanga)
  if (d1 > 0 && d1 < 20 && locuriDisponibile > 0) {// Dacă distanța la senzorul 1 este mică ȘI mai avem locuri libere (locuri > 0)
    locuriDisponibile--;// scade nr locuri libere 
    lcd.clear();
    lcd.print("PIN ACCES: ");
    lcd.print(random(1000, 9999)); // genereaza pin de intrare
    
    bariera.write(90); // se ridica bariera
    delay(3000);       // asteapta masina
    bariera.write(0);  // coboara bariera
    actualizeazaDisplay();
  }

  // LOGICA IESIRE (Senzor Dreapta)
  if (d2 > 0 && d2 < 20 && locuriDisponibile < 5) {
    locuriDisponibile++;
    lcd.clear();
    lcd.print("DRUM BUN!");
    
    bariera.write(90); // Se ridica
    delay(3000);
    bariera.write(0);  // Coboara
    actualizeazaDisplay();
  }
  
  delay(200);
}