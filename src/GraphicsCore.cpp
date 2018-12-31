#include "GraphicsCore.h"

GraphicsCore::GraphicsCore()
{
    //ctor
}

void GraphicsCore::init_graphics()
{
    WORD attrib = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    for(int x=0; x<WIDTH_SCREEN*HEIGHT_SCREEN; x++)
    {
        GraphicsCore::BackBuffer[x].Char.UnicodeChar=' ';
        GraphicsCore::BackBuffer[x].Attributes = attrib;
    }


    GraphicsCore::hConsole = CreateFile("CONOUT$", GENERIC_WRITE | GENERIC_READ,
                          FILE_SHARE_READ | FILE_SHARE_WRITE,
                          0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);


}

void GraphicsCore::drawSimpleLine(point start, point stop, bool flagColoredStart, WORD inputColor)//функция рисующая линию(начало,конец, флаг использоваия,цвет)
{
    if (!flagColoredStart)//закрашивает начало и коенц
    {
        if (start.x != stop.x)
            start.x-=(start.x-stop.x)/abs(start.x-stop.x);
        if (start.x != stop.x)
            stop.x+=(start.x-stop.x)/abs(start.x-stop.x);
        if (start.y != stop.y)
            start.y-=(start.y-stop.y)/abs(start.y-stop.y);
        if (start.y != stop.y)
            stop.y+=(start.y-stop.y)/abs(start.y-stop.y);
    }
    if (start.x == stop.x)//для оформления начала или конца линии(рисует уголок)
    {
        int pointY=start.y;
        do
        {
            drawOneSymb(point{start.x,pointY}, '\xB3', inputColor);
            if (stop.y>pointY)
                pointY++;
            if (stop.y<pointY)
                pointY--;
        }
        while (pointY!=stop.y);
        drawOneSymb(point{start.x,pointY}, '\xB3', inputColor);
    }
    if (start.y == stop.y)
    {
        int pointX=start.x;
        do
        {
            drawOneSymb(point{pointX,start.y}, '\xC4', inputColor);
            if (stop.x>pointX)
                pointX++;
            if (stop.x<pointX)
                pointX--;
        }
        while (pointX!=stop.x);
        drawOneSymb(point{pointX,start.y}, '\xC4', inputColor);
    }
}

void GraphicsCore::drawOneSymb(point pos, char symb, WORD inputColor)//рисует символ(позиция, код символва, цвет)
{
    BackBuffer[pos.y*WIDTH_SCREEN+pos.x].Char.UnicodeChar=symb;//вывод через буфер, координата символа(рсчет в одномерном массиве)
    BackBuffer[pos.y*WIDTH_SCREEN+pos.x].Attributes = inputColor;//цвет
}

void GraphicsCore::drawSimpleRectangle(point lt, point rb, WORD inputColor)//рисует прямоуольнки по левой верхней и нижей правой координате
{
    point rt{rb.x, lt.y};
    point lb{lt.x, rb.y};
    drawOneSymb(lt, '\xDA',inputColor);
    drawOneSymb(lb, '\xC0',inputColor);
    drawOneSymb(rt, '\xBF',inputColor);
    drawOneSymb(rb, '\xD9',inputColor);

    drawSimpleLine(lt,rt,false,inputColor);
    drawSimpleLine(lt,lb,false,inputColor);
    drawSimpleLine(rb,rt,false,inputColor);
    drawSimpleLine(rb,lb,false,inputColor);
}

void GraphicsCore::switchBuffer()//чета буфер
{
    SMALL_RECT writeArea= {0,0,WIDTH_SCREEN,HEIGHT_SCREEN};
    COORD charPosition= {0,0};
    COORD bufferSize = {WIDTH_SCREEN,HEIGHT_SCREEN};

    WriteConsoleOutput(hConsole, BackBuffer, bufferSize,
                       charPosition, &writeArea);
}

void GraphicsCore::drawCentreText(std::string text, point center, WORD inputColor)//текст,координата центра,цвет
{
    int lenght = text.length();//длина текста
    int leftBord = center.x - lenght/2;//начало для вывода текста

    for (int i=0; i<lenght; i++)//вывод текста посимвольно
    {
        if (i<=HEIGHT_SCREEN)
        drawOneSymb(point{leftBord+i,center.y}, text[i], inputColor);
    }
}

void GraphicsCore::drawFill(point lt, point rb, WORD inputColor)//закрашивание заднего плана прямоугольника
{

    for (int x=lt.x; x<=rb.x; x++)
    {
        for (int y=lt.y; y<=rb.y; y++)
        {
            drawOneSymb(point{x,y}, ' ', inputColor);
        }
    }

}

void GraphicsCore::clearBuffer(){
    WORD attrib = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    for(int x=0; x<WIDTH_SCREEN*HEIGHT_SCREEN; x++)
    {
        BackBuffer[x].Char.UnicodeChar=' ';
        BackBuffer[x].Attributes = attrib;
    }
}

void GraphicsCore::drawLeftText(std::string text, point left, WORD inputColor){//вывод текста слева?
    int lenght = text.length();

    for (int i=0; i<lenght; i++)
    {
        if (i<=HEIGHT_SCREEN)
        drawOneSymb(point{left.x+i,left.y}, text[i], inputColor);
    }
}
