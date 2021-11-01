#ifndef Menu_h
#define Menu_h
#include "pixelProgram.h"
#include "config.h"
#include "pixelRing.h"

#define MinMenuPixellength 5
#define MinMenuSpacerPixellength 2


typedef struct {
    String Itemname;
    uint32_t Colour;
    uint8_t Position;
} menuItem_t;

typedef struct {
    String MenuName;
    uint8_t MenuItemCount; 
    menuItem_t MenuItems[10];
} menuCollection_t;


class Menu: public  PixelProgram
{
    private: 
        menuCollection_t *CurrentMenu;
        uint8_t menuRotaryValue;
    public:
        Menu(PixelRing *pr);
        ~Menu();
        void SetMenu(menuCollection_t *menu);
        void Begin();
        void DisplayMenu();

        void RunStep();
        void SetValueOne(int8_t value);
        void SetValueTwo(int8_t value);
        void SetValueThree(int8_t value);
        void SetValueFour(int8_t value);

        void SetMenuRotaryValue(uint16_t value){menuRotaryValue = value;};
        uint16_t GetMenuRotaryValue(){return menuRotaryValue; };
};

#endif 