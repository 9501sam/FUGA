#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#define NUM_USERS       3   // s
#define NUM_RES_KINDS   3   // k
#define NUM_SERVERS     2   // p
#define NUM_VM_TYPES    NUM_USERS

typedef struct {
    double cpu;
    double mem;
    double disk;
} resources;

typedef struct {
    resources res;
} resource_capacity;

typedef struct {
    resources res;
} vm;

typedef struct {
    int num_vm;
    vm type;
} job;

extern int          eta;     // n like letter
extern int          alpha;   // a like letter

// extern resources    C[NUM_SERVERS][NUM_RES_KINDS];
// extern resources    J[NUM_USERS];
// extern resources    r[NUM_USERS];

#endif
