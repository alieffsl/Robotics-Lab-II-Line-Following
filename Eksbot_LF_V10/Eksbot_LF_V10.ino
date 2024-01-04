#include "LINEFOLL_EKSBOT.h"

// // Keypad
// char keys[4][4] = {
//   {'1','2','3', 'A'},
//   {'4','5','6', 'B'},
//   {'7','8','9', 'C'},
//   {'*','0','#', 'D'}
// };

// byte pin_rows[4] = {31, 21, 33, 35};
// byte pin_column[4] = {17, 15, 16, 14};

// Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, 4, 4);

void lineIntersect(int n) {
  for (int i = 0; i < n; i++) {
    linedelay(150, 30, -5);
    line(FF, 150, -10);
  }
}

void setup() {
  Serial.begin(9600);
  eksbotInit();
}

void loop() {
  char key = keypad.getKey();
  if (key) selectMode(key);
}

void selectMode(char key){
  Serial.println(key);

  switch (key){
    //Mode Start Kiri
    case '1':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_RIGHT);

      line(FF,220, -14);
      turn(TURN_LEFT);
      lineIntersect(3); //start tengah
    
      turn(TURN_LEFT); //exit tengah
      motorDrivePID(150,165); delay(700); 
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(100);
      motorDrivePID(-150,-165); delay(200);
      spinheading(175); delay(200); //ambil objek 1

      autolinefollow(200,0); 
      line(FL,150,-15); delay(100);
      turn(TURN_LEFT); delay(100);
      // line(FL,150,-7);
      // linedelay(150,20,-5);
      autolinefollow(290,0); 
      line(FR,150,-18);
      turn(TURN_RIGHT); delay(100);
      lineIntersect(4);
      turn(TURN_RIGHT);
      line(FL,150,-15);
      turn(TURN_LEFT); delay(100);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180);  //taruh objek 1


      motorDrivePID(0,0); delay(100);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0);
      line(FF,150,-15);
      turn(TURN_RIGHT); delay(100);
      motorDrivePID(150,165); delay(650); 
      turn(TURN_LEFT);
      lineIntersect(4);

      turn(TURN_LEFT); delay(80);
      linedelay(150,20,-5);
      line(FR,150,-5);
      linedelay(150,20,-5);
      line(FR,150,-18); 
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 2

      autolinefollow(200,0); 
      line(FF,150,-25); 
      findline(140, 140, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-15);
      turn(TURN_RIGHT);
      lineIntersect(3);

      turn(TURN_RIGHT); delay(80);
      linedelay(150,30,-5);
      line(FL,150,-5);
      linedelay(150,30,-5);
      line(FL,150,-18);
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 2

      
      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,140,-25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FL,150,-18);
      turn(TURN_LEFT);

      lineIntersect(3);
      turn(TURN_LEFT); delay(80);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-18);
      turn(TURN_RIGHT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 3

      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      line(FL,150,-7);
      linedelay(150,20,-5); 
      line(FL,150,-7);
      linedelay(150,20,-5); 
      line(FL,150,-18);
      turn(TURN_LEFT);

      autolinefollow(1053,0);
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 3


      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-20);
      findline(140, 165, -25);
      findline(140, 165, -25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FL,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT); delay(80);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-15);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      turn(TURN_LEFT);

      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      turn(TURN_RIGHT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      turn(TURN_LEFT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      
      servoTaruh(2000); delay(100);  //taruh objek 5
      
      motorDrivePID(0,0); delay(100);

      motorDrivePID(-150,-165); delay(500);
      buzzer(1,1000,500);
      //--------------------------------
      motorDrivePID(0,0);
      delay(10000);
      //--------------------------------

      break;
    case '2':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_RIGHT);

      line(FF,220, -14);
      turn(TURN_LEFT);
      lineIntersect(3); //start tengah
    
      turn(TURN_LEFT); //exit tengah
      linedelay(150,20,-5);
      line(FR,150,-5);
      linedelay(150,20,-5);
      line(FR,150,-18); 
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 2

      autolinefollow(200,0); 
      line(FF,150,-25); 
      findline(140, 140, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-15);
      turn(TURN_RIGHT);
      lineIntersect(3);

      turn(TURN_RIGHT); delay(80);
      linedelay(150,30,-5);
      line(FL,150,-5);
      linedelay(150,30,-5);
      line(FL,150,-18);
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 2

      
      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,140,-25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FL,150,-18);
      turn(TURN_LEFT);

      lineIntersect(3);
      turn(TURN_LEFT); delay(80);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-18);
      turn(TURN_RIGHT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 3

      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      line(FL,150,-7);
      linedelay(150,20,-5); 
      line(FL,150,-7);
      linedelay(150,20,-5); 
      line(FL,150,-18);
      turn(TURN_LEFT);

      autolinefollow(1053,0);
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 3


      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-20);
      findline(140, 165, -25);
      findline(140, 165, -25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FL,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT); delay(80);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-15);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      turn(TURN_LEFT);

      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      turn(TURN_RIGHT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      turn(TURN_LEFT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      
      servoTaruh(2000); delay(100);  //taruh objek 5
      motorDrivePID(0,0); delay(50);
      motorDrivePID(-150,-165); delay(500);
      buzzer(1,1000,500);

      motorDrivePID(0,0); delay(10000);
      break;
    case '3':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_RIGHT);
      line(FF,220, -14);
      turn(TURN_LEFT);
      lineIntersect(3); //start tengah
      turn(TURN_LEFT); //exit tengah
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-18);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 3

      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      line(FL,150,-7);
      linedelay(150,20,-5); 
      line(FL,150,-7);
      linedelay(150,20,-5); 
      line(FL,150,-18);
      turn(TURN_LEFT);

      autolinefollow(1053,0);
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 3


      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-20);
      findline(140, 165, -25);
      findline(140, 165, -25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FL,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT); delay(80);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-15);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      turn(TURN_LEFT);

      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      turn(TURN_RIGHT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      turn(TURN_LEFT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      
      servoTaruh(2000); delay(100);  //taruh objek 5
      motorDrivePID(0,0); delay(50);
      motorDrivePID(-150,-165); delay(500);
      buzzer(1,1000,500);

      motorDrivePID(0,0); delay(10000);
      break;
    case '4':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_RIGHT);
      line(FF,220, -14);
      turn(TURN_LEFT);
      lineIntersect(3); //start tengah
      turn(TURN_LEFT); //exit tengah
      delay(80);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-15);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 160); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      turn(TURN_LEFT);

      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_RIGHT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      turn(TURN_RIGHT);

      autolinefollow(953,0); 
      motorDrivePID(150, 150); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      turn(TURN_LEFT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      
      servoTaruh(2000); delay(100);  //taruh objek 5
            motorDrivePID(0,0); delay(50);
      motorDrivePID(-150,-165); delay(500);
      buzzer(1,1000,500);

      motorDrivePID(0,0); delay(10000);
      break;
    
    case '5':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,170,-20);
      findline(150,170,-20);
      turn(TURN_RIGHT);
      line(FF,180,-15);
      turn(TURN_LEFT);
      lineIntersect(3);
      turn(TURN_LEFT);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-7);
      linedelay(120,20,-5);
      line(FR,120,-25);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 165); delay(650);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_LEFT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      linedelay(150,30,-5);
      line(FL,150,-10);
      turn(TURN_LEFT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      
      servoTaruh(2000); delay(100);  //taruh objek 5
      motorDrivePID(0,0); delay(100);
      motorDrivePID(-150,-165); delay(500);
      buzzer(1,1000,500);

      motorDrivePID(0,0); delay(10000); 
      break;
    //Mode Start Kanan
    case '6':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_LEFT);

      line(FF,220, -14);
      turn(TURN_RIGHT);
      lineIntersect(3); //start tengah
    
      turn(TURN_RIGHT); //exit tengah
      motorDrivePID(150,165); delay(700); 
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(100);
      motorDrivePID(-150,-165); delay(200);
      spinheading(-175); delay(200); //ambil objek 1

      autolinefollow(200,0); 
      line(FR,150,-15); delay(100);
      turn(TURN_RIGHT); delay(100);
      // line(FL,150,-7);
      // linedelay(150,20,-5);
      autolinefollow(290,0); 
      line(FL,150,-18);
      turn(TURN_LEFT); delay(100);
      lineIntersect(4);
      turn(TURN_LEFT);
      line(FR,150,-15);
      turn(TURN_RIGHT); delay(100);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180);  //taruh objek 1


      motorDrivePID(0,0); delay(100);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(300,0);
      line(FF,150,-15);
      turn(TURN_LEFT); delay(100);
      motorDrivePID(150,165); delay(650); 
      turn(TURN_RIGHT);
      lineIntersect(4);

      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-5);
      linedelay(150,20,-5);
      line(FL,150,-18); 
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 2

      autolinefollow(200,0); 
      line(FF,150,-25); 
      findline(140, 140, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-15);
      turn(TURN_LEFT);
      lineIntersect(3);

      turn(TURN_LEFT); delay(80);
      linedelay(150,30,-5);
      line(FR,150,-5);
      linedelay(150,30,-5);
      line(FR,150,-18);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 2

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,140,-25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FR,150,-18);
      turn(TURN_RIGHT);

      lineIntersect(3);
      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-18);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 3

      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      line(FR,150,-7);
      linedelay(150,20,-5); 
      line(FR,150,-7);
      linedelay(150,20,-5); 
      line(FR,150,-18);
      turn(TURN_RIGHT);

      autolinefollow(1053,0);
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 3


      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-20);
      findline(140, 165, -25);
      findline(140, 165, -25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FR,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-15);
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(700);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      turn(TURN_RIGHT);
      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      turn(TURN_RIGHT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);  //taruh objek 5

      motorDrivePID(-150,-160); delay(900);

      motorDrivePID(0,0); delay(100);
      buzzer(1,1000,50);
      //////FINISH/////
      motorDrivePID(0,0); delay(10000);
      break;
    case '7':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_LEFT);

      line(FF,220, -14);
      turn(TURN_RIGHT);
      lineIntersect(3); //start tengah
      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-5);
      linedelay(150,20,-5);
      line(FL,150,-18); 
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 2

      autolinefollow(200,0); 
      line(FF,150,-25); 
      findline(140, 140, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-15);
      turn(TURN_LEFT);
      lineIntersect(3);

      turn(TURN_LEFT); delay(80);
      linedelay(150,30,-5);
      line(FR,150,-5);
      linedelay(150,30,-5);
      line(FR,150,-18);
      turn(TURN_RIGHT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 2

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,140,-25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FR,150,-18);
      turn(TURN_RIGHT);

      lineIntersect(3);
      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-18);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 3

      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      line(FR,150,-7);
      linedelay(150,20,-5); 
      line(FR,150,-7);
      linedelay(150,20,-5); 
      line(FR,150,-18);
      turn(TURN_RIGHT);

      autolinefollow(1053,0);
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 3


      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-20);
      findline(140, 165, -25);
      findline(140, 165, -25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FR,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-15);
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      turn(TURN_RIGHT);
      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      turn(TURN_RIGHT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);  //taruh objek 5

      motorDrivePID(-150,-160); delay(900);

      motorDrivePID(0,0); delay(100);
      buzzer(1,1000,50);
      //////FINISH/////
      motorDrivePID(0,0); delay(10000);
      break;
    case '8':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_LEFT);

      line(FF,220, -14);
      turn(TURN_RIGHT);
      lineIntersect(3);
      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-18);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(200);
      spinheading(180); delay(100); //ambil objek 3

      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      line(FR,150,-7);
      linedelay(150,20,-5); 
      line(FR,150,-7);
      linedelay(150,20,-5); 
      line(FR,150,-18);
      turn(TURN_RIGHT);

      autolinefollow(1053,0);
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 3


      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-20);
      findline(140, 165, -25);
      findline(140, 165, -25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FR,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-15);
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      turn(TURN_RIGHT);
      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(650);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      turn(TURN_RIGHT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);  //taruh objek 5

      motorDrivePID(-150,-160); delay(900);

      motorDrivePID(0,0); delay(100);
      buzzer(1,1000,50);
      //////FINISH/////
      motorDrivePID(0,0); delay(10000);
      break;
    case '9':
      buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_LEFT);

      line(FF,220, -14);
      turn(TURN_RIGHT);
      lineIntersect(3);
      turn(TURN_RIGHT); delay(80);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-7);
      linedelay(150,20,-5);
      line(FL,150,-15);
      turn(TURN_LEFT);
      autolinefollow(953,0); 
      motorDrivePID(150, 175); delay(750);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(800);
      spinheading(180); delay(100); //ambil objek 4
      
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 150, -25);
      findline(150, 150, -25);
      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      linedelay(150,20,-5);
      line(FR,150,-7);
      turn(TURN_RIGHT);
      autolinefollow(1153,0);
      motorDrivePID(150, 175); delay(600);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);
      motorDrivePID(-150,-165); delay(500);
      spinheading(180); delay(100);  //taruh objek 4

      motorDrivePID(0,0); delay(200);
      servoReset(2000); 
      motorDrivePID(0,0); delay(100);
      autolinefollow(100,0); 
      line(FF,150,-16);
      findline(140,165,-25);
      findline(140,165,-25);
      turn(TURN_LEFT);
      autolinefollow(200,0); 
      line(FF,150,-18);
      turn(TURN_RIGHT);
      lineIntersect(2);

      turn(TURN_RIGHT);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 180); delay(750);
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(800);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      turn(TURN_RIGHT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);  //taruh objek 5

      motorDrivePID(-150,-160); delay(900);

      motorDrivePID(0,0); delay(100);
      buzzer(1,1000,50);
      //////FINISH/////
      motorDrivePID(0,0); delay(10000);
      break;
    case 'A':
          buzzer(1,50,0);
      delay(100);
      
      linefoll();
      motorDrivePID(150,150);
      delay(800);
      findline(150,160,-20);
      findline(150,160,-20);
      turn(TURN_LEFT);

      line(FF,220, -14);
      turn(TURN_RIGHT);
      lineIntersect(3);
      turn(TURN_RIGHT); delay(80);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      linedelay(120,20,-5);
      line(FL,120,-7);
      turn(TURN_LEFT);

      autolinefollow(953,0); 
      motorDrivePID(150, 185); delay(750);
      next;
      motorDrivePID(0,0); delay(200);
      servoAngkut(2000); 
      motorDrivePID(0,0); delay(200);
      motorDrivePID(-150,-165); delay(800);
      spinheading(180); delay(100); //ambil objek 5
      
      autolinefollow(200,0); 
      line(FF,150,-15);
      motorDrivePID(150,150); delay(800);
      findline(150, 140, -25);
      findline(150, 140, -25);

      turn(TURN_RIGHT);
      autolinefollow(600,0);
      line(FF,150,-18);
      turn(TURN_LEFT);
      lineIntersect(2);

      turn(TURN_LEFT);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      linedelay(150,30,-5);
      line(FR,150,-10);
      turn(TURN_RIGHT);
      autolinefollow(1153,0); 
      motorDrivePID(150, 175); delay(500);
      motorDrivePID(0,0); delay(200);
      servoTaruh(2000); delay(100);  //taruh objek 5

      motorDrivePID(-150,-160); delay(900);

      motorDrivePID(0,0); delay(100);
      buzzer(1,1000,50);
      //////FINISH/////
      motorDrivePID(0,0); delay(10000);
      break;
  }
}
