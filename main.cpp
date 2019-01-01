#include <iostream>
#include <GraphicsCore.h>

#include <vector>
#include <ctime>
#include <sstream>
#include <stdio.h>

using namespace std;

void drawPlayer(GraphicsCore core, int x, int y){
    core.drawOneSymb(point{x,y}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x-2,y}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x+2,y}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y+1}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y+2}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y+2}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y+3}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y+4}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y+2}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y+3}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y+4}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y-1}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y-2}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y-2}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y-2}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y-3}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y-3}, '*', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y-3}, '*', Color_Red, Color_Black);
}

void hidePlayer(GraphicsCore core, int x, int y){
    core.drawOneSymb(point{x,y}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x-2,y}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x+2,y}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y+1}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y+2}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y+2}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y+3}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y+4}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y+2}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y+3}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y+4}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y-1}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y-2}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y-2}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y-2}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x-1,y-3}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x+1,y-3}, ' ', Color_Red, Color_Black);
    core.drawOneSymb(point{x,y-3}, ' ', Color_Red, Color_Black);
}

int main()
{
    GraphicsCore GCore;
    /// Initialization of the console window. The method is overloaded,
    ///     if no arguments are passed, then the window size is taken from the system.
    /// Инициализация окна консоли. Метод перегружен, если не переданы аргументы
    ///     то размер окна устанавливается по умолчанию свойств консоли.
    GCore.init_graphics(80, 40);

    for (int i=0;i<16;i++){
        GCore.drawOrthogonalLine(point{0,i}, point{7,i}, true, GraphicsCore_Color(i), Color_Black);
    }

    GCore.drawOrthogonalLine(point{8,0}, point{8,16}, true, Color_Blue, Color_Black);

    GCore.drawOrthogonalRectangle(point{30,12}, point{45,25}, Color_Green, Color_GreenDark);
    GCore.drawOrthogonalRectangle(point{35,5}, point{55,15}, Color_Blue, Color_Black);

//    for (int i=170;i<400;i++){
//        GCore.drawOneSymb(point{i-170,0}, (char)i,Color_Green, Color_Black);
//    }

    GCore.drawOneSymb(point{20,2}, (char)176,Color_Green, Color_Black);
    GCore.drawOneSymb(point{21,2}, (char)177,Color_Green, Color_Black);
    GCore.drawOneSymb(point{22,2}, (char)178,Color_Green, Color_Black);

    GCore.drawOrthogonalRectangle(point{5,29}, point{35,31}, Color_Red, Color_Black);
    GCore.drawCentreText("test text", point{20,30}, Color_Red, Color_Black);
    GCore.drawOrthogonalRectangle(point{5,33}, point{35,35}, Color_BlueDark, Color_Black);
    GCore.drawLeftText("test text2", point{6,34}, Color_BlueDark, Color_Black);

    GCore.drawFill(point{40,33}, point{55,35}, Color_GreenDark);
    GCore.drawOrthogonalRectangle(point{40,33}, point{55,35}, Color_Green, Color_GreenDark);
    GCore.drawCentreText("TEST", point{48,34}, Color_Green, Color_GreenDark);


    GCore.ShowBuffer();

    int realTimer=clock() / (CLOCKS_PER_SEC/1000);
    int timer = realTimer + 3000;

    while (realTimer<timer){
        realTimer=clock() / (CLOCKS_PER_SEC/1000);
    }

    GCore.clearBuffer();

    GCore.drawOrthogonalRectangle(point{5,29}, point{35,31}, Color_Red, Color_Black);
    GCore.drawCentreText("Press arrows for moving", point{20,30}, Color_Red, Color_Black);

    char buff[20];
    int x=10;
    int y=10;
    GraphicsCore_Color NowColorRect = Color_Red;
    while (1){
        if (GetAsyncKeyState(VK_ESCAPE)&0x8000!=0) return 0;
        hidePlayer(GCore, x, y);
        if (GetAsyncKeyState(VK_UP)&0x8000!=0) y--;
        if (GetAsyncKeyState(VK_DOWN)&0x8000!=0) y++;
        if (GetAsyncKeyState(VK_LEFT)&0x8000!=0) x--;
        if (GetAsyncKeyState(VK_RIGHT)&0x8000!=0) x++;
        drawPlayer(GCore, x, y);

        realTimer=clock() / (CLOCKS_PER_SEC/1000);
        sprintf(buff, "%d ms", realTimer);
        GCore.drawOrthogonalRectangle(point{60,0}, point{79,2}, Color_Green, Color_Black);
        GCore.drawCentreText(buff, point{70,1}, Color_Green, Color_Black);

        if (realTimer>=timer){
            timer = realTimer + 1000;
            GCore.drawFill(point{5,5}, point{10,10}, NowColorRect);
            GCore.drawOrthogonalRectangle(point{5,5}, point{10,10}, NowColorRect, NowColorRect);
            NowColorRect = GraphicsCore_Color(rand()%16);
        }

        GCore.ShowBuffer();
    }

    return 0;
}
