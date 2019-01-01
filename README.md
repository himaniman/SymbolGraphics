# Symbol Graphics class
Class for works with WIN API output ASCII graphics

## Описание
Класс позволяет выводить в консоль Windows (cmd.exe) графические примитивы и текст с указанием цвета и координат.

## Доступные методы
* init_graphics()
	Выделение памяти по буффер размера текущей сессии командной строки (по умолчанию в Windows это 80х25), очистка буфера.
* init_graphics(int WIDTH, int HEIGHT)
	Выделение памяти по буффер размера WIDTH х HEIGHT, очистка буфера.

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

В классе доступны только вертикальные и горизонтальные линии.
Можно устанавливать цвет символа и цвет фона для символа.

При построении прямоугольника важно указывать верхний левый угол и нижний правый угол для корректного отображения.

Весь процесс рисования методами drawOrthogonalLine(), drawOneSymb(), drawOrthogonalRectangle(), drawCentreText(), drawLeftText(), drawFill() производят запись символов в временный буфер. Для отображения графики(буфера) на экран нужно вызвать метод ShowBuffer(), при его вызове буфер не очищается, для очистки нужно воспользоваться методом clearBuffer(). С помощью этого можно рисовать в нескольких разных буферах (объектах класса) и выводить их по необходимости.
Метод clearBuffer() не очищает экран, а очищает буфер, для вывода очищенного буфера на экран всего нужно последовательно вызвать clearBuffer() и ShowBuffer().

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