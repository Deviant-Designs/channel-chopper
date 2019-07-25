// recieved message will be "Shock¬1¬1" this equates to channel 1, turn on


const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

char message1FromPC[32] = {0};
char message2FromPC[32] = {0};
char message3FromPC[32] = {0};

char recvChar;
char endMarker = '\n';

int shockChannelPinArray[] = {6,7,8,9}; //holds the pins for the LED channel outputs
int shockChannelPinArray2[] = {5,4,3,2,A3}; //holds the pins for the octocouplers ADD A3 WHEN WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int buttonChannelPinArray[] = {15,14,16,10}; //CHANGE THIS TO MATCH BUTTON PINS!!!!!!!!!!!!!

int shockChannelActive[] = {0,0,0,0};
int buttonShockChannelActive[] = {0,0,0,0};

void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");
 for (int i = 0; i<(sizeof(shockChannelPinArray)/sizeof(shockChannelPinArray[0])); i++) {
  pinMode(shockChannelPinArray[i], OUTPUT);
 } 
 for (int i = 0; i<4; i++) {
  pinMode(shockChannelPinArray2[i], OUTPUT);
  pinMode(buttonChannelPinArray[i], INPUT_PULLUP);
 }
 pinMode(shockChannelPinArray2[4], OUTPUT);
}

void loop() {
 recvWithEndMarker();
 showNewData();
buttonPress();
 serialDebug();
 actualShock();  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void serialDebug() {
  Serial.print ("Shock Channel Active Array - ");
  for (int i = 0; i<=(sizeof(buttonChannelPinArray) / sizeof(shockChannelPinArray[0]))-1; i++){
    Serial.print("[");
  Serial.print (shockChannelActive[i]);
  Serial.print("]");
  }
  Serial.println("");
  Serial.print ("Button Channel Active Array - ");
  for (int i = 0; i<=(sizeof(buttonChannelPinArray) / sizeof(buttonChannelPinArray[0]))-1; i++){
    Serial.print("[");
    Serial.print (buttonShockChannelActive[i]);
    Serial.print("]");
  }
  Serial.println("");
}

//This func recieves the incoming serial data and adds it to a Char array. 
//when end marker is recieved it sets newdata flag to true
void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;

 // if (Serial.available() > 0) {
   while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
      }
  }
}


//if newData flag is triggered then parse the data
void showNewData() {
  if (newData == true) {
//  Serial.print("This just in ... ");
//  Serial.println(receivedChars);
  newData = false;
  parseData();
//  showParsedData();
   shock();
  }
}

void parseData() {

    // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(receivedChars,"¬");      // get the first part - the string
  strcpy(message1FromPC, strtokIndx); // copy it to messageFromPC
  strtokIndx = strtok(NULL,"¬");      // get the first part - the string
  strcpy(message2FromPC, strtokIndx); // copy it to messageFromPC
  strtokIndx = strtok(NULL,"¬");      // get the first part - the string
  strcpy(message3FromPC, strtokIndx); // copy it to messageFromPC
 // strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
 // integerFromPC = atoi(strtokIndx);     // convert this part to an integer
  // strtokIndx = strtok(NULL, ",");
  // floatFromPC = atof(strtokIndx);     // convert this part to a float

}

void shock() {
//  Serial.println("shock func running");
  if (strcmp(message1FromPC,"shock")==0) {
  int integer1FromPC = atoi(message2FromPC)-1; //convert string to int. Channels coming in would be 1-4, make 0-3
  int integer2FromPC = atoi(message3FromPC);
  
    if (integer1FromPC >= 0 && integer1FromPC < 4) {
    shockChannelActive[integer1FromPC] = integer2FromPC;  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }

}
}

void buttonPress() {
  //Serial.print(sizeof(buttonChannelPinArray) / sizeof(shockChannelPinArray[0]));
  for (int i = 0; i<4; i++) {
    if (digitalRead(buttonChannelPinArray[i])==LOW) {
      buttonShockChannelActive[i] = 1;
    } else {
      buttonShockChannelActive[i] = 0;
    }
  }
  //Serial.print ("Button Shock - ");

 // Serial.println("");
}

void actualShock() {   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 for (int i = 0; i<4; i++) {
   if (buttonShockChannelActive[i] == 1 || shockChannelActive[i] == 1) {
     digitalWrite(shockChannelPinArray[i], HIGH);
     digitalWrite(shockChannelPinArray2[i], HIGH);
     if (buttonShockChannelActive[3] == 1 || shockChannelActive[3] == 1) {
      digitalWrite(shockChannelPinArray2[4], HIGH);
     }
   }  else {
   digitalWrite(shockChannelPinArray[i], LOW);
   digitalWrite(shockChannelPinArray2[i], LOW);
       if (buttonShockChannelActive[3] == 0 || shockChannelActive[3] == 0) {
      digitalWrite(shockChannelPinArray2[4], LOW);
     }
 }
}
}
