import pandas as pd
import matplotlib.pyplot as plt
import scienceplots

csv_file_path = '../g_freqs.csv'
data = pd.read_csv(csv_file_path, header=None)

plt.style.use('ggplot')
data = data.reset_index()
data.rename(columns={'index': 'Generation'}, inplace=True)
plt.figure(figsize=(6,6))
plt.ylim(0, 1)


print(data)

surviving_clones = []
custom_legend_titles = [
    'KNY--C1', 'KNY--C2', 'KNY--Y1', 'KNY--Y2',
    'KNYNYC1', 'KNYNYC2', 'KNYNYY1', 'KNYNYY2',
    'KNF--C1', 'KNF--C2', 'KNF--Y1', 'KNF--Y2',
    'KNFNFC1', 'KNFNFC2', 'KNFNFY1', 'KNFNFY2',
    'KYY--C1', 'KYY--C2', 'KYY--Y1', 'KYY--Y2',
    'KYYYYC1', 'KYYYYC2', 'KYYYYY1', 'KYYYYY2',
    'KYF--C1', 'KYF--C2', 'KYF--Y1', 'KYF--Y2',
    'KYFYFC1', 'KYFYFC2', 'KYFYFY1', 'KYFYFY2',
    'TNY--C1', 'TNY--C2', 'TNY--Y1', 'TNY--Y2',
    'TNYNYC1', 'TNYNYC2', 'TNYNYY1', 'TNYNYY2',
    'TNF--C1', 'TNF--C2', 'TNF--Y1', 'TNF--Y2',
    'TNFNFC1', 'TNFNFC2', 'TNFNFY1', 'TNFNFY2',
    'TYY--C1', 'TYY--C2', 'TYY--Y1', 'TYY--Y2',
    'TYYYYC1', 'TYYYYC2', 'TYYYYY1', 'TYYYYY2',
    'TYF--C1', 'TYF--C2', 'TYF--Y1', 'TYF--Y2',
    'TYFYFC1', 'TYFYFC2', 'TYFYFY1', 'TYFYFY2'
]

data.columns = ['Generation'] + custom_legend_titles

threshold = 0.05

for column in custom_legend_titles:
    if (data[column] > threshold).any():
        surviving_clones.append(column)

for column in surviving_clones:
    line = plt.plot(data['Generation'], data[column], alpha=0.6, label=column)[0]

plt.xlabel('Transmission cycles', fontsize = 12)
plt.ylabel('Frequency (unitless)', fontsize = 12)
plt.title('Global clone frequencies across generations', fontsize = 12)

plt.legend(title='Surviving Clones', loc='upper right')

plt.grid(True)
plt.show()