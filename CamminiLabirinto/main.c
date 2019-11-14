//
// Created by gianluca on 12/11/19.
//
#include <stdio.h>
#define MAXD 8

typedef struct
{
    int r, c;
} Dim;
typedef struct {
    int lun, sem;
} Cam; // Caratteristiche cammino

Dim leggiMaze(char m[][MAXD])
{
    Dim dim;
    FILE *fp = fopen("maze.txt", "r");
    fscanf(fp, "%d %d", &dim.r,&dim.c);
    fscanf(fp, "%*c");

    for (int i = 0; i < dim.r; i++) {
        for (int j = 0; j < dim.c; j++) {
            fscanf(fp, "%c", &m[i][j]);
        }
        fscanf(fp, "%*c");
    }
    fclose(fp);
    return dim;
}
void stampaMaze(char m[][MAXD], Dim dim)
{
    for (int i = 0; i < dim.r; i++) {
        for (int j = 0; j < dim.c; j++) {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}
Cam verificaCammino(char m[][MAXD], Dim dim)
{
    int dx, dy;
    int posx=0, posy=0;
    int valido = 1;
    Cam cammino;

    FILE *fp = fopen("mazeWrong.txt", "r");
    cammino.lun=0;
    cammino.sem=1;

    while (fscanf(fp, "%d %d", &dx, &dy)==2 && valido)
    {
        printf("Mossa: %d %d\n", dx, dy);
        dy=-dy;

        if((posx+dx)<0 || (posx+dx)>=dim.c || (posy+dy)<0 || (posy+dy)>=dim.c)
        {
            valido=0;
            printf("Fuori dai bordi\n");
        }
        else
        {

        }

        for (int i = posy; (i < posy+dy) && valido; i++) {
            if(m[i][posx]=='x') valido =0;
            else
            {
                m[i][posx]='*';
                stampaMaze(m, dim);
            }
        }
    }
}

int main()
{
    char maze[MAXD][MAXD];
    Dim dim;

    dim = leggiMaze(maze);
    stampaMaze(maze, dim);
    printf("-----------------------------------------------\n");

    verificaCammino(maze, dim);

    return 0;
}

