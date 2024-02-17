import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

csv_file_path = '../mean_fitness.csv'
data = pd.read_csv(csv_file_path)

plt.figure(figsize=(20, 10))
sns.set(style="whitegrid")

plt.plot(data.iloc[:])

plt.xlabel('Generation')
plt.ylabel('Mean fitness (unitless)')
plt.title('Mean fitness over generations')

plt.grid(True)

plt.show()
