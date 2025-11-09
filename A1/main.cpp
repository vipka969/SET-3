#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>
#include <cmath>

double x1, x2, x3;
double y_1, y2, y3;
double r1, r2, r3;

bool ChekPoint(double x, double y) {
  if ((x - x1) * (x - x1) + (y - y_1) * (y - y_1) <= r1 * r1 &&
    (x - x2) * (x - x2) + (y - y2) * (y - y2) <= r2 * r2 && (x - x3) * (x - x3) + (y - y3) * (y - y3) <= r3 * r3) {
    return true;
  }
  return false;
}

double MonteCarlo(double min_x, double max_x, double min_y, double max_y, int n) {
  int points = 0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist_x(min_x, max_x);
  std::uniform_real_distribution<> dist_y(min_y, max_y);


  for (int i = 0; i < n; i++) {
    double x = dist_x(gen);
    double y = dist_y(gen);

    if (ChekPoint(x, y)) {
      points++;
    }
  }

  double s_rect = (max_x - min_x) * (max_y - min_y);
  double res = (points / (double) n) * s_rect;
  return res;
}

int main() {

  x1 = 1.0; y_1 = 1.0; r1 = 1.0;
  x2 = 1.5; y2 = 2.0; r2 = std::sqrt(5)/2;
  x3 = 2.0; y3 = 1.5; r3 = std::sqrt(5)/2;

  double max_r = std::max(r1, std::max(r2, r3));
  double min_x = std::min(x1, std::min(x2, x3)) - max_r;
  double max_x = std::max(x1, std::max(x2, x3)) + max_r;
  double min_y = std::min(y_1, std::min(y2, y3)) - max_r;
  double max_y = std::max(y_1, std::max(y2, y3)) + max_r;

  double narrow_min_x = 0.8;
  double narrow_max_x = 2.2;
  double narrow_min_y = 0.8;
  double narrow_max_y = 2.2;

  double pi = 3.14159265358979323846;
  double theta = asin(0.8);
  double s = 0.25 * pi + 1.25 * theta - 1.0;



  std::ofstream out1("chart1.csv");
  std::ofstream out2("chart2.csv");

  out1 << "N,S_wide,S_narrow,S_exact\n";
  out2 << "N,error_wide,error_narrow\n";

  for (int n = 100; n <= 100000; n += 500) {
    double s_wide = MonteCarlo(min_x, max_x, min_y, max_y, n);
    double s_narrow = MonteCarlo(narrow_min_x, narrow_max_x, narrow_min_y, narrow_max_y, n);

    double error_wide = std::fabs(s_wide - s) / s;
    double error_narrow = std::fabs(s_narrow - s) / s;

    out1 << n << "," << s_wide << "," << s_narrow << "," << s << "\n";
    out2 << n << "," << error_wide << "," << error_narrow << "\n";
  }

  out1.close();
  out2.close();

  return 0;
}