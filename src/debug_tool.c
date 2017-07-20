#include "genesis.h"
#include "debug_tool.h"
#include "string.h"
#include "vdp_bg.h"

void logU16Int(char *key, u32 value, u16 xPos, u16 yPos) {
  char str[40];
  char strNum[16];
  uintToStr(value, strNum, 4);
  strcat(str, key);
  strcat(str, ": ");
  strcat(str, strNum);
  VDP_drawText(str, xPos, yPos);
}

void logs16Int(char *key, s32 value, u16 xPos, u16 yPos) {
  char str[40];
  char strNum[16];
  intToStr(value, strNum, 4);
  strcat(str, key);
  strcat(str, ": ");
  strcat(str, strNum);
  VDP_drawText(str, xPos, yPos);
}
