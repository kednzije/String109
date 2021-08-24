/*~Rainybunny~*/

#include <cstdio>

#define rep( i, l, r ) for ( int i = l, rep##i = r; i <= rep##i; ++i )
#define per( i, r, l ) for ( int i = r, per##i = l; i >= per##i; --i )

const int MAXN = 400;
int n, m, P, fac[MAXN + 5], ifac[MAXN + 5];
int pwr[MAXN + 5][MAXN + 5], ipwr[MAXN + 5][MAXN + 5];
int f[MAXN + 5][MAXN + 5], g[MAXN + 5];

inline int mul( const int a, const int b ) { return 1ll * a * b % P; }
inline void subeq( int& a, const int b ) { ( a -= b ) < 0 && ( a += P ); }
inline int add( int a, const int b ) { return ( a += b ) < P ? a : a - P; }
inline void addeq( int& a, const int b ) { ( a += b ) >= P && ( a -= P ); }
inline int sub( int a, const int b ) { return ( a -= b ) < 0 ? a + P : a; }
inline int mpow( int a, int b ) {
    int ret = 1;
    for ( ; b; a = mul( a, a ), b >>= 1 ) ret = mul( ret, b & 1 ? a : 1 );
    return ret;
}

inline void init() {
    fac[0] = 1;
    rep ( i, 1, n ) fac[i] = mul( i, fac[i - 1] );
    ifac[n] = mpow( fac[n], P - 2 );
    per ( i, n - 1, 0 ) ifac[i] = mul( i + 1, ifac[i + 1] );

    rep ( i, 0, n ) {
        pwr[i][0] = ipwr[i][0] = 1;
        ipwr[i][1] = mpow( pwr[i][1] = i, P - 2 );
        rep ( j, 2, n ) {
            pwr[i][j] = mul( i, pwr[i][j - 1] );
            ipwr[i][j] = mul( ipwr[i][j - 1], ipwr[i][1] );
        }
    }
}

inline int comb( const int a, const int b ) {
    return a < b ? 0 : mul( fac[a], mul( ifac[b], ifac[a - b] ) );
}

#include <iostream>
using namespace std;

int main() {
    scanf( "%d %d %d", &n, &m, &P ), init();

    rep ( j, 1, n ) {
        static int sum[MAXN + 5][2];
        rep ( i, 1, n ) sum[i][0] = sum[i][1] = 0;
        rep ( i, 1, n ) {
            int& cur = f[i][j] = pwr[j][i];
            rep ( t, 1, j ) {
                subeq( cur, mul( pwr[t][i], sum[t][0] ) );
                addeq( cur, mul( pwr[t - 1][i], sum[t][1] ) );
            }
            rep ( t, 1, j ) {
                addeq( sum[t][0], mul( ipwr[t][i],
                  sub( f[i][j - t + 1], f[i][j - t] ) ) );
                addeq( sum[t][1], mul( ipwr[t - 1][i],
                  sub( f[i][j - t + 1], f[i][j - t] ) ) );
            }
        }
    }

	rep (i, 1, n) {
		rep (j, 1, n) {
			cout << f[i][j] << ' ';
		}
		cout << endl;
	}

    int ans = 0, c = 1;
    rep ( i, 1, n ) {
        int& cur = g[i] = f[n][i];
        rep ( j, 1, i - 1 ) subeq( cur, mul( comb( i, j ), g[j] ) );
        c = mul( c, mul( m - i + 1, ipwr[i][1] ) );
        addeq( ans, mul( c, g[i] ) );
    }
    printf( "%d\n", ans );
    return 0;
}