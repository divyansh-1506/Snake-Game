

#include <graphics.h>  // for all graphic related functions
#include <time.h>
#include <unistd.h> // for sleep function


int length = 2, score = 0;

int foodx, foody;

int posx[200] = {0}, posy[200] = {0};
int grid = 30; //to make game scalable
int width = 990;
int height = 780;
int page = 0;
int x = 0;

//to Generate random coordinates for food depending upon
int randfood(int x)
{
    int c;

    if(x == width)
    {
        do
        {
            c = (grid + rand()%(width-30));
            c = c/grid;
            c = c * grid;
        }
        while(c == 0 || c < 30 || c > 900 );
    }
    else
    {
        do
        {
            c = (grid + rand()%(width-30));
            c = c/grid;
            c = c * grid;
        }
        while(c == 0 || c < 60 || c > 720 );
    }
    return c;

}


void died(int s)
{
    using namespace std;
    char c[4 + sizeof(char)];
    sprintf(c, "SCORE : %d", score);
    cleardevice();
    setfillstyle(1,11);
    bar(0, 0, width, height);
    setcolor(WHITE);
    settextjustify(1, 1);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(width/2, height/2, "GAME OVER");
    outtextxy(width/2, height/2 + 70, c);
    setvisualpage(page);
    delay(5000);
    closegraph();
    printf("\nYOU DIED");
    delay(3000);
    exit(0);

}
int main()
{
    //dir will hold past directon of snake and d will be present direction of snake
    int dir = 1, d = 0;
    srand(time(0));
    initwindow(width,height,"snake game");
    posx[0] = 150;
    posy[0] = 300;
    foodx = randfood(width);
    foody = randfood(height);

    for(;;)
    {
        setactivepage(page);
        setvisualpage(1-page);
        setfillstyle(9, 3);
        bar(0, 0, width, height);
        setfillstyle(4, 15);
        bar(0, 0, width, grid); //TOP
        bar(0,0, grid, height); //LEFT
        bar(0, height-grid, width, height);  //BOTTOM
        bar(width- grid,0, width, height);   //RIGHT
        setfillstyle(1, 4);
        setlinestyle(SOLID_LINE,DASHED_LINE,1);

        for(int i = 2 * grid; i <= width - (2 * grid); i+=grid)
        {

            line(i,grid, i, height-30);
            line(grid, i, width-grid, i);

        }

        bar(foodx, foody, foodx + grid, foody + grid);

        if(foodx == posx[0] && foody == posy[0] )
        {
            length++;
            score++;
            setfillstyle(1, 0);
            bar(foodx, foody, foodx + grid, foody + grid);
            foodx = randfood(width);
            foody = randfood(height);
            setfillstyle(1, 4);
            bar(foodx, foody, foodx + grid, foody + grid);
        }

        if((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))&& dir != 2) d = 1;
        else if((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && dir != 1) d = 2;
        else if((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && dir != 4) d = 3;
        else if((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && dir != 3) d = 4;
        switch(d)
        {

        case 0:
            if(dir == 1)
            {
                posx[0] = posx[0] + grid;
            }
            if(dir == 2)
            {
                posx[0] = posx[0] - grid;
            }
            if(dir == 3)
            {
                posy[0] = posy[0] - grid;

            }
            if(dir == 4)
            {
                posy[0] = posy[0] + grid;
            }
            break;

        case 1:
            posx[0] = posx[0] + grid;
            dir = d;
            break;

        case 2:
            posx[0] = posx[0] - grid;
            dir = d;
            break;

        case 3:
            posy[0] = posy[0] - grid;
            dir = d;
            break;

        case 4:
            posy[0] = posy[0] + grid;
            dir = d;
            break;

        }
        for(int i = 199; i > 0; i--)
        {
            posx[i] = posx[i - 1];
            posy[i] = posy[i - 1];

        }
        for(int i = 0; i <= length ; i++)
        {

            setfillstyle(1, 2);
            bar(posx[0], posy[0], posx[0] + grid, posy[0] + grid);
            setfillstyle(1, 10);
            bar(posx[i], posy[i], posx[i] + grid, posy[i] + grid);

        }
        using namespace std;
        char c[4 + sizeof(char)];
        sprintf(c, "SCORE : %d", score);
        settextjustify(1, 1);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(6);
        outtextxy(900, 20, c);
        if(posx[0] < grid || posx[0] >= width - grid || posy[0] < grid  || posy[0] >= height-grid)
        {
            setactivepage(page);
            sleep(2);
            died(score);
        }
        page = 1 - page;
        for(int i = 2 ; i < length ; i++)
        {
            if(posx[0] == posx[i] && posy[0] == posy[i])
            {
                setactivepage(page);
                sleep(2);
                died(score);
            }
        }

        delay(100);

    }




}


