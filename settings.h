#pragma once

//transmission
#define STARTING_POISSON_MEAN 0.4

#define R_NAUGHT 5

#define NUM_GENERATIONS 60

#define NUM_HOSTS 300000

#define TERMINATE_WHEN_ENDEMIC_OR_ELIMINATED

//genetics
#define LAMBDA 0.000001 //mutation rate

#define THETA 0.2 //recombination rate

#define NUM_LOCI 6

#define NUM_UNIQUE_CLONES 64 //2^6

//drug treatment
#define TREATED_PROP 0.9

#define NUM_DRUGS 11 // 10 drugs + NO_DRUG

enum drug {AS = 0, LM, AQ, PPQ, MQ, CQ, AL, ASAQ, DHAPPQ, ASMQ, NO_DRUG};

#define DTS_MFT

#define CYCLING_DRUG1 AS
#define CYCLING_DRUG2 CQ
#define CYCLING_DRUG3 LM

#define SINGLE_DRUG AQ

#define MFT_DRUG1 AQ
#define MFT_DRUG2 CQ
#define MFT_DRUG3 LM

#define DEBUG_DRUG