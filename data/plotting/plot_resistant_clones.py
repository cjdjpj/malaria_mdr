import pandas as pd
import matplotlib.pyplot as plt

csv_file_path = '../g_freqs.csv'
data = pd.read_csv(csv_file_path, header=None)

triply_resistant = [7, 11, 13, 14, 15]  # Columns representing triply resistant clones
data['triply resistant'] = data.iloc[:, triply_resistant].sum(axis=1)

doubly_resistant = [7, 11, 13, 14, 15, 3, 5, 6, 9, 12]  # Additional columns to sum
data['doubly resistant'] = data.iloc[:, doubly_resistant].sum(axis=1)

print(data[['triply resistant', 'doubly resistant']])

plt.figure(figsize=(20, 10))
plt.plot(data.index, data['triply resistant'], label='triply resistant')
plt.plot(data.index, data['doubly resistant'], label='doubly resistant')
plt.title('Frequency of resistant clones over generations')
plt.xlabel('Generation')
plt.ylabel('Frequency')
plt.legend(loc='upper right')
plt.grid(True)
plt.ylim(0, 1)
plt.show()
