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
    GCore.init_graphics(40,30);

    for (int i=0;i<16;i++){
        GCore.drawSimpleLine(point{0,i}, point{7,i}, true, GraphicsCore_Color(i), GraphicsCore_Color(Color_Black));
    }

    GCore.drawSimpleLine(point{8,0}, point{8,16}, true, Color_Blue, Color_Black);

    GCore.drawSimpleRectangle(point{30,12}, point{39,25}, Color_Green, Color_GreenDark);

    GCore.switchBuffer();

    while (1){
        if (GetAsyncKeyState(VK_UP)&0x8000!=0) return 0;
    }

    return 0;
}
