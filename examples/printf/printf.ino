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
float p=M_PI;

void loop() {
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("This is an int : %d.\n", i?i*=-2:++i);
  printf("This is an uint32_t printed with %%"PRIu32": %"PRIu32".\n", j?j*=2:++j);
  printf("This is an uint64_t printed whith %%"PRIu64" : %"PRIu64".\n", k?k*=2:++k);
  printf("This is an uint64_t printed whith %%"PRIu32" : %"PRIu32".\n", k);
  printf("This is an float : %f\n", p*=10);
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
