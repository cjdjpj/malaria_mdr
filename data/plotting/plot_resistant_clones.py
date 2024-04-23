import pandas as pd
import matplotlib.pyplot as plt

# load data and process
csv_file_path = '../g_freqs.csv'
data = pd.read_csv(csv_file_path, header=None)

# resistance categories
dha_ppq_aq_triple_resistant = [51, 55]
data['DHA-PPQ, AQ triple-resistant'] = data.iloc[:, dha_ppq_aq_triple_resistant].sum(axis=1)
dha_ppq_lum_triple_resistant = [11, 15]
data['DHA-PPQ, LUM triple-resistant'] = data.iloc[:, dha_ppq_lum_triple_resistant].sum(axis=1)
dha_ppq_double_resistant = [3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63]
data['DHA-PPQ double-resistant'] = data.iloc[:, dha_ppq_double_resistant].sum(axis=1)
asaq_double_resistant = [50, 51, 54, 55]
data['ASAQ double-resistant'] = data.iloc[:, asaq_double_resistant].sum(axis=1)
al_double_resistant = [10, 11, 14, 15]
data['AL double-resistant'] = data.iloc[:, al_double_resistant].sum(axis=1)

print(data[['DHA-PPQ, AQ triple-resistant', 'DHA-PPQ, LUM triple-resistant',
            'DHA-PPQ double-resistant', 'ASAQ double-resistant', 'AL double-resistant']])

# settings
plt.style.use('ggplot')
plt.rcParams['savefig.dpi'] = 300
plt.figure(figsize=(8, 6))

# CYCLING
# plt.axvline(x=0, color='grey', linestyle='--')
# plt.text(0+0.5, 0.95, 'CQ', rotation=0, color='grey')
# plt.axvline(x=15, color='grey', linestyle='--')
# plt.text(15+0.5, 0.95, 'LM', rotation=0, color='grey')
# plt.axvline(x=39, color='grey', linestyle='--')
# plt.text(39+0.5, 0.95, 'ASAQ', rotation=0, color='grey')

# plot data
plt.plot(data.index, data['DHA-PPQ, AQ triple-resistant'], label='DHA-PPQ, AQ triple-resistant')
plt.plot(data.index, data['DHA-PPQ, LUM triple-resistant'], label='DHA-PPQ, LUM triple-resistant')
plt.plot(data.index, data['DHA-PPQ double-resistant'], label='DHA-PPQ double-resistant')
plt.plot(data.index, data['ASAQ double-resistant'], label='ASAQ double-resistant')
plt.plot(data.index, data['AL double-resistant'], label='AL double-resistant')

# settings
plt.xlabel('Transmission cycles', fontsize=12)
plt.ylabel('Frequency (unitless)', fontsize=12)
plt.title('Frequency of resistant clones across generations', fontsize=12)

# grid, legend
plt.grid(True)
plt.legend(loc='upper left')
plt.ylim(0, 1)

plt.show()
