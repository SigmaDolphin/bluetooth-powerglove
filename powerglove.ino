#include <Keypad.h>
const byte rows = 3;
const byte cols = 8;
boolean fader = false;
boolean forwards = true;
int brightness = 0;

char buttons[rows][cols] = {
  {'7', '6', '5', '4', '3', '0', '1', '2'},
  {'A', 'B', 'T', 'S', 'U', 'R', 'L', 'D'},
  {'?', '?', '?', '?', 'P', '8', '9', 'E'}
};

byte colPins[cols] = {2, 3, 4, 5, 6, 7, 8, 9};
byte rowPins[rows] = {11, 12, 13};

Keypad buttonMap = Keypad(makeKeymap(buttons), rowPins, colPins, rows, cols);

void setup() {
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  buttonMap.addEventListener(buttonEvent);
}

void loop() {
char inputKey = buttonMap.getKey();

  //if (inputKey != NO_KEY) {
  //  Serial.println(inputKey);
  //}
  
  if (fader == true) {

    if (brightness == 255) {
      forwards = false;
    } else if (brightness == 0) {
      forwards = true;
    }

    if (forwards) {
      brightness++;
    } else {
      brightness--;
    }
    analogWrite(10, brightness);
    delay(5);
  }
}

//0xFE 0x02 0x03 0x29 = Task Manager


void buttonEvent(KeypadEvent key) {
  switch (buttonMap.getState()) {

    case PRESSED:
      switch (key) {
        //LED Light
        case '0':
          fader = ! fader;
          brightness = 0;
          analogWrite(10, brightness);
          break;

        //Prev Track
        case '5':
          sendCommand(0x00, 0x02);
          break;

        //Next Track
        case '6':
          sendCommand(0x00, 0x01);
          break;

        //Play
        case '7':
          sendCommand(0x80, 0x00);
          break;

        //Stop
        case '8':
          sendCommand(0x00, 0x04);
          break;

        //Mute
        case '9':
          sendCommand(0x40, 0x00);
          break;

        //Enter
        case 'E':
          sendComKeys(0x00, 0x28);
          break;


        //Directionals
        case 'U':
          sendComKeys(0x00, 0x52);
          break;

        case 'D':
          sendComKeys(0x00, 0x51);
          break;

        case 'L':
          sendComKeys(0x00, 0x50);
          break;

        case 'R':
          sendComKeys(0x00, 0x4F);
          break;

        //unrealistic key combinations to bind to opening programs or other actions
        //Ctrl + Shift + Alt + = key
        case '1':
          sendComKeys(0x07, 0x2e);
          break;
        //Ctrl + Shift + Alt + 0 key
        case '2':
          sendComKeys(0x07, 0x27);
          break;
        //Ctrl + Shift + Alt + 9 key
        case '3':
          sendComKeys(0x07, 0x26);
          break;
        //Ctrl + Shift + Alt + 8 key
        case '4':
          sendComKeys(0x07, 0x25);
          break;


        //Change monitor settings (Win + P)
        case 'P':
          sendComKeys(0x08, 0x13);
          break;


        //Spacebar
        case 'A':
          sendComKeys(0x00, 0x2C);
          break;

        //Backspace
        case 'B':
          sendComKeys(0x00, 0x2A);
          break;
          
        //Open Start menu (Ctrl + Esc)
        case 'S':
          sendComKeys(0x01, 0x29);
          break;
          
        //Switch between open windows  (Ctrl + Win + Tab)
        case 'T':
          sendComKeys(0x09, 0x2B);
          break;
      }

      break;



    case RELEASED:
      switch (key) {

        //Prev Track
        case '5':
          releaseButton();
          break;

        //Next Track
        case '6':
          releaseButton();
          break;

        //Play
        case '7':
          releaseButton();
          break;

        //Stop
        case '8':
          releaseButton();
          break;

        //Mute
        case '9':
          releaseButton();
          break;

        //Enter
        case 'E':
          releaseShort();
          break;


        //Directionals
        case 'U':
          releaseShort();
          break;

        case 'D':
          releaseShort();
          break;

        case 'L':
          releaseShort();
          break;

        case 'R':
          releaseShort();
          break;



        case '1':
          releaseShort();
          break;

        case '2':
          releaseShort();
          break;

        case '3':
          releaseShort();
          break;

        case '4':
          releaseShort();
          break;

        case 'P':
          releaseShort();
          break;



        case 'A':
          releaseShort();
          break;

        case 'B':
          releaseShort();
          break;

        case 'S':
          releaseShort();
          break;

        case 'T':
          releaseShort();
          break;
      }
      break;
  }
}

void sendCommand(byte byte1, byte byte2) {
  byte message[] = {0xFD, 0x03, 0x03};
  Serial.write(message, sizeof(message));
  Serial.write(byte1);
  Serial.write(byte2);
  delay(20);
}

void releaseButton() {
  byte message[] = {0xFD, 0x03, 0x03, 0x00, 0x00 };
  Serial.write(message, sizeof(message));
  delay(20); //a delay, to give to time to release the button.
}

void releaseShort() {
  byte message[] = {0xFE, 0x00};
  Serial.write(message, sizeof(message));
  delay(20); //a delay, to give to time to release the button.
}

void sendComKeys(byte byte1, byte byte2) {
  byte message[] = {0xFE, 0x02};
  Serial.write(message, sizeof(message));
  Serial.write(byte1);
  Serial.write(byte2);
  delay(20);
}


