#pragma once

#define STARTING_POISSON_MEAN 3

#define R_NAUGHT 3

#define LAMBDA 0.000000005 //mutation rate

#define THETA 0.1 //recombination rate

#define NUM_LOCI 6

#define NUM_UNIQUE_CLONES 64 //2^6 = 64

#define NUM_DRUGS 10

enum drug {AS, LM, AQ, PPQ, MQ, CQ, AL, ASAQ, DHAPPQ, ASMQ};

#define NUM_GENERATIONS 300

#define NUM_HOSTS 300000

#define CYCLING_MEAN_FITNESS 0.35

#define DTS_CYCLING

#define DEBUG_DRUG