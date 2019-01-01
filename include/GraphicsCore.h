#ifndef GRAPHICSCORE_H
#define GRAPHICSCORE_H

/// Indicates that the current operating system is newer than Windows 2000
#define _WIN32_WINNT 0x0500

#include <windows.h>     //for Windows console functions
#include <math.h>        //for sin, cos, abs
#include <iostream>

struct point{
    int x;
    int y;
};

enum GraphicsCore_Color
{
    Color_Black = 0,
    Color_Gray = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE,
    Color_White = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
    Color_RedDark = FOREGROUND_RED,
    Color_GreenDark = FOREGROUND_GREEN,
    Color_BlueDark = FOREGROUND_BLUE,
    Color_Red = FOREGROUND_RED|FOREGROUND_INTENSITY,
    Color_Green = FOREGROUND_GREEN|FOREGROUND_INTENSITY,
    Color_Blue = FOREGROUND_BLUE|FOREGROUND_INTENSITY,
    Color_Yellow = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY,
    Color_YellowDark = FOREGROUND_RED|FOREGROUND_GREEN,
    Color_Pink = FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
    Color_PinkDark = FOREGROUND_RED|FOREGROUND_BLUE,
    Color_Aqua = FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY,
    Color_AquaDark = FOREGROUND_GREEN|FOREGROUND_BLUE,
};

class GraphicsCore
{
    public:
        GraphicsCore();
        void init_graphics();
        void init_graphics(int WIDTH, int HEIGHT);
        void drawOrthogonalLine(point start, point stop, bool flagColoredStart, GraphicsCore_Color FColor, GraphicsCore_Color BColor);
        void drawOneSymb(point pos, char symb, GraphicsCore_Color FColor, GraphicsCore_Color BColor);
        void drawOrthogonalRectangle(point lt, point rb, GraphicsCore_Color FColor, GraphicsCore_Color BColor);
        void ShowBuffer();
        void drawCentreText(std::string text, point center, GraphicsCore_Color FColor, GraphicsCore_Color BColor);
        void drawLeftText(std::string text, point left, GraphicsCore_Color FColor, GraphicsCore_Color BColor);
        void drawFill(point lt, point rb, GraphicsCore_Color BColor);
        void clearBuffer();
        int get_WIDTH_SCREEN();
        int get_HEIGHT_SCREEN();

    private:
        HANDLE hConsole;
        CHAR_INFO *BackBuffer;

        unsigned int WIDTH_SCREEN;
        unsigned int HEIGHT_SCREEN;
};

#endif // GRAPHICSCORE_H
