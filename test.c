#include "game.h"

static void test_init_game(void)
{
    // init_game();
    // C
    long double expect_Cj[NUM_RES_KINDS] = {8, 14, 90};
    for (int j = 0; j < NUM_RES_KINDS; j++)
        assert(almost_eq(expect_Cj[j], Cj[j]));
    // psy
    long double expect_psy[NUM_USERS][NUM_RES_KINDS] = {
        {1.0/4, 2.0/7, 2.0/9},
        {1.0/8, 1.0/14, 1.0/9},
        {1.0/4, 1.0/7, 1.0/9},
    };
    for (int i = 0; i < NUM_USERS; i++)
        for (int j = 0; j < NUM_RES_KINDS; j++)
            assert(almost_eq(psy[i][j], expect_psy[i][j]));
    // d
    long double expect_d[NUM_USERS][NUM_RES_KINDS] = {
        {7.0/8, 1.0, 7.0/9},
        {1.0, 4.0/7, 8.0/9},
        {1.0, 4.0/7, 4.0/9},
    };
    for (int i = 0; i < NUM_USERS; i++)
        for (int j = 0; j < NUM_RES_KINDS; j++)
            assert(almost_eq(expect_d[i][j], d[i][j]));
    // lamda
    assert(almost_eq(lamda, 8.0 / 23));
}

static void test_set_phi()
{
    // init_game();
    int coms[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},
        {1, 0, 1},
    };
    long double phi[NUM_USERS][NUM_RES_KINDS] = {0};
    set_phi(coms, phi);
    long double expect_phi[NUM_USERS][NUM_RES_KINDS] = {
        {4, 8, 40},
        {2, 2, 20},
        {2, 2, 10},
    };
    for (int i = 0; i < NUM_USERS; i++)
        for (int j = 0; j < NUM_RES_KINDS; j++)
            assert(almost_eq(phi[i][j], expect_phi[i][j]));
}

static void test_set_A()
{
    // init_game();
    int coms[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},
        {1, 0, 1},
    };
    long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS] = {0};
    set_A(coms, A);
    long double expect_A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS] = {
        {
            {2, 4, 20},
            {2, 2, 20},
            {0, 0, 0},
        },
        {
            {2, 4, 20},
            {0, 0, 0},
            {2, 2, 10},
        },
    };
    for (int m = 0; m < NUM_SERVERS; m++)
        for (int i = 0; i < NUM_USERS; i++)
            for (int j = 0; j < NUM_RES_KINDS; j++)
                assert(almost_eq(A[m][i][j], expect_A[m][i][j]));
}

static void test_u()
{
    // init_game();
    int coms[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},
        {1, 0, 1},
    };
    long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS] = {0};
    set_A(coms, A);

    long double expect_u[NUM_SERVERS][NUM_RES_KINDS] = {
        {1, 0.75, 1},
        {1, 1, 0.6},
    };
    for (int m = 0; m < NUM_SERVERS; m++)
        for (int j = 0; j < NUM_RES_KINDS; j++) {
            long double utilization = u(A, m, j);
            assert(almost_eq(expect_u[m][j], utilization));
        }

}

static void test_ske()
{
    // init_game();
    int coms[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},
        {1, 0, 1},
    };
    long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS] = {0};
    set_A(coms, A);
    long double expect_ske[NUM_SERVERS] = {powl(6.0 / 121, 0.5), powl(24.0 / 169, 0.5)};
    for (int m = 0; m < NUM_SERVERS; m++) {
        long double s = ske(A, m);
        assert(almost_eq(s, expect_ske[m]));
    }

}

static void test_Xij_Cj_lamda_Dij_a_1()
{
    // init_game();
    int coms[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},
        {1, 0, 1},
    };
    long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS] = {0};
    set_A(coms, A);

    long double expect[NUM_USERS][NUM_RES_KINDS] = {
        {0.19565217391304346, 0.22360248447204967, 0.17391304347826086, },
        {0.09782608695652173, 0.05590062111801242, 0.08695652173913043, },
        {0.09782608695652173, 0.05590062111801242, 0.043478260869565216,},
    };
    
    for (int i = 0; i < NUM_USERS; i++)
        for (int j = 0; j < NUM_RES_KINDS; j++) {
            assert(almost_eq(expect[i][j], Xij_Cj_lamda_Dij_a_1(A, i, j)));
        }
}

static void test_v()
{
    // init_game();
    int coms[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},
        {1, 0, 1},
    };
    long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS] = {0};
    set_A(coms, A);
    long double expect_v = 1.0154092281544018;
    assert(almost_eq(expect_v, v(A)));
}


static void test_U()
{
    long double val;
    // init_game();
    int coms1[NUM_SERVERS][NUM_USERS] = {
        {2, 0, 0},  // d
        {1, 2, 0},  // a
    };
    int coms2[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},  // e
        {1, 2, 0},  // a
    };
    int coms3[NUM_SERVERS][NUM_USERS] = {
        {1, 0, 1},  // f
        {1, 2, 0},  // a
    };
    int coms4[NUM_SERVERS][NUM_USERS] = {
        {2, 0, 0},  // d
        {1, 0, 1},  // b
    };
    int coms5[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},  // e
        {1, 0, 1},  // b
    };
    int coms6[NUM_SERVERS][NUM_USERS] = {
        {1, 0, 1},  // f
        {1, 0, 1},  // b
    };
    int coms7[NUM_SERVERS][NUM_USERS] = {
        {2, 0, 0},  // d
        {0, 0, 2},  // c
    };
    int coms8[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},  // e
        {0, 0, 2},  // c
    };
    int coms9[NUM_SERVERS][NUM_USERS] = {
        {1, 0, 1},  // f
        {0, 0, 2},  // c
    };
    long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS] = {0};
    printf("a, d: ");
    set_A(coms1, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    
    printf("a, e: ");
    set_A(coms2, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    
    printf("a, f: ");
    set_A(coms3, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);

    printf("b, d: ");
    set_A(coms4, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    
    printf("b, e: ");
    set_A(coms5, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    
    printf("b, f: ");
    set_A(coms6, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    
    printf("c, d: ");
    set_A(coms7, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    
    printf("c, e: ");
    set_A(coms8, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    
    printf("c, f: ");
    set_A(coms9, A);
    val = U(A, 1);
    printf("%Lf, ", val);
    val = U(A, 0);
    printf("%Lf\n", val);
    // long double expect_U[NUM_SERVERS] = {};
    // for (int m = 0; m < NUM_SERVERS; m++) {
    //     long double val = U(A, m);
    //     assert(almost_eq(val, expect_U[m]));
    // }
    // val = U(A, 0);
    // assert(almost_eq(val, 1.2));
    // val = U(A, 1);
    // assert(almost_eq(val, 1.27));
}

int main()
{
    init_game();

    test_init_game();
    test_set_phi();
    test_set_A();
    test_u();
    test_ske();
    test_Xij_Cj_lamda_Dij_a_1();

    test_v();
    test_U();
    return 0;
}
