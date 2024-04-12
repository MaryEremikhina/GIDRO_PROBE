import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('5_13_20_13.csv', delimiter=';')
df1 = df.copy()
df1 = df1.iloc[:, :-2]
df1.dropna(inplace=True)
timing = []
columns = list(df1.columns)
for i in range(50):
    timing.append(i) # время должно быть записано в самом файле с помощью модуля RTC
for x in columns:
    plt.plot(timing, df1[x], color='blue', linestyle='-', label=f'{x}') # вместо timing будет df1['Time']
    plt.xlabel('Время работы цикла')
    plt.ylabel(f'{x}')
    plt.title(f'Зависимость {x} от времени')
    plt.legend()

    plt.savefig(f'data/{x}.png')