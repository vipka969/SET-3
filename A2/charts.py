import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

plt.style.use('default')
plt.rcParams['figure.figsize'] = (15, 5)

path = "/Users/mac/Desktop/c++ unik/set3_a2/cmake-build-debug"

def plot_comparison():
    fig, axes = plt.subplots(1, 3, figsize=(18, 6))

    array_types = ['random', 'reverse_sorted', 'almost_sorted']
    titles = ['Случайные массивы', 'Обратно отсортированные', 'Почти отсортированные']

    for i, (array_type, title) in enumerate(zip(array_types, titles)):
        std_data = pd.read_csv(f'{path}/{array_type}-1.csv')
        hybrid_data = pd.read_csv(f'{path}/{array_type}-2.csv')

        axes[i].plot(std_data['size'], std_data['time_micros'],
                     'b-', linewidth=2, label='Standard Merge Sort', alpha=0.8)
        axes[i].plot(hybrid_data['size'], hybrid_data['time_micros'],
                     'r-', linewidth=2, label='Hybrid Merge+Insertion Sort', alpha=0.8)

        axes[i].set_title(title, fontsize=14, fontweight='bold')
        axes[i].set_xlabel('Размер массива')
        axes[i].set_ylabel('Время (микросекунды)')
        axes[i].legend()
        axes[i].grid(True, alpha=0.3)

        improvement = ((std_data['time_micros'] - hybrid_data['time_micros']) /
                       std_data['time_micros'] * 100).mean()
        axes[i].text(0.05, 0.95, f'Улучшение: {improvement:.1f}%',
                     transform=axes[i].transAxes, fontsize=12,
                     bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))

    plt.tight_layout()
    plt.savefig('comparison_results.png', dpi=300, bbox_inches='tight')
    plt.show()

def plot_individual_graphs():
    array_types = ['random', 'reverse_sorted', 'almost_sorted']
    titles = ['Случайные массивы', 'Обратно отсортированные', 'Почти отсортированные']

    for array_type, title in zip(array_types, titles):
        plt.figure(figsize=(10, 6))

        std_data = pd.read_csv(f'{path}/{array_type}-1.csv')
        hybrid_data = pd.read_csv(f'{path}/{array_type}-2.csv')

        plt.plot(std_data['size'], std_data['time_micros'],
                 'bo-', linewidth=2, label='Standard Merge Sort', markersize=3, alpha=0.7)
        plt.plot(hybrid_data['size'], hybrid_data['time_micros'],
                 'ro-', linewidth=2, label='Hybrid Merge+Insertion Sort', markersize=3, alpha=0.7)

        plt.title(f'Сравнение алгоритмов: {title}', fontsize=16, fontweight='bold')
        plt.xlabel('Размер массива', fontsize=12)
        plt.ylabel('Время выполнения (микросекунды)', fontsize=12)
        plt.legend(fontsize=11)
        plt.grid(True, alpha=0.3)

        improvement = ((std_data['time_micros'] - hybrid_data['time_micros']) /
                       std_data['time_micros'] * 100).mean()

        plt.text(0.05, 0.95, f'Среднее улучшение: {improvement:.1f}%',
                 transform=plt.gca().transAxes, fontsize=12,
                 bbox=dict(boxstyle="round,pad=0.3", facecolor="yellow", alpha=0.7))

        plt.tight_layout()
        plt.savefig(f'{array_type}_comparison.png', dpi=300, bbox_inches='tight')
        plt.show()

def plot_time_complexity():
    plt.figure(figsize=(12, 8))

    array_types = ['random', 'reverse_sorted', 'almost_sorted']
    colors = ['blue', 'red', 'green']
    labels = ['Случайные', 'Обратно отсортированные', 'Почти отсортированные']

    for i, array_type in enumerate(array_types):
        data = pd.read_csv(f'{path}/{array_type}-1.csv')

        sizes = data['size']
        times = data['time_micros']

        plt.subplot(2, 2, 1)
        plt.loglog(sizes, times, 'o-', color=colors[i], label=labels[i], alpha=0.7)

        plt.subplot(2, 2, 2)
        plt.plot(sizes, times, 'o-', color=colors[i], label=labels[i], alpha=0.7)

        plt.subplot(2, 2, 3)
        normalized_time = times / (sizes * np.log2(sizes))
        plt.plot(sizes, normalized_time, 'o-', color=colors[i], label=labels[i], alpha=0.7)

    plt.subplot(2, 2, 1)
    plt.title('Логарифмический масштаб')
    plt.xlabel('Размер массива (log)')
    plt.ylabel('Время (log)')
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.subplot(2, 2, 2)
    plt.title('Линейный масштаб')
    plt.xlabel('Размер массива')
    plt.ylabel('Время (микросекунды)')
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.subplot(2, 2, 3)
    plt.title('Нормализованное время')
    plt.xlabel('Размер массива')
    plt.ylabel('Нормализованное время')
    plt.legend()
    plt.grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig('time_complexity_analysis.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    print("Начинаем анализ результатов...")

    plot_comparison()

    plot_individual_graphs()

    plot_time_complexity()

    print("Анализ завершен")