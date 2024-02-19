import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

csv_file_path = '../g_freqs.csv'
data = pd.read_csv(csv_file_path, header = None)

data = data.reset_index()
data.rename(columns={'index': 'Generation'}, inplace=True)

plt.figure(figsize=(20, 10))

print(data)

surviving_clones = []
for i, column in enumerate(data.columns[1:], start=1):
    line = plt.plot(data['Generation'], data[column], alpha=0.6, label=f'Clone_{i}')[0]
    if any(data[column].iloc[-1:] > 0.02):
        surviving_clones.append(i)

plt.xlabel('Generation')
plt.ylabel('Global Frequency')
plt.title('Global Frequency of Malaria Clones over generations')

sns.set(style="whitegrid")
plt.legend(title='Surviving Clones', loc='upper right', bbox_to_anchor=(1.12, 1.02),
           handles=[line for line in plt.gca().get_lines() if int(line.get_label().split('_')[1]) in surviving_clones])

plt.grid(True)
plt.show()
