#include<iostream>

using namespace std;
int i, flag = 0;
char ch[1000];
int Num(char c)
{
    if(  !(    (c >= '0' && c <= '9' ) || c == '.'  )  )
        return 0;
    return 1;

}
int start, end, tp;
int main()
{
    while(gets(ch))
    {
        flag = 0;
        int len = strlen(ch);
        for(i = 0; i < len ;i++)
        {
            if(!Num(ch[i]))
                flag = 1;
        }
        tp = 0;
        if(!flag)
        {
            for(i = 0; i < len ;i++)
            {
                if(ch[i] >= '0' && ch[i] <= '9')
                {
                    tp ++;
                    start = i;
                    while(ch[i] >= '0' && ch[i] <= '9')
                        i++;
                    
                    end = i-1;
                    if(end - start >= 3)
                        flag = 1;
                    else if(end - start == 2)
                    {
                        if(ch[start] >= '3')
                            flag = 1;
                        else if(ch[start] == '2')
                        {
                            int s = 1;
                            int sum = 0;
                            sum = (ch[start] - '0')*100
                                +(ch[start+1] - '0')*10
                                +(ch[end] - '0')*1;
                            if(sum > 255)
                                flag = 1;
                        }
                    }
                    
                }
            }
            if(tp != 4)
                flag = 1;
        }
        int coun = 0;
        if(!flag)
        {
            
            for(i = 0; i < len; i++)
            {
                if(ch[i] == '.')
                    coun ++;
            }
            if(coun != 3)
                flag = 1;
        }

        if(flag)
            printf("NO\n");
        else
            printf("YES\n");
    }
}
