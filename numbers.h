#ifndef NUMBERS_H
#define NUMBERS_H

void drawScore(long score){
  
  char charBuf[7];
  int i;
  int pad = 0;
    
  // convert the int to a string?
  itoa(score, charBuf, 10);

  // Add leading zeros:
  if(score >= 1000000) pad = 0;
  if(score < 1000000) pad = 1;
  if(score < 100000) pad = 2;
  if(score < 10000) pad = 3;
  if(score < 1000) pad = 4;
  if(score < 100) pad = 5;
  if(score < 10) pad = 6;
  
  for(i = 0; i <= pad; i++){
    //Sprites::drawOverwrite(50 + (i * 4), 0, num0, 0);
  }

  for(i = 0; i < sizeof(charBuf); i++){
    // blit a number here...
    // This is a real-time string compare, for better or for worse...

    /*
    if(charBuf[i] == '0')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num0, 0);
    if(charBuf[i] == '1')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num1, 0);
    if(charBuf[i] == '2')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num2, 0);
    if(charBuf[i] == '3')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num3, 0);
    if(charBuf[i] == '4')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num4, 0);
    if(charBuf[i] == '5')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num5, 0);
    if(charBuf[i] == '6')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num6, 0);
    if(charBuf[i] == '7')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num7, 0);
    if(charBuf[i] == '8')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num8, 0);
    if(charBuf[i] == '9')  
      Sprites::drawOverwrite(50 + ((i + pad) * 4), 0, num9, 0);

    */
  }
}

#endif
