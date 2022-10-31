MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(900,600);
    QLabel *lab=new QLabel(QStringLiteral("线型 "),this);
    QComboBox *cmb=new QComboBox(lab);
    cmb->addItem(QStringLiteral("直线"));
    cmb->addItem(QStringLiteral("曲线"));
    cmb->addItem(QStringLiteral("矩形"));
    cmb->addItem(QStringLiteral("椭圆"));


    ui->toolBar->addWidget(lab);
    ui->toolBar->addWidget(cmb);
    QLabel *lab1=new QLabel(QStringLiteral(" 线宽 "),this);
    QSpinBox *sb=new QSpinBox(lab1);
    ui->toolBar->addWidget(lab1);
    ui->toolBar->addWidget(sb);

    ui->toolBar->addSeparator();
    QPushButton *color=new QPushButton(QStringLiteral("调色板"));
    ui->toolBar->addWidget(color);
   // ui->toolBar->addAction(QStringLiteral("直线"));
    ui->toolBar->addSeparator();
    QPushButton *clear=new QPushButton(QStringLiteral("清空"));
    ui->toolBar->addWidget(clear);

    drawboard *d=new drawboard;
    this->setCentralWidget(d);

    connect(cmb,&QComboBox::currentTextChanged,[=](QString text){
        d->style=text;
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}

