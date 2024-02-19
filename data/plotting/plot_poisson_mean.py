import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

csv_file_path = '../poisson_mean.csv'
data = pd.read_csv(csv_file_path, header = None)

plt.figure(figsize=(20, 10))
sns.set(style="whitegrid")

print(data)

plt.xlabel('Generation')
plt.ylabel('Poisson mean')
plt.title('Poisson mean (moi) over generations')
plt.plot(data.iloc[:])
plt.grid(True)

plt.show()
