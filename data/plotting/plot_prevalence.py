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
plt.figure(figsize=(6, 6))
plt.ylim(0, 1)
plt.rcParams['savefig.dpi'] = 300

# plot
plt.plot(data.index, prevalences, label='Prevalence')

# CYCLING
# plt.axvline(x=0, color='grey', linestyle='--')
# plt.text(0+0.5, 0.95, 'CQ', rotation=0, color='grey')
# plt.axvline(x=15, color='grey', linestyle='--')
# plt.text(15+0.5, 0.95, 'LM', rotation=0, color='grey')
# plt.axvline(x=39, color='grey', linestyle='--')
# plt.text(39+0.5, 0.95, 'ASAQ', rotation=0, color='grey')

# Setting labels and title
plt.xlabel('Transmission cycles', fontsize=12)
plt.ylabel('Prevalence (ratio of infected individuals)', fontsize=12)
plt.title('Prevalence across generations', fontsize=12)

# grid, legend
plt.grid(True)
plt.legend()

plt.show()
