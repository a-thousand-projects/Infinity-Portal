#include "menu.h"
#include "pixelRing.h"
#include <ArduinoLog.h>
Menu::Menu(PixelRing *pr):PixelProgram(pr)
{

}
Menu:: ~Menu()
{}

void Menu::Begin()
{
    // Set the Ring to White to White
    Log.info("Menu Begin" CR);
    DisplayMenu();
}


void Menu::DisplayMenu()
{
    pixelRing->clear();
    // TODO : There is an alignment issue when menu has an Odd Number of Menu Items
    // Calculate Center Position spacing
    uint8_t PixSpacing = (NUM_PIXELS/ CurrentMenu->MenuItemCount) ;
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
                d =  NUM_PIXELS-1-s;
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

void Menu::SelectMenu()
{
        menuItem_t *menu = GetSelectedMenu();
        pixelRing->blinkRing(menu->Colour,1,200);
        delay(50);
        DisplayMenu();
        if (fncBtnEnter != NULL)
        {
            menuItem_t *menuItem = GetSelectedMenu();
            (*fncBtnEnter)(menuItem->Id);
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

void Menu::MoveMenu(int8_t value)
{
    if (value == 0)
        return;
    uint8_t PixSpacing = (NUM_PIXELS/ CurrentMenu->MenuItemCount) ;
    
  //  Serial.print(" | value ");Serial.println(value);
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
    //        Serial.print("Menu: ");Serial.print(CurrentMenu->MenuItems[i].Itemname);Serial.print(" : ");Serial.println(CurrentMenu->MenuItems[i].Position);

        }
    }

    DisplayMenu();
};

void Menu::Clicked(uint8_t buttonNo)
{
    switch (buttonNo)
    {
       
        case BTN_UP: MoveMenu(1);break;
        case BTN_DOWN: MoveMenu(-1);break;
    }
}

