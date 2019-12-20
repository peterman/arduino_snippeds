// Seriell auf RX ( oder USB ) reinkommende Daten per event auslesen und das Zeilenende erkennen
// serialEvent() ist nicht kompatible mit Arduino Esplora, Leonardo oder Micro
//
// Matthias Busse 17.12.2018 Version 1.0

String inputString="";            // Eingabe String Daten
bool stringComplete=false;        // String abgeschlossen

void setup() {
  Serial.begin(38400);            // Baud
  inputString.reserve(64);        // 64 Byte Platz für den Seriellen Text
  Serial.println("Bitte Text eingeben und mit Enter bestaetigen:");
}

void loop() {
  if(stringComplete) {
    stringComplete=false;
    Serial.print("String : ");      // String ausgeben
    Serial.println(inputString);  
    Serial.print("Integer: ");      // Integer ausgeben
    Serial.println(inputString.toInt());
    Serial.print("Float  : ");      // Float ausgeben
    Serial.println(inputString.toFloat());
    inputString="";
  }
}

void serialEvent() {
// Wird aufgerufen wenn an RX Daten angekommen sind, ausserhalb von loop().
// Ein delay() in loop() kann die Datenübernahme verzögern.
// Der Arduino RX Buffer ist standardmässig 64 Zeichen groß, kann aber ggf. vergrößert werden.
  while(Serial.available()) {        // bis alle Zeichen im RX Buffer ausgelesen sind
    char inChar=(char)Serial.read(); // ein Zeichen im RX Buffer auslesen
    if(inChar == '\n') {             // String Ende erkennen
      stringComplete=true; 
    }
    else {                            // Zeichen anhängen
      inputString+=inChar; 
    }
  }
}
