
void setup()
{
  Serial.begin(115200);
  Serial.print("Access point in: ");
}

void loop()
{
  if (Serial.available()) {
    int a = Serial.read();
    if (a ==96)
      Serial.println("Hola");

    
  }
  delay(2220);
  Serial.println("hola");
 delay(2220);



}
