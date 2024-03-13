#pragma once

//transmission
#define STARTING_POISSON_MEAN 0.4

#define R_NAUGHT 4

#define NUM_GENERATIONS 100

#define NUM_HOSTS 300000

//genetics
#define LAMBDA 0.000001 //mutation rate

#define THETA 0.2 //recombination rate

#define NUM_LOCI 4

#define NUM_UNIQUE_CLONES 16 //2^4 = 16

//drug treatment
#define NUM_DRUGS 10

enum drug {AS = 0, LM, AQ, PPQ, MQ, CQ, AL, ASAQ, DHAPPQ, ASMQ, NO_DRUG = 99};

#define DTS_CYCLING

#define CYCLING_DRUG1 AS
#define CYCLING_DRUG2 CQ
#define CYCLING_DRUG3 LM

#define SINGLE_DRUG AQ

#define MFT_DRUG1 AQ
#define MFT_DRUG2 CQ
#define MFT_DRUG3 LM

#define DEBUG_DRUG