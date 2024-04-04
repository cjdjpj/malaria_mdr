import pandas as pd
import matplotlib.pyplot as plt

csv_file_path = '../g_freqs.csv'
data = pd.read_csv(csv_file_path, header=None)

dha_ppq_aq_triple_resistant = [39, 55]  
data['DHA-PPQ, AQ triple-resistant'] = data.iloc[:, dha_ppq_aq_triple_resistant].sum(axis=1)

dha_ppq_lum_triple_resistant = [11, 27]  
data['DHA-PPQ, LUM triple-resistant'] = data.iloc[:, dha_ppq_lum_triple_resistant].sum(axis=1)

dha_ppq_double_resistant = [3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63]  
data['DHA-PPQ double-resistant'] = data.iloc[:, dha_ppq_double_resistant].sum(axis=1)

asaq_double_resistant = [38, 39, 54, 55]  
data['ASAQ double-resistant'] = data.iloc[:, asaq_double_resistant].sum(axis=1)

al_double_resistant = [10, 11, 26, 27]  
data['AL double-resistant'] = data.iloc[:, al_double_resistant].sum(axis=1)

print(data[['DHA-PPQ, AQ triple-resistant', 'DHA-PPQ, LUM triple-resistant', 'DHA-PPQ double-resistant', 'ASAQ double-resistant', 'AL double-resistant']])

plt.figure(figsize=(20, 10))
plt.plot(data.index, data['DHA-PPQ, AQ triple-resistant'], label='DHA-PPQ, AQ triple-resistant')
plt.plot(data.index, data['DHA-PPQ, LUM triple-resistant'], label='DHA-PPQ, LUM triple-resistant')
plt.plot(data.index, data['DHA-PPQ double-resistant'], label='DHA-PPQ double-resistant')
plt.plot(data.index, data['ASAQ double-resistant'], label='ASAQ double-resistant')
plt.plot(data.index, data['AL double-resistant'], label='AL double-resistant')
plt.title('Frequency of resistant clones over generations')
plt.xlabel('Generation')
plt.ylabel('Frequency')
plt.legend(loc='upper right')
plt.grid(True)
plt.ylim(0, 1)
plt.show()
