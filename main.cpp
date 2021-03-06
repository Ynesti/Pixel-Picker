#include <QtWidgets>
 
QString     strRedColor;
QString     strGreenColor;
QString     strBlueColor;
QString     strRgbColor;
QString     strAlphaColor;
 
int alphaColor = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
QRgb pixelRgb;
 
QString     hexAlphaColor;
QString     hexRedColor;
QString     hexGreenColor;
QString     hexBlueColor;
QString     hexRgbColor;
 
int xMouse = 0;
int yMouse = 0;
 
class MainWindow : public QMainWindow {
   public:
       MainWindow ();
       void openButtonClick ();
       void openImage (const QString &path = QString());
       void mousePressEvent (QMouseEvent *event);
       void paintEvent (QPaintEvent *event);
   private:
       QLabel      *fileLabel;
       QPushButton *openButton;
       QPainter    *painter1;
       QPixmap     pixmap1;
       QLabel      *redLabel;
       QLabel      *greenLabel;
       QLabel      *blueLabel;
       QLabel      *rgbLabel;
       QImage      image1;
       QLabel      *xLabel;
       QLabel      *yLabel;
       QString     filePath;
       QLineEdit   *pathEdit;
       QLabel      *textLabel;
       QLabel      *helpLabel;
};
 
MainWindow::MainWindow() {
   setWindowTitle ("PixelPicker");
   setFixedSize (1000, 850);
   QString strLabelCSS = "display: block;"
                         "border-style: solid;"
                         "border-width: 1px;"
                         "border-color: black;"
                         "padding: 0;"
                         "margin: 0;";
   QFont labelFont ("Times", 12, QFont::Normal);
   fileLabel = new QLabel(this);
   fileLabel -> setGeometry (20, 500, 850, 30);
   fileLabel -> setFont(labelFont);
   fileLabel -> setText ("Open: ");
   fileLabel -> setStyleSheet (strLabelCSS);
 
   openButton = new QPushButton ("Open", this);
   openButton -> setGeometry (20, 530, 75, 30);
   openButton -> setFont (QFont("Times", 10, QFont::Normal));
 
   connect (openButton, &QPushButton::clicked, this, &MainWindow::openButtonClick);
 
   rgbLabel = new QLabel (this);
   rgbLabel -> setGeometry (20, 560, 850, 30);
   rgbLabel -> setFont (labelFont);
 
   redLabel = new QLabel (this);
   redLabel -> setGeometry (20, 590, 850, 30);
   redLabel -> setFont (labelFont);
 
   greenLabel = new QLabel (this);
   greenLabel -> setGeometry (20, 620, 850, 30);
   greenLabel -> setFont (labelFont);
 
   blueLabel = new QLabel (this);
   blueLabel -> setGeometry (20, 650, 850, 30);
   blueLabel -> setFont (labelFont);
 
   helpLabel = new QLabel (this);
   helpLabel -> setGeometry (20, 800, 850, 30);
   helpLabel -> setFont (QFont("Times", 8, QFont::Normal));
   helpLabel -> setText ("P.S: ???????????? ?????????????????????? ???????????? ???????? ???? ???????????? 600??400. ???????????? ??????????????????????: .jpg .png .bmp");
 
   xLabel = new QLabel (this);
   xLabel -> setGeometry (20, 690, 850, 30);
   xLabel -> setFont (labelFont);
   xLabel -> setText ("Mouse X: ");
 
   yLabel = new QLabel (this);
   yLabel -> setGeometry (20, 730, 850, 30);
   yLabel -> setFont (labelFont);
   yLabel -> setText ("Mouse Y: ");
   image1.load (filePath);
}
 
void MainWindow::openButtonClick() {
   openImage ();
   fileLabel -> setText ("Open: " + filePath);
   image1.load (filePath);
   update();
}
 
void MainWindow::openImage(const QString & path){
   filePath=path;
   if (filePath.isNull()){
       filePath=QFileDialog::getOpenFileName(this,"Open Image"," ","Image Files(*.png *.jpg *.bmp) ");
       }
   if (!filePath.isEmpty()){
       if (!pixmap1.load(filePath)){
           QMessageBox::warning(this,"Open Image","The img file could not be loaded.", QMessageBox::Cancel);
   return;
   }
}
   fileLabel -> setText(filePath);
}
 
void MainWindow::mousePressEvent (QMouseEvent *event) {
   QString strX;
   xMouse = event -> x();
   strX = QString ("%1").arg (xMouse, 3, 10, QChar('0'));
   xLabel -> setText ("Mouse X: " + strX);
 
   QString strY;
   yMouse = event -> y();
   strY = QString ("%1").arg (yMouse, 3, 10, QChar('0'));
   yLabel -> setText ("Mouse Y: " + strY);
 
   pixelRgb = image1.pixel (xMouse, yMouse);
   strRgbColor.setNum(pixelRgb);
   rgbLabel -> setText ("ARGB: " + strRgbColor);
 
   alphaColor = qAlpha (pixelRgb);
   strAlphaColor.setNum(alphaColor);
   hexAlphaColor = QString("%1").arg(alphaColor, 2, 16, QChar('0'));
   hexAlphaColor = hexAlphaColor.toUpper();
 
   redColor = qRed(pixelRgb);
   strRedColor = QString("%1").arg(redColor, 3, 10, QChar('0'));
   hexRedColor = QString("%1").arg(redColor, 2, 16, QChar('0'));
   hexRedColor = hexRedColor.toUpper();
   redLabel -> setText("R = " + strRedColor + " = 0x" + hexRedColor);
 
   greenColor = qGreen(pixelRgb);
   strGreenColor = QString("%1").arg(greenColor, 3, 10, QChar('0'));
   hexGreenColor = QString("%1").arg(greenColor, 2, 16, QChar('0'));
   hexGreenColor = hexGreenColor.toUpper();
   greenLabel -> setText("G = " + strGreenColor + " = 0x" + hexGreenColor);
 
   blueColor = qBlue(pixelRgb);
   strBlueColor = QString("%1").arg(blueColor, 3, 10, QChar('0'));
   hexBlueColor = QString("%1").arg(blueColor, 2, 16, QChar('0'));
   hexBlueColor = hexBlueColor.toUpper();
   blueLabel -> setText("B = " + strBlueColor + " = 0x" + hexBlueColor);
 
   QString hexRgbColor = hexAlphaColor + hexRedColor + hexGreenColor + hexBlueColor;
   rgbLabel -> setText ("ARGB: " + strRgbColor + " HEX: #" + hexRgbColor);
}
 
void MainWindow::paintEvent(QPaintEvent *) {
   QPainter painter1(this);
   pixmap1.load(filePath);
   painter1.drawPixmap (0, 0, pixmap1);
   painter1.restore();
}
 
int main (int argc, char *argv[]) {
   QApplication app (argc, argv);
   MainWindow mainWin;
   mainWin.show();
   return app.exec();
}

