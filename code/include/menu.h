#ifndef Menu_h
#define Menu_h
#include "pixelProgram.h"
#include "config.h"
#include "pixelRing.h"

#define MinMenuPixellength 5
#define MinMenuSpacerPixellength 2


typedef struct {
    uint8_t Id;
    String Itemname;
    uint32_t Colour;
    uint32_t HiColour;
    int8_t Position;
    PixelProgram *  program;
} menuItem_t;

typedef struct {
    String MenuName;
    uint8_t MenuItemCount; 
    menuItem_t MenuItems[10];
    uint8_t currentMenuItem;
} menuCollection_t;


class Menu: public  PixelProgram
{
    private: 
        menuCollection_t *CurrentMenu;
        uint8_t menuRotaryValue;
    public:
        Menu(PixelRing *pr);
        ~Menu();
        void SetMenu(menuCollection_t *menuItem);
        void Begin();
        void DisplayMenu();
        void RunStep();
        void MoveMenu(int8_t value);
        void SelectMenu();
        void Clicked(uint8_t buttonNo);
        menuItem_t* GetSelectedMenu();
        void AttachCallBack(void (*cback)(int));

        void SetMenuRotaryValue(uint16_t value){menuRotaryValue = value;};
        uint16_t GetMenuRotaryValue(){return menuRotaryValue; };

};

#endif 