/*
  printfToSerial

  Some examples of printf uses.

  This example code is in the public domain.
*/

#include <printfToSerial.h>

void setup() {
  Serial.begin(115200);
}

int i=1;
uint32_t j=1;
uint64_t k=1;
float p=1;
double d=1;


void loop() {
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("This is an int : %d.\n", i?i*=-2:++i);
  printf("This is an uint32_t printed with %%"PRIu32": %"PRIu32".\n", j?j*=2:++j);
  printf("This is an uint64_t printed with %%"PRIu64" : %"PRIu64".\n", k?k*=2:++k);
  printf("This is an uint64_t printed with %%"PRIu32" : %"PRIu32".\n", k);
  char buffer[20];
  printf("This is an uint64_t printed in decimal with ulltoa : %s.\n", ulltoa(k,buffer,sizeof(buffer),10));
  printf("This is an uint64_t printed in hexadecimal with ulltoa : %s.\n", ulltoa(k,buffer,sizeof(buffer),16));
  printf("This is a float   : %f\n", M_PI*(p*=10));
  printf("This is a double  : %f\n", M_PI*(d*=10));
  printf("(Should look like : 314159265358979323846...)\n");
  char *boatTop="_/\\_";
  char *boatBottom="\\__/";
  printf("This boat is afloat ~~~~~~~%s~~~~~~~\n",boatTop);
  printf("                    ~~~~~~~%s~~~~~~~\n",boatBottom);
  // NOTE : no way to print directly very large int :(


  char *title="Heart diagram :";
  printf("%s\n          |  \\ \\ | |/ / \n          |  |\\ `' ' / \n          |  ;'aorta \\      / , pulmonary \n          | ;    _,   |    / / ,  arteries \n superior | |   (  `-.;_,-' '-' , \nvena cava | `,   `-._       _,-'_ \n          |,-`.    `.)    ,<_,-'_, pulmonary \n         ,'    `.   /   ,'  `;-' _,  veins \n        ;        `./   /`,    \\-' \n        | right   /   |  ;\\   |\\ \n        | atrium ;_,._|_,  `, ' \\ \n        |        \\    \\ `       `, \n        `      __ `    \\   left  ;, \n         \\   ,'  `      \\,  ventricle \n          \\_(            ;,      ;; \n          |  \\           `;,     ;; \n inferior |  |`.          `;;,   ;' \nvena cava |  |  `-.        ;;;;,;' \n          |  |    |`-.._  ,;;;;;' \n          |  |    |   | ``';;;'  FL \n                  aorta\n\n",title);
  // art from  aa906@FreeNet.Carleton.CA (Steve Wendt)
  printf("IMPORTANT : If you do not see a heart just above this line, then multiple \\n in the same format string fails\n");
  // NOTE : anything after the first \n may be dropped.
  delay(1324);
}
