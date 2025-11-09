import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('seaborn-v0_8')
plt.rcParams['figure.figsize'] = (12, 5)

chart1 = pd.read_csv('cmake-build-debug/chart1.csv')
chart2 = pd.read_csv('cmake-build-debug/chart2.csv')

print("Данные загружены:")
print(f"Количество экспериментов: {len(chart1)}")
print(f"Точное значение площади: {chart1['S_exact'][0]:.6f}")

plt.figure(figsize=(14, 6))

plt.subplot(1, 2, 1)
plt.semilogx(chart1['N'], chart1['S_wide'], 'b-', label='Широкая область', alpha=0.8, linewidth=2)
plt.semilogx(chart1['N'], chart1['S_narrow'], 'r-', label='Узкая область', alpha=0.8, linewidth=2)
plt.axhline(y=chart1['S_exact'][0], color='black', linestyle='--', label='Точное значение', linewidth=2)
plt.xlabel('Количество точек')
plt.ylabel('Приближенная площадь')
plt.title('Зависимость площади от количества точек')
plt.legend()
plt.grid(True, alpha=0.3)

plt.subplot(1, 2, 2)
plt.loglog(chart2['N'], chart2['error_wide'], 'b-', label='Широкая область', alpha=0.8, linewidth=2)
plt.loglog(chart2['N'], chart2['error_narrow'], 'r-', label='Узкая область', alpha=0.8, linewidth=2)

N_theoretical = np.logspace(2, 5, 50)
error_theoretical = 0.5 / np.sqrt(N_theoretical)
plt.loglog(N_theoretical, error_theoretical, 'k--', label='Теоретическая ~1/√N', alpha=0.5)

plt.xlabel('Количество точек')
plt.ylabel('Относительное отклонение')
plt.title('Зависимость относительного отклонения от количества точек')
plt.legend()
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('monte_carlo_analysis.png', dpi=300, bbox_inches='tight')

print("\nСтатистика по последним 10 экспериментам:")
print(f"Средняя ошибка (широкая область): {chart2['error_wide'].tail(10).mean():.4f}")
print(f"Средняя ошибка (узкая область): {chart2['error_narrow'].tail(10).mean():.4f}")
print(f"Минимальная ошибка (узкая область): {chart2['error_narrow'].min():.4f}")

plt.show()
