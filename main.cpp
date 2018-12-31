#include <iostream>
#include <GraphicsCore.h>

#include <vector>
#include <ctime>
#include <sstream>
#include <stdio.h>

using namespace std;

int main()
{
    GraphicsCore GCore;
    GCore.init_graphics(80,40);

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

    while (1){
        if (GetAsyncKeyState(VK_ESCAPE)&0x8000!=0) return 0;
    }

    return 0;
}
