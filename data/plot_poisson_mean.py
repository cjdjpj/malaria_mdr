import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
csv_file_path = '../data/poisson_mean.csv'
data = pd.read_csv(csv_file_path)

# Increase the figure size for better readability
plt.figure(figsize=(20, 10))

plt.plot(data.iloc[:])

# Add labels and title
plt.xlabel('Generation')
plt.ylabel('Poisson mean')
plt.title('Poisson mean (moi) across generations')


# Add grid for better readability
plt.grid(True)

# Show the plot
plt.show()
