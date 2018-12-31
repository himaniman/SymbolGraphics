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

    GCore.drawSimpleLine(point{10,10}, point{20,10}, true, FOREGROUND_RED);
    GCore.drawSimpleRectangle(point{30,12}, point{39,25}, FOREGROUND_RED);

    GCore.switchBuffer();

    while (1){
        if (GetAsyncKeyState(VK_UP)&0x8000!=0) return 0;
    }

    return 0;
}
