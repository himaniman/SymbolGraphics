# Symbol Graphics class
Class for works with WIN API output ASCII graphics

## Описание
Класс позволяет выводить в консоль Windows (cmd.exe) графические примитивы и текст с указанием цвета и координат. Можно устанавливать цвет символа и цвет фона для символа.
```
Ключевые слова: консольная графика windows терминал отображать построить линию прямоугольник цветная графика пиксельная графика псевдографика библиотека класс
keywords: ASCII grapchis windows cmd console
```

## Доступные методы
* init_graphics() 
> Выделение памяти по буффер размера текущей сессии командной строки (по умолчанию в Windows это 80х25), очистка буфера. Метод обязательно должен быть вызван до рисования.
* init_graphics(int WIDTH, int HEIGHT)
> Выделение памяти по буффер размера WIDTH х HEIGHT, очистка буфера. Метод обязательно должен быть вызван до рисования.
* ShowBuffer()
> Отображение буфера на экран (при слишком частом вызове может привести к мерцанию экрана). Не очищает буфер класса, просто копирует буфер класса в буфер экрана консоли.
* clearBuffer()
> Очистка буфера от символов и цвета, заполняет буфер пробелами с черным цветом фона.
* int get_WIDTH_SCREEN() и int get_HEIGHT_SCREEN()
> Возвращают размеры экрана. В случае если перед этим в методе init_graphics() не были переданы аргументы размера экрана, позволяет узнать текущий размер экрана по умолчанию.
* drawOneSymb(point pos, char symb, GraphicsCore_Color FColor, GraphicsCore_Color BColor)
> Выводит в заданную позицию буфера **pos** заданный символ **symb** с цветом символа **FColor** и цветом фона **BColor**. Пример *ObjName.drawOneSymb(point{20,2}, 's',Color_Green, Color_Black)*
* drawOrthogonalLine(point start, point stop, bool flagColoredStart, GraphicsCore_Color FColor, GraphicsCore_Color BColor)
> Выводит линию с помощью псевдографики "- ¦" начиная с координат **start** и заканчивая координатами **stop** с цветом линии **FColor** и цветом фона **BColor**. Если **flagColoredStart** истина то линия рисуется включая переданные координаты. Строит вертикальную или горизонтальную линию в зависимости от координат. Не строит линии где start.x != stop.x && start.y != stop.y.
* drawOrthogonalRectangle(point lt, point rb, GraphicsCore_Color FColor, GraphicsCore_Color BColor)
> Выводит прямоугольник с помощью псевдографики "-¬L-¦-" начиная с левого верхнего угла **lt** и заканчивая правым нижним углом **rb** включительно с цветом линий **FColor** и цветом фона **BColor**. При построении прямоугольника важно указывать верхний левый угол и нижний правый угол для корректного отображения. При выводе прямоугольника не очищается и не закрашивается внутренее пространство прямоугольника, для его изменения использовать drawFill().
* drawFill(point lt, point rb, GraphicsCore_Color BColor)
> Заполняет область начиная с левого верхнего угла **lt** и заканчивая правым нижним углом **rb** включительно используя символ пробела с цветом фона **BColor**.
* drawCentreText(std::string text, point center, GraphicsCore_Color FColor, GraphicsCore_Color BColor)
* drawLeftText(std::string text, point left, GraphicsCore_Color FColor, GraphicsCore_Color BColor)

## Доступные цвета для символов и фона
В классе описана таблица цветов. В качестве FColor и BColor можно использовать следующие цвета:
- Color_Black
- Color_Gray 
- Color_White 
- Color_RedDark
- Color_GreenDark
- Color_BlueDark
- Color_Red 
- Color_Green
- Color_Blue 
- Color_Yellow
- Color_YellowDark
- Color_Pink 
- Color_PinkDark
- Color_Aqua 
- Color_AquaDark


Весь процесс рисования методами drawOrthogonalLine(), drawOneSymb(), drawOrthogonalRectangle(), drawCentreText(), drawLeftText(), drawFill() производят запись символов в временный буфер. Для отображения графики(буфера) на экран нужно вызвать метод ShowBuffer(), при его вызове буфер не очищается, для очистки нужно воспользоваться методом clearBuffer(). С помощью этого можно рисовать в нескольких разных буферах (объектах класса) и выводить их по необходимости.
Метод clearBuffer() не очищает экран, а очищает буфер, для вывода очищенного буфера на экран всего нужно последовательно вызвать clearBuffer() и ShowBuffer().

При указании размера экрана 40х40 самый правый нижний угол будет иметь координаты 39х39.

## Простой пример использования
	#include <GraphicsCore.h>
	#include <ctime>
	#include <stdio.h>

	int main()
	{
		GraphicsCore GCore;
		GCore.init_graphics(80, 40);
		GCore.drawOneSymb(point{10,10}, 'X', Color_Green, Color_Black);
		GCore.drawOrthogonalRectangle(point{5,29}, point{35,31}, Color_Red, Color_Black);
		GCore.ShowBuffer();
		while (1){
			
		}
		return 0;
	}

## Установка
Установить "CodeBlocks 16.01 with minGW". Загрузить этот репозиторий (желательно в папку без пробелов и русских символов) и открыть файл проекта в CodeBlocks.
Если требуется использовать библиотеку из другой IDE - создать консольный проект и расположить в папке где находится main.cpp 2 файла класса - GraphicsCore.cpp, GraphicsCore.h. В файле main.cpp текст заменить текстом из примера и скомпилировать проект.

<meta name="google-site-verification" content="W5AlcwrkjqtKXbkISc2WaySFtY3e4unL_f-reiNauys" />
