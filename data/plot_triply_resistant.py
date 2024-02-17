import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

csv_file_path = '../data/g_freqs.csv'
data = pd.read_csv(csv_file_path)

data['sum_values'] = data.iloc[:, -4:].sum(axis=1)

sns.set(style="whitegrid")

plt.figure(figsize=(12, 8))
plt.plot(data.index + 1, data['sum_values'], linestyle='-', color='b', label='Sum of Four Rightmost Values')
plt.title('Frequency of triply resistant clones over generations', fontsize=16)
plt.xlabel('Generation', fontsize=14)
plt.ylabel('Frequency of triply resistant clones', fontsize=14)
plt.grid(True)
plt.show()
