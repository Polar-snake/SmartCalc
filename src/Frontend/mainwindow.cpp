#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->plot->setBackground(QColor(50, 50, 50, 100));
  ui->plot->xAxis->setBasePen(
      QPen(Qt::white, 2));  // устанавливаем белый цвет разметки по оси X
  ui->plot->yAxis->setBasePen(
      QPen(Qt::white, 2));  // устанавливаем белый цвет разметки по оси Y
  ui->plot->xAxis->setTickLabelColor(Qt::white);
  ui->plot->yAxis->setTickLabelColor(Qt::white);
  //  QPen pen(Qt::magenta); // Создание фиолетовой ручки (линии)
  //  ui->plot->addGraph();
  //  ui->plot->graph(0)->setPen(pen); // Установка фиолетового цвета для
  //  графика

  QRegularExpressionValidator *regexXFilter =
      new QRegularExpressionValidator(QRegularExpression(
          "^(-?100000000000(\\.0{1,6})?|(-?[0-9]{1,11})(\\.[0-9]{1,6})?)$"));
  ui->x_input->setValidator(regexXFilter);

  QRegularExpressionValidator *regexAmount = new QRegularExpressionValidator(
      QRegularExpression("^(0*|([1-9][0-9]{0,8}))(\\.[0-9]{1,2})?$"));
  ui->loan_amount->setValidator(regexAmount);

  QRegularExpressionValidator *regexPeriod = new QRegularExpressionValidator(
      QRegularExpression("^(0|[1-5]?[0-9]{2}|600)$"));
  ui->period->setValidator(regexPeriod);

  QRegularExpressionValidator *regexInterest = new QRegularExpressionValidator(
      QRegularExpression("^(100(\\.0{1,2})?|([0-9]{1,2})(\\.[0-9]{1,2})?)$"));
  ui->interest_rate->setValidator(regexInterest);

  connect(ui->zero, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->one, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->two, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->three, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->four, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->five, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->six, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->seven, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->eight, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->nine, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(plus_minus_operator()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(plus_minus_operator()));
  connect(ui->clear, SIGNAL(clicked()), this, SLOT(clear_operator()));
  connect(ui->multiply, SIGNAL(clicked()), this, SLOT(mult_div_operator()));
  connect(ui->division, SIGNAL(clicked()), this, SLOT(mult_div_operator()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(dot_operator()));
  connect(ui->left_bracket, SIGNAL(clicked()), this, SLOT(open_bracket()));
  connect(ui->right_bracket, SIGNAL(clicked()), this, SLOT(closed_bracket()));
  connect(ui->x_button, SIGNAL(clicked()), this, SLOT(x_function()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(mod_operator()));
  connect(ui->pow, SIGNAL(clicked()), this, SLOT(pow_operator()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->x_button, SIGNAL(clicked()), this, SLOT(x_function()));
  connect(ui->equal, SIGNAL(clicked()), this, SLOT(equal_function()));
  connect(ui->count_ann, SIGNAL(clicked()), this, SLOT(annuity_front()));
  connect(ui->count_diff, SIGNAL(clicked()), this, SLOT(diff_front()));
  connect(ui->build_plot, SIGNAL(clicked()), this, SLOT(graph_func()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  if (StringCalc.length() != 0 && x_select == false &&
      StringCalc.back() != ')') {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);  // changed SetText to StringCalc
    number_select = true;
    operator_select = false;
  } else if (StringCalc.length() == 0) {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);  // changed SetText to StringCalc
    number_select = true;
    operator_select = false;
  }
}

void MainWindow::clear_operator() {
  // QPushButton *button = (QPushButton *)sender();
  StringCalc.clear();
  ui->output_display->setText("0");
  select_dot = false;
  number_select = false;
  operator_select = false;
  x_select = false;
  open_bracket_count = 0;
}

void MainWindow::plus_minus_operator() {
  if (StringCalc.length() != 0 && operator_select == false &&
      StringCalc.back() != '.') {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    select_dot = false;
    number_select = false;
    operator_select = true;
    x_select = false;
  } else if (StringCalc.length() ==
             0) {  // put minus or plus in the beginning of string
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    select_dot = false;
    number_select = false;
    operator_select = true;
    x_select = false;
  }
}

void MainWindow::mult_div_operator() {
  if (operator_select == false && StringCalc.length() != 0 &&
      StringCalc.back() != '.' && StringCalc.back() != '(') {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);  // changed SetText to StringCalc
    select_dot = false;
    number_select = false;
    operator_select = true;
    x_select = false;
  }
}

void MainWindow::dot_operator() {
  if (select_dot == false && number_select == true &&
      StringCalc.back() != ')') {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    select_dot = true;
    x_select = false;
  }
}

void MainWindow::open_bracket() {
  if (StringCalc.length() != 0 && StringCalc.back() != '.' &&
      number_select == false && x_select == false) {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    operator_select = false;
    open_bracket_count++;
    // x_select = false;

  } else if (StringCalc.length() == 0) {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    operator_select = false;
    open_bracket_count++;
    // x_select = false;
  }
}

void MainWindow::closed_bracket() {
  if (open_bracket_count > 0 && StringCalc.back() != '.' &&
      (StringCalc.back() == ')' || number_select == true || x_select == true)) {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    operator_select = false;
    open_bracket_count--;
  }
}

void MainWindow::x_function() {
  if (StringCalc.length() != 0 && select_dot == false &&
      number_select == false && x_select == false && StringCalc.back() != ')') {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    x_select = true;
    number_select = false;
    operator_select = false;
  } else if (StringCalc.length() == 0) {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text();
    ui->output_display->setText(StringCalc);
    x_select = true;
    number_select = false;
    operator_select = false;
  }
}

void MainWindow::mod_operator() {
  if (operator_select == false && StringCalc.length() != 0 &&
      StringCalc.back() != '.' && StringCalc.back() != '(') {
    // QPushButton *button = (QPushButton *)sender();
    StringCalc += "%";
    ui->output_display->setText(StringCalc);
    select_dot = false;
    number_select = false;
    operator_select = true;
    x_select = false;
  }
}

void MainWindow::pow_operator() {
  if (StringCalc.length() != 0 && StringCalc.back() != '.' &&
      (StringCalc.back() == ')' || number_select == true || x_select == true)) {
    // QPushButton *button = (QPushButton *)sender();
    StringCalc += "^(";
    ui->output_display->setText(StringCalc);
    select_dot = false;
    number_select = false;
    x_select = false;
    open_bracket_count++;
  }
}

void MainWindow::functions() {
  if (StringCalc.length() != 0 && number_select == false &&
      select_dot == false && x_select == false && StringCalc.back() != ')') {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text() + "(";
    ui->output_display->setText(StringCalc);
    operator_select = false;
    open_bracket_count++;
  } else if (StringCalc.length() == 0) {
    QPushButton *button = (QPushButton *)sender();
    StringCalc += button->text() + "(";
    ui->output_display->setText(StringCalc);
    operator_select = false;
    open_bracket_count++;
  }
}
void MainWindow::equal_function() {
  if (open_bracket_count == 0 && StringCalc.length() != 0 &&
      operator_select == false) {
    QByteArray mainDisplay = StringCalc.toLocal8Bit();
    mainData = mainDisplay.data();
    xValue = ui->x_input->text().toDouble();
    //        ui->expression->setText(StringCalc);
    int returnCode = parser(mainData, xValue, &resultValue);
    if (returnCode == 0) {
      ui->output_display->setText("ERROR");
      StringCalc.clear();
      number_select = false;
      select_dot = false;
      operator_select = false;
      x_select = false;
      open_bracket_count = 0;
    } else {
      check_result(resultValue, result_string);
      ui->output_display->setText(result_string);
      StringCalc.clear();
      number_select = false;
      select_dot = false;
      operator_select = false;
      x_select = false;
      open_bracket_count = 0;
    }
  }
}

void MainWindow::check_result(long double result_value, char *output) {
  long double truncated_value = truncl(result_value);
  if (isinf(result_value) || isnan(result_value)) {
    sprintf(output, "calc error");
  } else if (result_value == truncated_value) {
    sprintf(output, "%.0Lf", result_value);
  } else {
    sprintf(output, "%.7Lf", result_value);
  }
  if (strlen(output) > 22) {
    sprintf(output, "%Le", result_value);
  }
}

void MainWindow::annuity_front() {
  double loan_amount_var = ui->loan_amount->text().toDouble();
  double interest_rate_var = ui->interest_rate->text().toDouble();
  double period_var = ui->period->text().toDouble();
  if (ui->loan_amount->text().isEmpty() == 0 &&
      ui->period->text().isEmpty() == 0 &&
      ui->interest_rate->text().isEmpty() == 0 && period_var != 0) {
    double month_payment_var = 0;
    double amount_overpay_var = 0;
    double total_cost_var = 0;
    annuity(loan_amount_var, interest_rate_var, period_var, &month_payment_var,
            &amount_overpay_var, &total_cost_var);
    ui->month_payment->setNum(month_payment_var);
    ui->amount_overpay_ann->setNum(amount_overpay_var);
    ui->total_cost_ann->setNum(total_cost_var);
  } else {
    ui->month_payment->setText("0");
    ui->amount_overpay_ann->setText("0");
    ui->total_cost_ann->setText("0");
  }
}

void MainWindow::diff_front() {
  double loan_amount_var = ui->loan_amount->text().toDouble();
  double interest_rate_var = ui->interest_rate->text().toDouble();
  double period_var = ui->period->text().toDouble();
  if (ui->loan_amount->text().isEmpty() == 0 &&
      ui->period->text().isEmpty() == 0 &&
      ui->interest_rate->text().isEmpty() == 0 && period_var != 0) {
    double first_payment_var = 0;
    double last_payment_var = 0;
    double amount_overpay_var = 0;
    double total_cost_var = 0;
    differential(loan_amount_var, interest_rate_var, period_var,
                 &first_payment_var, &last_payment_var, &amount_overpay_var,
                 &total_cost_var);
    ui->first_payment->setNum(first_payment_var);
    ui->last_payment->setNum(last_payment_var);
    ui->amount_overpay_diff->setNum(amount_overpay_var);
    ui->total_cost_diff->setNum(total_cost_var);
  } else {
    ui->first_payment->setText("0");
    ui->last_payment->setText("0");
    ui->amount_overpay_diff->setText("0");
    ui->total_cost_diff->setText("0");
  }
}

void MainWindow::graph_func() {
  ui->plot->clearGraphs();
  QByteArray mainDisplay = ui->output_display->text().toLocal8Bit();
  mainData = mainDisplay.data();
  QVector<double> x, y;
  long double xBegin = ui->X_min->value();
  long double xEnd = ui->X_max->value();
  long double yBegin = ui->Y_min->value();
  long double yEnd = ui->Y_max->value();
  long double step = 0.1;
  long double Y = 0;
  if (ui->x_input->text().isEmpty() == 1) {  // 1 - empty, 0 not empty
    for (long double i = xBegin; i < xEnd; i += step) {
      parser(mainData, i, &Y);
      x.push_back(i);
      y.push_back(Y);
    }
  } else {
    for (long double i = xBegin; i < xEnd; i += step) {
      parser(mainData, xValue, &Y);
      x.push_back(i);
      y.push_back(Y);
    }
  }
  ui->plot->xAxis->setRange(xBegin, xEnd);
  ui->plot->yAxis->setRange(yBegin, yEnd);

  //    ui->plot->xAxis->setBasePen(QPen(Qt::white, 2)); // устанавливаем белый
  //    цвет разметки по оси X ui->plot->yAxis->setBasePen(QPen(Qt::white, 2));
  //    // устанавливаем белый цвет разметки по оси Y

  ////    ui->plot->xAxis->setLabelColor(Qt ::white);
  ////    ui->plot->yAxis->setLabelColor(Qt::white);

  //    ui->plot->xAxis->setTickLabelColor(Qt::white);
  //    ui->plot->yAxis->setTickLabelColor(Qt::white);

  ui->plot->addGraph();
  //    ui->plot->graph(0)->setPen(pen);
  ui->plot->graph(0)->setData(x, y);
  ui->plot->replot();
  ui->plot->update();
  x.clear();
  y.clear();
  ui->plot->setInteraction(QCP::iRangeZoom, true);
  ui->plot->setInteraction(QCP::iRangeDrag, true);
}
