import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# до кластеризации
df = pd.read_csv("/Users/amakarshina/CLionProjects/k-means/mall_data.csv")
df2 = pd.read_csv("/Users/amakarshina/CLionProjects/k-means/output.csv")
#sns.scatterplot(x=df2["x"], y=df2["y"])
#plt.title("Диаграмма распределения  (y) по (x) до кластеризации")

# после кластеризации
#plt.figure()
sns.scatterplot(x=df2["x"], y=df2["y"],
                 hue=df2["c"],
                 palette=sns.color_palette("hls", n_colors=5),
                 size = 2
                 )
plt.title("Кластеризация:(y) по (x)")

plt.show()