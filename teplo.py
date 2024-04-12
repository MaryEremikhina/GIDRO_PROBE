import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv('5_13_20_13.csv', delimiter=';')
df1 = df.copy()
df1 = df1.iloc[:, :-2]
df1.dropna(inplace=True)
timing = []
columns = list(df1.columns)
for i in range(50):
    timing.append(i) # время должно быть записано в самом файле с помощью модуля RTC

np.random.seed(0)
for x in columns:
    data = {'pressure': np.tile(df1['Pressure'], 1),
    'data': np.repeat(timing, 1),
    'temperature': df1[x]
    }

    df = pd.DataFrame(data, columns=['pressure', 'data', x])
    df = df.pivot(index='pressure', columns='data', values=x)

    sns.heatmap(df)
    plt.tight_layout()
    plt.savefig(f'teplo/{x}.png', dpi=120)