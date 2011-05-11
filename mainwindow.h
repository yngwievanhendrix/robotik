#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "vtkEventQtSlotConnect.h"
#include "vtkCommand.h"
#include "vtkRenderWindow.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPointData.h"
#include "myvtkanimator.h"
#include "myvtkreader.h"

#define TIMER_TIME 100

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    vtkRenderWindow *renWin;
    vtkUnstructuredGrid *myGeometry;
    vtkPoints *points;
    vtkLookupTable *lut;

    int qTimerTime;
    QTimer timer;

    myVtkReader myReader;
    myVtkAnimator myAnimator;

public slots:
    void onClickedMessageFromMyVtkInteractor(void);
    void onClickedAnimateButton(void);
    void onClickedResetButton(void);
    void onTimerTimeOut(void);
protected:
    //vtkEventQtSlotConnect* vtkQtConnection;

private slots:
    void on_pushButton_clicked();
    void on_timeSlider_sliderMoved(int position);
};

#endif // MAINWINDOW_H
