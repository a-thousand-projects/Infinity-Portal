#include "menu.h"
#include "pixelRing.h"
Menu::Menu(PixelRing *pr):PixelProgram(pr)
{}
Menu:: ~Menu()
{}

void Menu::Begin()
{
    // Set the Ring to White to White
    Serial.println("Menu Begin");
    DisplayMenu();
}

void Menu::DisplayMenu()
{

    // Number of Items by Pixel Length and Spacer tailLength
    uint8_t totalLength = CurrentMenu->MenuItemCount * (MinMenuPixellength);
    uint8_t spacerPixelLength;
   // spacerPixelLength = (GetNeoPixels()->numPixels() -  totalLength) /CurrentMenu->MenuItemCount ;
    // Spacer must a an Even Number
    if (spacerPixelLength%2 > 0)
        spacerPixelLength +=1;

    Serial.print("Spacer length :");
    Serial.println(spacerPixelLength);



    uint8_t i = 0;
    uint8_t px = 0;
    for (i = 0; i < CurrentMenu->MenuItemCount;i++) 
    {
        // write in Half the Spacer
        for (uint8_t l = 0; l < spacerPixelLength/2;l++)
        {
           // GetNeoPixels()->setPixelColor(px,BLACK);
            px+=1;
        }
        // write in the Menu Item
        for (uint8_t l = 0; l < MinMenuPixellength;l++)
        {           
          //  GetNeoPixels()->setPixelColor(px,CurrentMenu->MenuItems[i].Colour);
            px+=1;
        }
        // write in Half the Spacer
        for (uint8_t l = 0; l < spacerPixelLength/2;l++)
        {
           // GetNeoPixels()->setPixelColor(px,BLACK);
            px+=1;
        }
    }
    //PixelRing()->show();
}

void Menu::SetMenu(menuCollection_t *menu)
{
    CurrentMenu = menu;
}




void Menu::RunStep(){};
void Menu::SetValueOne(int8_t value){};
void Menu::SetValueTwo(int8_t value){};
void Menu::SetValueThree(int8_t value){};
void Menu::SetValueFour(int8_t value)
{
   
    if (GetMenuRotaryValue() != value){
        SetMenuRotaryValue(value);
         Serial.print("MENU Select : ");Serial.println(value);
    }
    
};