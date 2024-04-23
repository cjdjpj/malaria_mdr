import pandas as pd
import matplotlib.pyplot as plt

# load data
data = pd.read_csv('../sensitivity_analysis.csv')

# get mean and error
means = data.mean()
errors = data.sem()

# settings
plt.rcParams['savefig.dpi'] = 300
plt.style.use('ggplot')
plt.figure(figsize=(10, 6))
plt.title('Single drug + WT start: R0 vs Time to max fitness clone fixation')
plt.xlabel('R0')
plt.ylabel('Time to max fitness clone fixation (# of generations)')
plt.xticks(rotation=45)
plt.grid(True)
plt.tight_layout()

# error bars
plt.errorbar(means.index, means, yerr=errors, fmt='-o', capsize=5)

plt.show()
