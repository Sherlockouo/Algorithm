#include <iostream>

using namespace std;

int coun, cou, len, i, start;
char ch[32], cpy[30];
int main()
{
    while(scanf("%s", ch) != EOF)    
    {
        len = strlen(ch);


        for(i = 0; i < len ;i++)
            if(ch[i] == '1')
                break;
        if(i == len)
        {
            printf("0\n");
            continue;
        }


        strcpy(cpy, ch);
        

        if(len == 1)
        {
            if(ch[0] == '0')
                printf("0\n");
            else
                printf("1\n");
            continue;
        }

        coun = 0;
        int tp = 0;

        //第一个不变的情况

        while(1)
        {

            for(i = tp; i < len ; i++)
            {
                if(ch[i] == '1')
                    break;
            }  
            if(i >= len - 1)
                break;
            i = i+1;

            if(i - 1 >= 0)
                ch[i-1] = '0' + (ch[i-1] - '0')^1;

            ch[i] ='0' + (ch[i] - '0')^1;

            if(i + 1 < len)
                ch[i+1] = '0' + (ch[i+1] - '0')^1;


            coun++;

            tp = i;


        }

        for(i = 0; i < len ;i++)
            if(ch[i] == '1')
                break;

            if(i != len )
                coun = 99999999;

        strcpy(ch, cpy);
        ch[0] = '0' + (ch[0] - '0')^1;
        ch[1] = '0' + (ch[1] - '0')^1;

        cou = 1;
        tp = 0;

        while(1)
        {

            for(i = tp; i < len ; i++)
            {
                if(ch[i] == '1')
                    break;
            } 
            if(i >= len - 1)
                break; 
            i = i+1;



            if(i - 1 >= 0)
                 ch[i-1] = '0' + (ch[i-1] - '0')^1;

            ch[i] ='0' + (ch[i] - '0')^1;
            if(i + 1 < len)
                 ch[i+1] = '0' + (ch[i+1] - '0')^1;

            cou++;
            
            tp = i;



        }


        for(i = 0; i < len ;i++)
            if(ch[i] == '1')
                break;

            if(i != len)
                cou = 99999999;



        if(coun == 99999999 && cou == 99999999)
            printf("NO\n");
        else
            printf("%d\n", coun < cou ? coun : cou);
            
    }
}

