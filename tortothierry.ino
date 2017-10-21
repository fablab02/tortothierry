#include <Servo.h> // librairie pour servomoteur 

// --- Déclaration des constantes utiles ---

//--- Constantes utilisées avec le servomoteur 
const int MAX_ARRIERE=1100; // largeur impulsion pour position ANGLE_MIN degrés du servomoteur ; min=1000
const int ARRET=1490; // largeur impulsion pour position ANGLE_MEDIANE degrés du servomoteur
const int MAX_AVANT=1700; // largeur impulsion pour position ANGLE_MAX degrés du servomoteur ; max=2000
const int DISTANCE_STOP=15;//distance a laquelle il faut changer de direction en cm 

// classiquement : centrage sur 1500 - maxi sens 1 = 1000 et maxi sens 2 = 2000

// --- Déclaration des constantes des broches E/S numériques ---
// Servos
const int broche_servoG=2; // Constante pour la broche 2
const int broche_servoD=3; // Constante pour la broche 3
// capteur US
const int trig = 12;// fil orange
const int echo = 11;// fl marron

long lecture_echo; 
long cm;

//--- Création objet servomoteur 
Servo servoD;  // crée un objet servo pour contrôler le servomoteur Droit
Servo servoG;  // crée un objet servo pour contrôler le servomoteur Gauche


// ////////////////////////// 2. FONCTION SETUP = Code d'initialisation ////////////////////////// 
// La fonction setup() est exécutée en premier et 1 seule fois, au démarrage du programme

void setup()   { // debut de la fonction setup()

// --- ici instructions à exécuter 1 seule fois au démarrage du programme --- 

// ------- Initialisation fonctionnalités utilisées -------  

//--- Initialisation Servomoteur 
 servoG.attach(broche_servoG);  // attache l'objet servo à la broche de commande du servomoteur
 servoD.attach(broche_servoD);  // attache l'objet servo à la broche de commande du servomoteur

// ------- Broches en sorties numériques -------  
 pinMode (broche_servoD,OUTPUT); // Broche broche_servo configurée en sortie
 pinMode (broche_servoG,OUTPUT); // Broche broche_servo configurée en sortie

 pinMode(trig, OUTPUT); 
 digitalWrite(trig, LOW); 
 pinMode(echo, INPUT); 
 Serial.begin(9600); //seulement pour debuggage

} // fin de la fonction setup()
// ********************************************************************************

void loop(){ // debut de la fonction loop()
  if (distance()>DISTANCE_STOP){
    marcheAvant();}
  else{
    tourner();}
}

void marcheAvant(){
//--- marche avant 
  if (!servoD.attached()) servoD.attach(broche_servoD); // attache le servomoteur à la broche si pas attaché
  if (!servoG.attached()) servoG.attach(broche_servoG); 
  servoG.writeMicroseconds(MAX_AVANT);
  servoD.writeMicroseconds(MAX_ARRIERE);
  delay(100);
} 

void tourner(){
//--- tourner 
  if (!servoD.attached()) servoD.attach(broche_servoD); // attache le servomoteur à la broche si pas attaché
  if (!servoG.attached()) servoG.attach(broche_servoG); 
  servoG.writeMicroseconds(MAX_AVANT);
  servoD.writeMicroseconds(MAX_AVANT);
  delay(100);
} 

long distance(){
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  cm = lecture_echo / 58; 
  
  /*uniquement pour debuggage
  Serial.print("Distancem : "); 
  Serial.println(cm);*/
  
  return cm; 
}

