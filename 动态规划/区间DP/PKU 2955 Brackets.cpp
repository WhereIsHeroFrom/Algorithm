#include <iostream>

using namespace std;

char str[ 1000 ];
int i;
int dp[ 1000 ][ 1000 ];

int dfs( int start, int end ) {
	int i;
	if( start >= end )
		return 0;
	if( start + 1 == end ) {
		if( str[ start ] == '[' && str[ end ] == ']' )
			return 1;
		if( str[ start ] == '(' && str[ end ] == ')' )
			return 1;
		return 0;
	}

	int Max = 0;

	if( str[ start ] == '[' && str[ end ] == ']' ) {
		if( dp[ start+1 ][ end-1 ] == -1 )
			dp[ start+1 ][ end-1 ] = dfs( start+1, end-1 );
		if(dp[ start+1 ][ end-1 ] + 1 > Max )
			Max = dp[ start+1 ][ end-1 ] + 1;
	}
	
	if( str[ start ] == '(' && str[ end ] == ')' ) {
		if( dp[ start+1 ][ end-1 ] == -1 )
			dp[ start+1 ][ end-1 ] = dfs( start+1, end-1 );
		if(dp[ start+1 ][ end-1 ] + 1 > Max )
			Max = dp[ start+1 ][ end-1 ] + 1;
	}

	if( dp[ start+1 ][ end ] == -1 )
		dp[ start+1 ][ end ] = dfs( start+1, end );
	if(dp[ start+1 ][ end ] > Max )
		Max = dp[ start+1 ][ end ];

	if( dp[ start ][ end-1 ] == -1 )
		dp[ start ][ end-1 ] = dfs( start, end-1 );
	if(dp[ start ][ end-1 ] > Max )
		Max = dp[ start ][ end-1 ];

	for(i = start; i < end; i++) {
		if( dp[ start ][ i ] == -1 )
			dp[ start ][ i ] = dfs( start, i );
		if( dp[ i+1 ][ end ] == -1 )
			dp[ i+1 ][ end ] = dfs( i+1, end );

		if( dp[ start ][ i ] + dp[ i+1 ][ end ] > Max )
			Max = dp[ start ][ i ] + dp[ i+1 ][ end ];
	}

	return Max;
}

int main() {
	while( gets( &str[1] ) ) {
		if( strcmp( &str[1], "end" ) == 0 )
			break;
		int len = strlen( &str[1] );
		if( !len ) {
			printf("0\n");
		}else {
			memset( dp, -1, sizeof( dp ) );
			dp[1][len] = dfs( 1, len );
			printf("%d\n", 2 * dp[1][len] );
		}
	}
}
