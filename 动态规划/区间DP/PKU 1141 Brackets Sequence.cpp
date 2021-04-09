#include <iostream>

using namespace std;

char str[120];
int i, len;
int pack[120];
int dp[120][120];

int dfs(int st, int en)
{
	int k;
	if(st == en) return 1;
	if(st > en) return 0;

	dp[st][en] = 999999999;

	if(str[st] == '(' && str[en] == ')' || str[st] == '[' && str[en] == ']')
	{
		if(dp[st+1][en-1] == -1)
			dp[st+1][en-1] = dfs(st+1, en-1);

		if(dp[st+1][en-1] < dp[st][en])
			dp[st][en] = dp[st+1][en-1];
	}
	
	if(str[st] == '(' || str[st] == '[')
	{
		if(dp[st+1][en] == -1)
			dp[st+1][en] = dfs(st+1, en);

		if(dp[st+1][en] + 1 < dp[st][en])
			dp[st][en] = dp[st+1][en] + 1;
	}
	
	if(str[en] == ')' || str[en] == ']')
	{
		if(dp[st][en-1] == -1)
			dp[st][en-1] = dfs(st, en-1);

		if(dp[st][en-1] + 1 < dp[st][en])
			dp[st][en] = dp[st][en-1] + 1;
	}

	for(k = st; k < en; k++)
	{
		if(dp[st][k] == -1)
			dp[st][k] = dfs(st, k);
		if(dp[k+1][en] == -1)
			dp[k+1][en] = dfs(k+1, en);

		if(dp[st][k] + dp[k+1][en] < dp[st][en])
			dp[st][en] = dp[st][k] + dp[k+1][en];
	}
	return dp[st][en];
}

void Dfs(int st, int en)
{
	int k;
	if(!dp[st][en])
		return;

	if(st == en)
	{
		pack[st] = 1;
		return;
	}

	if(st > en)
		return;

	if(str[st] == '(' && str[en] == ')' || str[st] == '[' && str[en] == ']')
	{
		if(dp[st+1][en-1] == dp[st][en])
		{
			Dfs(st+1, en-1);
			return;
		}
	}
	
	if(str[st] == '(' || str[st] == '[')
	{
		if(dp[st+1][en] + 1 == dp[st][en])
		{
			Dfs(st+1, en);
			Dfs(st, st);
			return ;
		}
	}
	
	if(str[en] == ')' || str[en] == ']')
	{
		if(dp[st][en-1] + 1 == dp[st][en])
		{
			Dfs(st, en-1);
			Dfs(en, en);
			return;
		}
	}

	for(k = st; k < en; k++)
	{
		if(dp[st][k] + dp[k+1][en] == dp[st][en])
		{
			Dfs(st, k);
			Dfs(k+1, en);
			return;
		}
	}
}
int main()
{
	int i, j;
	while(gets(&str[1]))
	{
		memset(dp, -1, sizeof(dp));
		memset(pack, 0, sizeof(pack));

		len = strlen(&str[1]);

		for(i = 0; i <= len; i++)
		{

			for(j = 0; j <= len; j++)
			{
				if(dp[i][j] == -1)
				    dp[i][j] = dfs(i, j);
				
				//printf("%5d", dp[i][j]);
			}
			
			//puts("");
		}

		Dfs(1, len);

		for(i = 1; i <= len; i++)
		{
			if(pack[i])
			{
				if(str[i] == '(' || str[i] == ')')
				{
					printf("()");
				}else
					printf("[]");
			}else
				printf("%c", str[i]);
		}
		puts("");
	}
}
