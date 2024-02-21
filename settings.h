#pragma once

//transmission
#define STARTING_POISSON_MEAN 3

#define R_NAUGHT 3

#define NUM_GENERATIONS 300

#define NUM_HOSTS 300000

//genetics
#define LAMBDA 0.000000005 //mutation rate

#define THETA 0.1 //recombination rate

#define NUM_LOCI 6

#define NUM_UNIQUE_CLONES 64 //2^6 = 64

//drug treatment
#define NUM_DRUGS 10

enum drug {AS = 0, LM, AQ, PPQ, MQ, CQ, AL, ASAQ, DHAPPQ, ASMQ, NO_DRUG = 99};

#define CYCLING_MEAN_FITNESS 0.35

#define DTS_CYCLING

#define DEBUG_DRUG