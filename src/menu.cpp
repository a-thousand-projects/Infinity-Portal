#include "menu.h"
#include "pixelRing.h"
Menu::Menu(PixelRing *pr):PixelProgram(pr)
{
  //  pixelRing = pr;
}
Menu:: ~Menu()
{}

void Menu::Begin()
{
    // Set the Ring to White to White
    Serial.println("Menu Begin");
    DisplayMenu();
}

void Menu::AttachCallBack(void (*cback)())
{
    callBack = cback;
}

void Menu::DisplayMenu()
{
    // TODO : This is an alignment issue when menu has an Odd Number of Menu Items
    // Calculate Center Position spacing
    uint8_t PixSpacing = (NUMPIXELS/ CurrentMenu->MenuItemCount) ;
    // Put in centre pixel
    for (uint8_t i=0;i<CurrentMenu->MenuItemCount;i++)
    {
        bool isCentre = CurrentMenu->MenuItems[i].Position * PixSpacing==0;
        if (isCentre)
            pixelRing->setPixel(CurrentMenu->MenuItems[i].Position * PixSpacing,CurrentMenu->MenuItems[i].HiColour);
        else
            pixelRing->setPixel(CurrentMenu->MenuItems[i].Position * PixSpacing,CurrentMenu->MenuItems[i].Colour);
        // Draw in sides of menu
        for (uint8_t s=0;s<(MinMenuPixellength-1)/2;s++)
        {
            pixelRing->setPixel((CurrentMenu->MenuItems[i].Position*PixSpacing)+1+s,CurrentMenu->MenuItems[i].Colour);
            int8_t d = (CurrentMenu->MenuItems[i].Position*PixSpacing)-1-s;
            if (d<0)
                d =  NUMPIXELS-1-s;
            pixelRing->setPixel(d,CurrentMenu->MenuItems[i].Colour);
        }
        
    }
    
    pixelRing->show();
}

void Menu::SetMenu(menuCollection_t *menu)
{
    CurrentMenu = menu;
}

void Menu::RunStep(){};
void Menu::SetValueOne(int16_t value){};
void Menu::SetValueTwo(int16_t value){};
void Menu::SetValueThree(int16_t value){};

void Menu::Clicked(uint8_t buttonNo)
{
    if (buttonNo == 4)
    {
        menuItem_t *menu = GetSelectedMenu();
        pixelRing->blinkRing(menu->Colour,1,200);
        delay(50);
        DisplayMenu();
        if (callBack != NULL)
            (*callBack)();
    }
   
}

// Gets the current menu at Position 0
// Returns Null is none (which should never be the case)
menuItem_t* Menu::GetSelectedMenu()
{
    for (uint8_t i=0;i<CurrentMenu->MenuItemCount;i++)
    {
        if (CurrentMenu->MenuItems[i].Position == 0)
        {
            return &CurrentMenu->MenuItems[i];
            break;
        }
    }
    return nullptr;
}

void Menu::SetValueFour(int16_t value)
{
    uint8_t PixSpacing = (NUMPIXELS/ CurrentMenu->MenuItemCount) ;
    if (value == 0)
        return;
    Serial.print(" | value ");Serial.println(value);
    for (uint8_t r=0;r< PixSpacing;r++)
    {
        pixelRing->rotate(value);
        pixelRing->show();
        delay(10);
    }
    
    pixelRing->show();
    if (value>0)
    {
        for (uint8_t i=0;i<CurrentMenu->MenuItemCount;i++)
        {
            CurrentMenu->MenuItems[i].Position ++;
            if (CurrentMenu->MenuItems[i].Position>CurrentMenu->MenuItemCount-1)
                CurrentMenu->MenuItems[i].Position=0;
        }
    }
    else if (value<0)
    {
        for (uint8_t i=0;i<CurrentMenu->MenuItemCount;i++)
        {
            CurrentMenu->MenuItems[i].Position --;
            if (CurrentMenu->MenuItems[i].Position < 0)
            {
                CurrentMenu->MenuItems[i].Position = CurrentMenu->MenuItemCount-1;
            }
            Serial.print("Menu: ");Serial.print(CurrentMenu->MenuItems[i].Itemname);Serial.print(" : ");Serial.println(CurrentMenu->MenuItems[i].Position);

        }
    }

    DisplayMenu();
};