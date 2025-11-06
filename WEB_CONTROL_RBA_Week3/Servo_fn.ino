//-----------------------------------------------Servo1 Function--------------------------------------------------//

void M1_1() {
  pos1++;
  delay(delay_value);
  Serial.print("servo1 ");
  Serial.println(pos1);
  idektep.setPWM(servo1, 0, angleToPulse(pos1));
  if (pos1 >= 160) {
    pos1 = 160;
    idektep.setPWM(servo1, 0, angleToPulse(pos1));
  }
}



void M1_2() {
  pos1--;
  delay(________);
  Serial.print("________ ");
  Serial.println(________);
  idektep.setPWM(________, 0, angleToPulse(________));
  if (pos1 <= 0) {
    pos1 = 0;
    idektep.setPWM(________, 0, angleToPulse(________));
  }
}

