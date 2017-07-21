#include "genesis.h"
#include "debug_tool.h"
#include "resources.h"

#define MODE_SEGA_LOGO_BOOT 0
#define MODE_MD_LOGO_DISPLAY 1

void animateSegaLogo(s16 left, s16 right, s16 *hscroll);
void setUpSegaLogoToAnimate(u32 sega_logo_width, u32 sega_logo_height);

u8 game_mode;

u16 sega_logo_screen_offset = 112;

int main() {
  // Init first scene
  game_mode = MODE_SEGA_LOGO_BOOT;
  setUpSegaLogoToAnimate(segalogo.w, segalogo.h);
  s16 leftScrollPos = 0 - (sega_logo_screen_offset + segalogo.w);
  s16 rightScrollPos = sega_logo_screen_offset + segalogo.w;
  s16 hscroll[VDP_getScreenHeight()];

  // TODO Don't need this right now but will need when sprites
  SPR_init(16, 256, 256);

  // GAME LOOP START
  while (1) {
    // Sega Logo Animation
    if (game_mode == MODE_SEGA_LOGO_BOOT){
      if (leftScrollPos < 0 && rightScrollPos > 0) {
        leftScrollPos += 2;
        rightScrollPos -= 2;
        animateSegaLogo(leftScrollPos, rightScrollPos, hscroll);
      } else {
        // Animation Finished - Cleaup Display
        waitTick(TICKPERSECOND);
        VDP_fadeOutAll(20, 0);
        waitTick(TICKPERSECOND);
        VDP_clearPlan(PLAN_B,1);
        VDP_waitDMACompletion();

      }
    }
    else if (game_mode == MODE_MD_LOGO_DISPLAY){




    }



    VDP_waitVSync();
  }
  return (0);
}

void setUpSegaLogoToAnimate(u32 sega_logo_width, u32 sega_logo_height){
  VDP_setPalette(PAL1, segalogo.palette->data);
  // load classic sega logo
  VDP_loadBMPTileData((u32 *)segalogo.image, 1, sega_logo_width / 8,
                      sega_logo_height / 8, sega_logo_width / 8);
  // Position logo on screen
  VDP_fillTileMapRectInc(PLAN_B, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), 14, 12,
                         sega_logo_width / 8, sega_logo_height / 8);
  // Need to set scrolling mode to get sega logo effect to work
  VDP_setScrollingMode(HSCROLL_LINE, VSCROLL_PLANE);
}

void animateSegaLogo(s16 left, s16 right, s16 *hscroll) {
  //logs16Int("left pos is", left, 2, 2);
  //logs16Int("right pos is", right, 2, 4);
  int i;
  for (i = 0; i < VDP_getScreenHeight(); i++) {
    if (i % 2 == 0) {
      hscroll[i] = left;
    } else {
      hscroll[i] = right;
    }
  }
  VDP_setHorizontalScrollLine(PLAN_B, 0, hscroll, VDP_getScreenHeight(), FALSE);
}
