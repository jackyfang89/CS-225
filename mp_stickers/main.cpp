#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image background; background.readFromFile("background.png");
  Image leo; leo.readFromFile("leo.png");
  Image monster; monster.readFromFile("monster.png");
  Image text; text.readFromFile("text.png");
  Image i; i.readFromFile("i.png");

  monster.scale(0.35);
  i.scale(0.4);

  StickerSheet sheet(background, 5);
  sheet.addSticker(leo, 0, 120);
  sheet.addSticker(monster, 0, 430);
  sheet.addSticker(text, 0, 0);
  sheet.addSticker(i, 430, 480);
  
  Image result = sheet.render();
  result.writeToFile("myImage.png");
  return 0;
}
