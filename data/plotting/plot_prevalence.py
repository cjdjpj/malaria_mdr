import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import poisson

csv_file_path = '../poisson_mean.csv'
data = pd.read_csv(csv_file_path, header=None)

prevalences = 1 - poisson.cdf(0, data[0])

print(prevalences)

plt.style.use('ggplot')
plt.figure(figsize=(6,6))
plt.ylim(0, 1)
plt.plot(data.index, prevalences, label='Prevalence')

plt.xlabel('Transmission cycles', fontsize = 12)
plt.ylabel('Prevalence (ratio of infected individuals)', fontsize = 12)
plt.title('Prevalence across generations', fontsize = 12)
plt.grid(True)
plt.legend()
plt.show()
