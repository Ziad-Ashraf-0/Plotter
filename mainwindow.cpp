#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {ui->setupUi(this);

  //Chart render
  chartView->setRenderHint(QPainter::Antialiasing);
  ui->horizontalLayout->addWidget(chartView);

  // Define a RegularExpression to validate the input equation terms, every term must be on
  // this form (sign magnitude*X^power) except the first term can defined
  // without a sign e.g. 3*X^2 + 5*X
  QRegularExpression rx("([+-]?[ ]?([0-9]+\\*)?[xX](\\^[0-9]+)?)[ ]?([+-][ " "]?([0-9]+\\*)?[xX](\\^[0-9]+)?)+[ ]?");

  QValidator *equationValidaor = new QRegularExpressionValidator(rx, 0);
  ui->equLine->setValidator(equationValidaor); // Assign the RegularExpression equation validator to the equation
                         

  connect(ui->equLine, SIGNAL(inputRejected()), this, SLOT(invalidEquation()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_plotButton_clicked() {
  
  QString equation = ui->equLine->text();
  float min_x = ui->minBox->value(), max_x = ui->maxBox->value();

  
  if (min_x >= max_x) {
    QMessageBox msg;
    msg.information(0, "Function Plotter",
                    "Invalid Input.\nThe minimum value of x must be less than "
                    "or equal the maximum value of x.");
    return;
  }

  
  FunctionEvaluator equ;
  equ.setEquation(equation);
  equ.setMinX(min_x);
  equ.setMaxX(max_x);

  series->append(
      equ.evaluatEquation()); 

  chart->legend()->hide(); 
  chart->addSeries(series); 
  chart->createDefaultAxes();
  chart->setTitle("Y = " + equation); 
}


void MainWindow::on_plotButton_released() {
  chart->removeSeries(series);
  series->clear();
}


void MainWindow::invalidEquation() {
  QMessageBox msg;
  msg.information(0, "Function Plotter",
                  "Invalid Equation.\nAny function's term should be "
                  "constructed as following\n"
                  "(sign  magnitude * x or X ^ power value).\nex: -2*X^4");
  return;
}
