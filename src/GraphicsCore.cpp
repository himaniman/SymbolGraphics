#include "GraphicsCore.h"

GraphicsCore::GraphicsCore()
{
    //ctor
}

void GraphicsCore::init_graphics()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WIDTH_SCREEN = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    HEIGHT_SCREEN = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    BackBuffer = new CHAR_INFO[WIDTH_SCREEN * HEIGHT_SCREEN];

    GraphicsCore::clearBuffer();

    GraphicsCore::hConsole = CreateFile("CONOUT$", GENERIC_WRITE | GENERIC_READ,
                          FILE_SHARE_READ | FILE_SHARE_WRITE,
                          0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);
}

void GraphicsCore::init_graphics(int width, int height){

    _COORD coord;
    _SMALL_RECT Rect;

    /// Initially, first a small 2x2 screen, then with the specified arguments.
    ///     It is necessary to hide the scrolling bands.
    coord.X = 2;
    coord.Y = 2;

    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = 2 - 1;
    Rect.Right = 2 - 1;

    GraphicsCore::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(GraphicsCore::hConsole, coord);
    SetConsoleWindowInfo(GraphicsCore::hConsole, TRUE, &Rect);

    coord.X = width;
    coord.Y = height;

    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = height - 1;
    Rect.Right = width - 1;

    GraphicsCore::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(GraphicsCore::hConsole, coord);
    SetConsoleWindowInfo(GraphicsCore::hConsole, TRUE, &Rect);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    WIDTH_SCREEN = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    HEIGHT_SCREEN = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    BackBuffer = new CHAR_INFO[WIDTH_SCREEN * HEIGHT_SCREEN];

    GraphicsCore::clearBuffer();

    GraphicsCore::hConsole = CreateFile("CONOUT$", GENERIC_WRITE | GENERIC_READ,
                          FILE_SHARE_READ | FILE_SHARE_WRITE,
                          0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);
}

void GraphicsCore::drawOrthogonalLine(point start, point stop, bool flagColoredStart, GraphicsCore_Color FColor, GraphicsCore_Color BColor)//функция рисующая линию(начало,конец, флаг использоваия,цвет)
{
    short smallLine=0; //1 - delta x = 2; 2 - delta y = 2
    if (!flagColoredStart && (start.x == stop.x || start.y == stop.y))
    {
        if (abs(start.x-stop.x) == 2) smallLine = 1;
        if (abs(start.y-stop.y) == 2) smallLine = 2;
        if (start.x != stop.x)
            start.x-=(start.x-stop.x)/abs(start.x-stop.x);
        if (start.x != stop.x)
            stop.x+=(start.x-stop.x)/abs(start.x-stop.x);
        if (start.y != stop.y)
            start.y-=(start.y-stop.y)/abs(start.y-stop.y);
        if (start.y != stop.y)
            stop.y+=(start.y-stop.y)/abs(start.y-stop.y);
    }
    if (start.x == stop.x && start.y != stop.y)
    {
        int pointY=start.y;
        do
        {
            drawOneSymb(point{start.x,pointY}, '\xB3', FColor, BColor);
            if (stop.y>pointY)
                pointY++;
            if (stop.y<pointY)
                pointY--;
        }
        while (pointY!=stop.y);
        drawOneSymb(point{start.x,pointY}, '\xB3', FColor, BColor);
    }
    if (smallLine == 2) {
        drawOneSymb(point{start.x,start.y}, '\xB3', FColor, BColor);
    }
    if (start.y == stop.y && start.x != stop.x)
    {
        int pointX=start.x;
        do
        {
            drawOneSymb(point{pointX,start.y}, '\xC4', FColor, BColor);
            if (stop.x>pointX)
                pointX++;
            if (stop.x<pointX)
                pointX--;
        }
        while (pointX!=stop.x);
        drawOneSymb(point{pointX,start.y}, '\xC4', FColor, BColor);
    }
    if (smallLine == 1) {
        drawOneSymb(point{start.x,start.y}, '\xC4', FColor, BColor);
    }
}

void GraphicsCore::drawOneSymb(point pos, char symb, GraphicsCore_Color FColor, GraphicsCore_Color BColor)
{
    if (pos.y>=HEIGHT_SCREEN || pos.x>=WIDTH_SCREEN || pos.y<0 || pos.x<0) return;
    BackBuffer[pos.y*WIDTH_SCREEN+pos.x].Char.UnicodeChar=symb;
    /// The color is determined by the sum of FColor | (BColor << 4),
    ///     since BColor is stored as the upper 4 bits in the color buffer.
    BackBuffer[pos.y*WIDTH_SCREEN+pos.x].Attributes = FColor|(BColor<<4);
}

void GraphicsCore::drawOrthogonalRectangle(point lt, point rb, GraphicsCore_Color FColor, GraphicsCore_Color BColor)
{
    point rt{rb.x, lt.y};
    point lb{lt.x, rb.y};
    drawOneSymb(lt, '\xDA',FColor, BColor);
    drawOneSymb(lb, '\xC0',FColor, BColor);
    drawOneSymb(rt, '\xBF',FColor, BColor);
    drawOneSymb(rb, '\xD9',FColor, BColor);

    drawOrthogonalLine(lt,rt,false,FColor, BColor);
    drawOrthogonalLine(lt,lb,false,FColor, BColor);
    drawOrthogonalLine(rb,rt,false,FColor, BColor);
    drawOrthogonalLine(rb,lb,false,FColor, BColor);
}

void GraphicsCore::ShowBuffer()
{
    SMALL_RECT writeArea= {0,0,WIDTH_SCREEN,HEIGHT_SCREEN};
    COORD charPosition= {0,0};
    COORD bufferSize = {WIDTH_SCREEN,HEIGHT_SCREEN};

    WriteConsoleOutput(hConsole, BackBuffer, bufferSize,
                       charPosition, &writeArea);
}

void GraphicsCore::drawCentreText(std::string text, point center, GraphicsCore_Color FColor, GraphicsCore_Color BColor)
{
    int lenght = text.length();
    int leftBord = center.x - lenght/2;

    for (int i=0; i<lenght; i++)
    {
        if (i<=HEIGHT_SCREEN)
            drawOneSymb(point{leftBord+i,center.y}, text[i], FColor, BColor);
    }
}

void GraphicsCore::drawFill(point lt, point rb, GraphicsCore_Color BColor)
{
    for (int x=lt.x; x<=rb.x; x++)
    {
        for (int y=lt.y; y<=rb.y; y++)
        {
            drawOneSymb(point{x,y}, ' ', GraphicsCore_Color(Color_Black), BColor);
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

void GraphicsCore::drawLeftText(std::string text, point left, GraphicsCore_Color FColor, GraphicsCore_Color BColor){
    int lenght = text.length();

    for (int i=0; i<lenght; i++)
    {
        if (i<=HEIGHT_SCREEN)
            drawOneSymb(point{left.x+i,left.y}, text[i], FColor, BColor);
    }
}

int GraphicsCore::get_WIDTH_SCREEN(){
    return WIDTH_SCREEN;
}
int GraphicsCore::get_HEIGHT_SCREEN(){
    return HEIGHT_SCREEN;
}
