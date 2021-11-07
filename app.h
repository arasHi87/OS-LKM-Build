#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxN 100007

typedef struct info
{
    char data[5][maxN];
    /*
    data[0] -> Version
    data[1] -> CPU
    data[2] -> Memory
    data[3] -> Time
    */
} Info;

int get_idx(char ch)
{
    if (ch == 'C' || ch == 'c')
        return 1;
    if (ch == 'M' || ch == 'm')
        return 2;
    if (ch == 'T' || ch == 't')
        return 3;
    return 0;
}

Info* get_info()
{
    Info* my_info = (Info*)malloc(sizeof(Info));
    FILE* file = fopen("/proc/my_info", "r");
    char line[1024];
    int idx;

    while (fgets(line, 1024, file))
    {
        if (line[0] == '=')
            idx = get_idx(line[10]);
        strcat(my_info->data[idx], line);
    }

    return my_info;
}
