#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include <SDL.h>
void Circle(SDL_Renderer *renderer,int r,int x,int y)
{
    int r2=r*2;

    int u=x;
    int v=y;
    x-=r;
    y-=r;
    //r*=r;
    for(int i=x;i<x+r2;i++)
    {
        for(int j=y;j<y+r2;j++)
        {
            if(sqrt(pow(i-u,2)+pow(j-v,2))<=r)
            SDL_RenderDrawPoint(renderer,i,j);

        }

    }

}

#endif // OBJECTS_H_INCLUDED
