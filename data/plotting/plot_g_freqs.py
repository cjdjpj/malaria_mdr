import pandas as pd
import matplotlib.pyplot as plt

# load data and process
csv_file_path = '../g_freqs.csv'
data = pd.read_csv(csv_file_path, header=None)
data = data.reset_index()
data.rename(columns={'index': 'Generation'}, inplace=True)

# custom legend titles and column assignment
custom_legend_titles = [
    'KNY--C1', 'KNY--C2', 'KNY--Y1', 'KNY--Y2', 'KNYNYC1', 'KNYNYC2', 'KNYNYY1', 'KNYNYY2',
    'KNF--C1', 'KNF--C2', 'KNF--Y1', 'KNF--Y2', 'KNFNFC1', 'KNFNFC2', 'KNFNFY1', 'KNFNFY2',
    'KYY--C1', 'KYY--C2', 'KYY--Y1', 'KYY--Y2', 'KYYYYC1', 'KYYYYC2', 'KYYYYY1', 'KYYYYY2',
    'KYF--C1', 'KYF--C2', 'KYF--Y1', 'KYF--Y2', 'KYFYFC1', 'KYFYFC2', 'KYFYFY1', 'KYFYFY2',
    'TNY--C1', 'TNY--C2', 'TNY--Y1', 'TNY--Y2', 'TNYNYC1', 'TNYNYC2', 'TNYNYY1', 'TNYNYY2',
    'TNF--C1', 'TNF--C2', 'TNF--Y1', 'TNF--Y2', 'TNFNFC1', 'TNFNFC2', 'TNFNFY1', 'TNFNFY2',
    'TYY--C1', 'TYY--C2', 'TYY--Y1', 'TYY--Y2', 'TYYYYC1', 'TYYYYC2', 'TYYYYY1', 'TYYYYY2',
    'TYF--C1', 'TYF--C2', 'TYF--Y1', 'TYF--Y2', 'TYFYFC1', 'TYFYFC2', 'TYFYFY1', 'TYFYFY2'
]
data.columns = ['Generation'] + custom_legend_titles

# settings
plt.style.use('ggplot')
plt.figure(figsize=(10, 10))
plt.ylim(0, 1)
plt.rcParams['savefig.dpi'] = 300

threshold = 0.2

# plot data
for column in custom_legend_titles:
    series = data[column]
    if series.max() > threshold:
        plt.plot(data['Generation'], series, label=column)
    else:
        plt.plot(data['Generation'], series, color='grey', alpha=0.2)  # grey out the non-significant lines


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

# setting labels
plt.xlabel('Transmission cycles', fontsize=12)
plt.ylabel('Frequency (unitless)', fontsize=12)
plt.title('Global clone frequencies across generations', fontsize=12)

# legend and grid
plt.legend(title='Surviving Clones', loc='upper right')
plt.grid(True)

plt.show()
