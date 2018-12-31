#ifndef GRAPHICSCORE_H
#define GRAPHICSCORE_H

#define _WIN32_WINNT 0x0500

#include <windows.h>     //for Windows console functions
#include <conio.h>       //for kbhit(), getche()
#include <math.h>        //for sin, cos
#include <iostream>

struct point{
    int x;
    int y;
};

class GraphicsCore
{
    public:
        GraphicsCore();
        void init_graphics();
        void init_graphics(int WIDTH, int HEIGHT);
        void drawSimpleLine(point start, point stop, bool flagColoredStart, WORD inputColor);
        void drawOneSymb(point pos, char symb, WORD inputColor);
        void drawSimpleRectangle(point lt, point rb, WORD inputColor);
        void switchBuffer();
        void drawCentreText(std::string text, point center, WORD inputColor);
        void drawLeftText(std::string text, point left, WORD inputColor);
        void drawFill(point lt, point rb, WORD inputColor);
        void clearBuffer();

    private:
        HANDLE hConsole;
        CHAR_INFO *BackBuffer;

        unsigned int WIDTH_SCREEN;
        unsigned int HEIGHT_SCREEN;
};

#endif // GRAPHICSCORE_H
