#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPen>
#include <QRegularExpressionValidator>
#include <QStack>
#include <QString>
#include <QVector>

extern "C" {
#include "../Backend/back.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QString StringCalc;
  char result_string[255] = {0};
  long double xValue = 0;
  long double resultValue = 0;
  char *mainData = {0}, *xData = {0};
  bool select_dot = false;
  bool number_select = false;
  bool operator_select = false;
  int open_bracket_count = 0;
  bool x_select = false;

 private slots:
  void digits_numbers();
  void plus_minus_operator();
  void clear_operator();
  void mult_div_operator();
  void dot_operator();
  void open_bracket();
  void closed_bracket();
  void x_function();
  void mod_operator();
  void pow_operator();
  void functions();
  void equal_function();
  void check_result(long double result_value, char *output);
  void annuity_front();
  void diff_front();
  void graph_func();
};
#endif  // MAINWINDOW_H
