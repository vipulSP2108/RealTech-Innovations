#include <wiringPi.h>
#include <stdio.h>
#include <string.h>

#define LED_PIN 1
#define DELAY_TIME 1000

char wordinputed[256];

int main(void) {
  if (wiringPiSetup() == -1) {
    printf("wiringPiSetup failed. Exiting...");
    return 1;
  }

  pinMode(LED_PIN, OUTPUT);

  while(1) {
    while (serialDataAvail(0) <= 0) { }
    fgets(wordinputed, sizeof(wordinputed), stdin);
    wordinputed[strcspn(wordinputed, "\r\n")] = 0; // Remove newline character

    printf("%s\n", wordinputed);

    if (strcmp(wordinputed, "ASA") == 0) {
      digitalWrite(LED_PIN, HIGH);
      delay(5000);
      digitalWrite(LED_PIN, LOW);
      delay(1000);
    }
  }

  return 0;
}
