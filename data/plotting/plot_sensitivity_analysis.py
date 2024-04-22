import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('../data.csv')

means = data.mean()
errors = data.sem()

plt.style.use('ggplot')
plt.figure(figsize=(10, 6))
plt.ylim(50, 100)
plt.errorbar(means.index, means, yerr=errors, fmt='-o', capsize=5)
plt.title('Sensitivity Analysis')
plt.xlabel('Variable Parameter')
plt.ylabel('Measured Metric')
plt.grid(True)
plt.xticks(rotation=45)  # Rotate x-axis labels if necessary
plt.tight_layout()
plt.show()
