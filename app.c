#include "app.h"
#include <stdio.h>

char ch;

int main()
{
    Info* my_info = get_info();
    while (1)
    {
        puts("Which information do you want?");
        puts("Version(v), CPU(c), Memory(m), Time(t), All(a), Exit(e)");
        scanf("%c", &ch), getchar();

        if (ch == 'a')
            for (int i = 0; i <= 3; i++)
                printf("%s\n", my_info->data[i]);
        else if (ch == 'e')
            exit(0);
        else if (ch == 'v' || ch == 'c' || ch == 'm' || ch == 't')
            printf("%s\n", my_info->data[get_idx(ch)]);
        else
            puts("None exist choice, please check your choice again.");
    }
}