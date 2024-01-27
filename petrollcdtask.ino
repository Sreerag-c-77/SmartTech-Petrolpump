#include<Keypad.h>
#include<LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;
const byte COLS = 3;
int rel1 = A0;
int rel2 = A1;
char keys[ROWS][COLS]= {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte rowPins[ROWS] = {1,2,3,4};
byte colPins[COLS] = {5,6,7};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int petrolPrice = 1;
int dieselPrice = 2;
int tot = 0;
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
lcd.print("1.Petrol 2.Diesel");
pinMode(rel1, OUTPUT);
pinMode(rel2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 char key = keypad.getKey();
if(key){
  lcd.clear();
  lcd.setCursor(0,0);
  switch(key){
    case '1':
         lcd.print("Petrol Selected");
         tot = cal(petrolPrice,rel1);
         break;
    case '2':
         lcd.print("Diesel Selected");
         tot = call(dieselPrice,rel2);
         break;
    case 'A0':     
         lcd.print("Totalamount");
         lcd.print(tot,1);
         break;
     case 'A1':     
         lcd.print("Totalamount");
         lcd.print(tot,2);
         break;     
    default:
            lcd.print("Invalid");
            break;       
}
delay(1000);
}
}
int cal(int pricePercount, int rel1) {
  lcd.setCursor(0, 1);
  lcd.print("Enter count:");
  
  String input = "";
  char key;
  do {
    key = keypad.getKey();
    if (key && (key >= '0' && key <= '9' || key == '*')) {
      lcd.print(key);
      input += key;
    }
  } while (key != '#');

  int count = input.toInt();
  int cost = count * pricePercount;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cost: Rs");
  lcd.print(cost, 2);

  // Activate the motor relay
  digitalWrite(rel1, HIGH);
  delay(5000); // Simulate dispensing for 5 seconds
  digitalWrite(rel1, LOW);
  // Deactivate the motor relay
  delay(5000);

  return cost;
}
int call(int pricePercountt, int rel2) {
  lcd.setCursor(0, 1);
  lcd.print("Enter count:");
  
  String input = "";
  char key;
  do {
    key = keypad.getKey();
    if (key && (key >= '0' && key <= '9' || key == '*')) {
      lcd.print(key);
      input += key;
    }
  } while (key != '#');

  int countt = input.toInt();
  int costt = countt * pricePercountt;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cost: Rs");
  lcd.print(costt, 2);
  digitalWrite(rel2, HIGH);
  delay(5000); // Simulate dispensing for 5 seconds
  digitalWrite(rel2, LOW);
  delay(5000);
  return costt;
}
