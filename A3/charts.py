import pandas as pd
import matplotlib.pyplot as plt
import os

plt.style.use('seaborn-v0_8')

class SortingAnalyzer:
    def __init__(self, data_path="/Users/mac/Desktop/c++ unik/set3_a3/cmake-build-debug"):
        self.data_path = data_path
        self.files = {
            'quick_random': 'quick_random.csv',
            'quick_reverse_sorted': 'quick_reverse_sorted.csv',
            'quick_almost_sorted': 'quick_almost_sorted.csv',
            'intro_random': 'intro_random.csv',
            'intro_reverse_sorted': 'intro_reverse_sorted.csv',
            'intro_almost_sorted': 'intro_almost_sorted.csv'
        }

    def load_data(self):
        self.data = {}
        for key, filename in self.files.items():
            full_path = os.path.join(self.data_path, filename)
            try:
                self.data[key] = pd.read_csv(full_path)
                print(f"Загружен {filename}: {len(self.data[key])} записей")
            except FileNotFoundError:
                print(f"Файл {filename} не найден")

    def plot_quick_sort_results(self):
        if not any('quick' in key for key in self.data.keys()):
            print("Нет данных для Quick Sort")
            return

        fig, axes = plt.subplots(1, 3, figsize=(18, 5))
        fig.suptitle('Стандартный Quick Sort', fontsize=16, fontweight='bold')

        if 'quick_random' in self.data:
            axes[0].plot(self.data['quick_random']['size'],
                         self.data['quick_random']['time_micros'],
                         linewidth=2, color='blue')
            axes[0].set_title('Случайные массивы')
            axes[0].set_xlabel('Размер массива')
            axes[0].set_ylabel('Время (микросекунды)')
            axes[0].grid(True, alpha=0.3)

        if 'quick_reverse_sorted' in self.data:
            axes[1].plot(self.data['quick_reverse_sorted']['size'],
                         self.data['quick_reverse_sorted']['time_micros'],
                         linewidth=2, color='red')
            axes[1].set_title('Обратно отсортированные массивы')
            axes[1].set_xlabel('Размер массива')
            axes[1].set_ylabel('Время (микросекунды)')
            axes[1].grid(True, alpha=0.3)

        if 'quick_almost_sorted' in self.data:
            axes[2].plot(self.data['quick_almost_sorted']['size'],
                         self.data['quick_almost_sorted']['time_micros'],
                         linewidth=2, color='green')
            axes[2].set_title('Почти отсортированные массивы')
            axes[2].set_xlabel('Размер массива')
            axes[2].set_ylabel('Время (микросекунды)')
            axes[2].grid(True, alpha=0.3)

        plt.tight_layout()
        plt.savefig('quick_sort_results.png', dpi=300, bbox_inches='tight')
        plt.show()

    def plot_introsort_results(self):
        if not any('intro' in key for key in self.data.keys()):
            print("Нет данных для Introsort")
            return

        fig, axes = plt.subplots(1, 3, figsize=(18, 5))
        fig.suptitle('Гибридный Introsort', fontsize=16, fontweight='bold')

        if 'intro_random' in self.data:
            axes[0].plot(self.data['intro_random']['size'],
                         self.data['intro_random']['time_micros'],
                         linewidth=2, color='blue')
            axes[0].set_title('Случайные массивы')
            axes[0].set_xlabel('Размер массива')
            axes[0].set_ylabel('Время (микросекунды)')
            axes[0].grid(True, alpha=0.3)

        if 'intro_reverse_sorted' in self.data:
            axes[1].plot(self.data['intro_reverse_sorted']['size'],
                         self.data['intro_reverse_sorted']['time_micros'],
                         linewidth=2, color='red')
            axes[1].set_title('Обратно отсортированные массивы')
            axes[1].set_xlabel('Размер массива')
            axes[1].set_ylabel('Время (микросекунды)')
            axes[1].grid(True, alpha=0.3)

        if 'intro_almost_sorted' in self.data:
            axes[2].plot(self.data['intro_almost_sorted']['size'],
                         self.data['intro_almost_sorted']['time_micros'],
                         linewidth=2, color='green')
            axes[2].set_title('Почти отсортированные массивы')
            axes[2].set_xlabel('Размер массива')
            axes[2].set_ylabel('Время (микросекунды)')
            axes[2].grid(True, alpha=0.3)

        plt.tight_layout()
        plt.savefig('introsort_results.png', dpi=300, bbox_inches='tight')
        plt.show()

    def plot_comparison(self):
        fig, axes = plt.subplots(1, 3, figsize=(18, 5))
        fig.suptitle('Сравнение Quick Sort и Introsort', fontsize=16, fontweight='bold')

        if 'quick_random' in self.data and 'intro_random' in self.data:
            axes[0].plot(self.data['quick_random']['size'],
                         self.data['quick_random']['time_micros'],
                         label='Quick Sort', linewidth=2)
            axes[0].plot(self.data['intro_random']['size'],
                         self.data['intro_random']['time_micros'],
                         label='Introsort', linewidth=2)
            axes[0].set_title('Случайные массивы')
            axes[0].set_xlabel('Размер массива')
            axes[0].set_ylabel('Время (микросекунды)')
            axes[0].legend()
            axes[0].grid(True, alpha=0.3)

        if 'quick_reverse_sorted' in self.data and 'intro_reverse_sorted' in self.data:
            axes[1].plot(self.data['quick_reverse_sorted']['size'],
                         self.data['quick_reverse_sorted']['time_micros'],
                         label='Quick Sort', linewidth=2)
            axes[1].plot(self.data['intro_reverse_sorted']['size'],
                         self.data['intro_reverse_sorted']['time_micros'],
                         label='Introsort', linewidth=2)
            axes[1].set_title('Обратно отсортированные массивы')
            axes[1].set_xlabel('Размер массива')
            axes[1].set_ylabel('Время (микросекунды)')
            axes[1].legend()
            axes[1].grid(True, alpha=0.3)

        if 'quick_almost_sorted' in self.data and 'intro_almost_sorted' in self.data:
            axes[2].plot(self.data['quick_almost_sorted']['size'],
                         self.data['quick_almost_sorted']['time_micros'],
                         label='Quick Sort', linewidth=2)
            axes[2].plot(self.data['intro_almost_sorted']['size'],
                         self.data['intro_almost_sorted']['time_micros'],
                         label='Introsort', linewidth=2)
            axes[2].set_title('Почти отсортированные массивы')
            axes[2].set_xlabel('Размер массива')
            axes[2].set_ylabel('Время (микросекунды)')
            axes[2].legend()
            axes[2].grid(True, alpha=0.3)

        plt.tight_layout()
        plt.savefig('comparison_results.png', dpi=300, bbox_inches='tight')
        plt.show()
if __name__ == "__main__":
    analyzer = SortingAnalyzer()

    print("Загрузка данных...")
    analyzer.load_data()

    if analyzer.data:
        print("\nСтандартный Quick Sort")
        analyzer.plot_quick_sort_results()

        print("Гибридный Introsort")
        analyzer.plot_introsort_results()

        print("\nСравнительный анализ")
        analyzer.plot_comparison()

        print("\nГрафики сохранены")
    else:
        print("Не удалось загрузить данные")