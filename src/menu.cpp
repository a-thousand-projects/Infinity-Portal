#include "menu.h"
#include "pixelRing.h"
Menu::Menu(PixelRing *pr):PixelProgram(pr)
{
    pixelRing = pr;
}
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
    uint16_t spacerPixelLength;
    spacerPixelLength = (NUMPIXELS -  totalLength) /CurrentMenu->MenuItemCount ;
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
            
            pixelRing->setPixel(px,BLACK);
            px+=1;
        }
        // write in the Menu Item
        for (uint8_t l = 0; l < MinMenuPixellength;l++)
        {           
            pixelRing->setPixel(px,CurrentMenu->MenuItems[i].Colour);
            px+=1;
        }
        // write in Half the Spacer
        for (uint8_t l = 0; l < spacerPixelLength/2;l++)
        {
            pixelRing->setPixel(px,BLACK);
            px+=1;
        };
    }
    pixelRing->show();
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
    if (value == 0)
        return;
   uint16_t currentValue = GetMenuRotaryValue();
   
    if (currentValue != value){
    Serial.print("current value: ");Serial.print(currentValue),Serial.print(" | value ");Serial.println(value);
        SetMenuRotaryValue(value);
    //    pixelRing->rotate(value);
     //   pixelRing->show();
    }
    
};