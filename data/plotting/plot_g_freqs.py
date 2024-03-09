import pandas as pd
import matplotlib.pyplot as plt

csv_file_path = '../g_freqs.csv'
data = pd.read_csv(csv_file_path, header=None)

data = data.reset_index()
data.rename(columns={'index': 'Generation'}, inplace=True)

plt.figure(figsize=(20, 10))
plt.ylim(0, 1)

print(data)

surviving_clones = []
custom_legend_titles = ['KNY--C1', 'KNY--Y1', 'KYY--C1', 'KYY--Y1', 
                        'KNF--C1', 'KNF--Y1', 'KYF--C1', 'KYF--Y1', 
                        'TNY--C1', 'TNY--Y1', 'TYY--C1', 'TYY--Y1', 
                        'TNF--C1', 'TNF--Y1', 'TYF--C1', 'TYF--Y1']


for i, column in enumerate(data.columns[1:], start=0):
    custom_name = custom_legend_titles[i]
    line = plt.plot(data['Generation'], data[column], alpha=0.6, label=custom_name)[0]
    
    if data[column].iloc[-1] > 0:
        surviving_clones.append(custom_name)

plt.xlabel('Generation')
plt.ylabel('Global Frequency')
plt.title('Global Frequency of Malaria Clones over generations')

plt.legend(title='Surviving Clones', loc='upper right', bbox_to_anchor=(1.12, 1.02),
           handles=[line for line in plt.gca().get_lines() if line.get_label() in surviving_clones],
           labels=custom_legend_titles)

plt.grid(True)
plt.show()
