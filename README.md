Event-based Malaria model using transmission cycles as time step. 

### Model Architecture
This model assumes a pool of Malaria clones and a population of anonymous hosts. It is stochastic and is run over discrete time steps equivalent to one Malaria generation/transmission cycle, which is approximately 100 days (as assumed in Ian M. Hastings 2002).

Here I will describe each step in the order that it occurs in the model.

#### (1) Transmission
1. Multiplicity of Infection (MOI): each host is assigned a MOI drawn from a poisson distribution with poisson mean $\lambda$

2. Selecting clones: each host selects randomly clones MOI times with chance of selecting clone equal to that clones frequency in population
	- each clone has frequency $\frac{1}{\text{MOI}}$ within host
	- same clone can be selected multiple times

3. Selecting drugs
	- **Single drug strategy**: all hosts receive single drug
	- **MFTs strategy**: each drug is distributed evenly across host population
	- **Adaptive cycling strategy**: all hosts receive single drug, until mean fitness of population is greater than average fitness of all clones to current drug

#### (2) Selection
Each host is assigned a mean fitness $m$ which is equal to
$$m = \sum^C_{c \in C} f_c \times w_c$$
where $C$ is set of all clones the host is infected with. $w_c$ is the fitness of the clone $c$ under the current drug and $f_c$ is its frequency ($m=0$ if host uninfected).
The new frequency of each clone ($w_c'$) is equal to
$$w_c' = \frac{f_c \times w_c}{m}$$

Fitness values are drawn from Appendix 2 of Nguyen et al. 2023

#### (3) Recombination
We assume mosquitoes (not simulated) pick up Malaria clones in exactly the frequency that they were in after selection within the host. We don't consider interrupted feeding.

Only a proportion $\theta$ of the population undergoes recombination. ($\theta$ is altered to observe effect of varying levels of recombination). For hosts whose clones undergo recombination, we assume complete recombination (all alleles are scrambled).

The frequency of each allele within the host is calculated, then the new frequency of all recombinants is calculated by finding the product of the frequencies of their alleles.

#### (4) Census
The new global frequency of each clone $F_c$ is collected with each host's contribution weighted according to their mean fitness. That is, for host $j$ and mean fitness $m_j$:
$$F_c = \sum^J_{j \in J} f_{jc} \times \frac{m_j}{M}$$
where $M$ is the total fitness of all hosts in the population:
$$M = \sum_{j \in J}^{J} m_j$$

The poisson mean in the next generation ($\lambda'$) is calculated.
$$\lambda' = R_0 \times \frac{M}{\text{num hosts}} \times \text{proportion of hosts uninfected}$$

#### (5) Mutation
In the model, mutations occur in the global pool of clones rather than within hosts. This means mutants do not recombine unless selected by chance by a host in the next generation.

We assume no backwards mutations and 1 allele is mutated (if not already mutant) for each mutant clone. The initial frequency of a single mutant is $10^{-6}$ which is also the parameter assumed in Hastings 2002.

The frequency of each mutant is:
$$f_{\text{mutant}}' = \lambda \times f_{\text{parent}}$$
and the original parent clone has new frequency:
$$f_{\text{parent}}' = f_{\text{parent}} - f_{\text{parent}} \times \lambda \times \text{num mutants}$$