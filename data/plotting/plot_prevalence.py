import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import poisson

# load data and process
csv_file_path = '../poisson_mean.csv'
data = pd.read_csv(csv_file_path, header=None)

# convert poisson mean to prevalence
prevalences = 1 - poisson.cdf(0, data[0])

print(prevalences)

# settings
plt.style.use('ggplot')
plt.figure(figsize=(10, 10))
plt.ylim(0, 1)
plt.rcParams['savefig.dpi'] = 300

# plot
plt.plot(data.index, prevalences, label='Prevalence')

# CYCLING
# drug1_gen = 0
# drug2_gen = 25
# drug3_gen = 48
# plt.axvline(x=drug1_gen, color='grey', linestyle='--')
# plt.text(drug1_gen+0.5, 0.95, 'CQ', rotation=0, color='grey')
# plt.axvline(x=drug2_gen, color='grey', linestyle='--')
# plt.text(drug2_gen+0.5, 0.95, 'LM', rotation=0, color='grey')
# plt.axvline(x=drug3_gen, color='grey', linestyle='--')
# plt.text(drug3_gen+0.5, 0.95, 'ASAQ', rotation=0, color='grey')

# Setting labels and title
plt.xlabel('Transmission cycles', fontsize=12)
plt.ylabel('Prevalence (ratio of infected individuals)', fontsize=12)
plt.title('Prevalence across generations', fontsize=12)

# grid, legend
plt.grid(True)
plt.legend()

plt.show()
