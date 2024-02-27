#pragma once

//transmission
#define STARTING_POISSON_MEAN 2

#define R_NAUGHT 3

#define NUM_GENERATIONS 300

#define NUM_HOSTS 300000

//genetics
#define LAMBDA 0.0000001 //mutation rate

#define THETA 0.2 //recombination rate

#define NUM_LOCI 4

#define NUM_UNIQUE_CLONES 16 //2^4 = 16

//drug treatment
#define NUM_DRUGS 10

enum drug {AS = 0, LM, AQ, PPQ, MQ, CQ, AL, ASAQ, DHAPPQ, ASMQ, NO_DRUG = 99};

#define CYCLING_MEAN_FITNESS 0.05

#define DTS_SINGLE

#define DEBUG_DRUG