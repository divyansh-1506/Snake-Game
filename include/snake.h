#ifndef SNAKE_H
#define SNAKE_H


class snake
{
public:
    int length = 2;
    int px = 100, py = 100;

    void draw()
    {
        for(int i = 0; i<=length; i++)
        {
        setfillstyle(1, 6);
        bar(px, py, px + grid, py + grid);
        }
    }



};

#endif // SNAKE_H
