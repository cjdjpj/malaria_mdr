import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import poisson

csv_file_path = '../poisson_mean.csv'
data = pd.read_csv(csv_file_path, header=None)

prevalences = 1 - poisson.cdf(0, data[0])

plt.plot(data.index, prevalences, label='Prevalence')

plt.xlabel('Generation')
plt.ylabel('Prevalence')
plt.title('Prevalence over generations')
plt.grid(True)
plt.legend()
plt.show()
