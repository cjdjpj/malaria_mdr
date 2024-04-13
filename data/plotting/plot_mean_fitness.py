import pandas as pd
import matplotlib.pyplot as plt

csv_file_path = '../mean_fitness.csv'
data = pd.read_csv(csv_file_path, header = None)

data = data.iloc[1:]

print(data)

plt.style.use('ggplot')
plt.xlabel('Transmission cycles', fontsize = 12)
plt.ylabel('Mean fitness (unitless)', fontsize = 12)
plt.title('Mean fitness of infected hosts across generations', fontsize = 12)

plt.grid(True)
plt.plot(data.iloc[:])
plt.show()