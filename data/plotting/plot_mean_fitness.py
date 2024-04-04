import pandas as pd
import matplotlib.pyplot as plt

csv_file_path = '../mean_fitness.csv'
data = pd.read_csv(csv_file_path, header = None)

data = data.iloc[1:]

print(data)

plt.xlabel('Generation')
plt.ylabel('Mean fitness (unitless)')
plt.title('Mean fitness of infected hosts over generations')

plt.grid(True)
plt.plot(data.iloc[:])
plt.show()