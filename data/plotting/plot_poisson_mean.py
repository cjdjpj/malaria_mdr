import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

csv_file_path = '../poisson_mean.csv'
data = pd.read_csv(csv_file_path)

plt.figure(figsize=(20, 10))
sns.set(style="whitegrid")

plt.plot(data.iloc[:])

plt.xlabel('Generation')
plt.ylabel('Poisson mean')
plt.title('Poisson mean (moi) over generations')

plt.grid(True)

plt.show()
