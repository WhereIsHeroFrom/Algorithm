#include <iostream>
using namespace std;

struct point
{
    int map[4][4];
};
int hash[5];
int flag;
void dfs(point temp, int depth, int MaxDep)
{
    int i, j;
    point tt;

    if(depth > MaxDep)
        return;
    if(flag)
        return;

    //满足条件则搜索完毕
    int sum1 = 0, sum2 = 0;

    for(i = 0; i < 4; i++)
    {
        for(j = 1; j <= 4; j++)
            hash[j] = 0;

        for(j = 0; j < 4; j++)
        {
            hash[ temp.map[i][j] ] ++;
        }
        int Max = 0;
        for(j = 1; j <= 4; j++)
        {
            if(hash[j] > Max)
                Max = hash[j];
        }
        sum1 += 4 - Max;
    }





    if(sum1 == 0)
    {
        flag = 1;
        return ;
    }
    if(flag)
        return ;



    for(i = 0; i < 4; i++)
    {
        for(j = 1; j <= 4; j++)
            hash[j] = 0;

        for(j = 0; j < 4; j++)
        {
            hash[ temp.map[j][i] ] ++;
        }
        int Max = 0;
        for(j = 1; j <= 4; j++)
        {
            if(hash[j] > Max)
                Max = hash[j];
        }
        sum2 += 4 - Max;
    }

/*    printf("%d, %d\n", sum2, depth);

    for(i = 0; i < 4; i++)
    {
        for(j = 0;j < 4; j++)
        {
            printf("%d", temp.map[i][j]);
        }
        puts("");
    }
    
*/
    if(sum2 == 0)
    {
        flag = 1;
        return ;
    }
    if(flag)
        return ;

    sum1 = sum1 < sum2 ? sum1 : sum2;

    if(sum1 - 4 * (MaxDep - depth) > 0)
        return;



    //搜索的四种情况
    for(i = 0; i < 4; i++)
    {
        tt = temp;
        tt.map[i][0] = temp.map[i][3];
        for(j = 1; j < 4; j++)
        {
            tt.map[i][j] = temp.map[i][j-1];
        }
        dfs(tt, depth + 1, MaxDep);
    }

    for(i = 0; i < 4; i++)
    {
        tt = temp;
        tt.map[i][3] = temp.map[i][0];
        for(j = 0; j < 3; j++)
        {
            tt.map[i][j] = temp.map[i][j+1];
        
        }
        dfs(tt, depth + 1, MaxDep);
    }

    for(i = 0; i < 4; i++)
    {
        tt = temp;
        tt.map[3][i] = temp.map[0][i];
        for(j = 0; j < 3; j++)
        {
            tt.map[j][i] = temp.map[j+1][i];
        
        }
        dfs(tt, depth + 1, MaxDep);
    }


    for(i = 0; i < 4; i++)
    {
        tt = temp;
        tt.map[0][i] = temp.map[3][i];
        for(j = 1; j < 4; j++)
        {
            tt.map[j][i] = temp.map[j-1][i];
        }
        dfs(tt, depth + 1, MaxDep);
    }

}
int main()
{
    point temp;
    int t;
    int i, j;
    scanf("%d", &t);

    while(t--)
    {
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 4; j++)
            {
                scanf("%d", &temp.map[i][j]);
            }
        }

        for(i = 1; i <= 5; i++)
        {
            flag = 0;
            dfs(temp, 0, i);
            if(flag)
                break;
        }
        if(i != 6)
            printf("%d\n", i);
        else
            printf("%d\n", -1);

    }

    return 0;
}

