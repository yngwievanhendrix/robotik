#include "mainwindow.h"
#include "myvtkreader.h"
//#include "myvtkinteractor.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include "stdio.h"
#include "vtkUnstructuredGrid.h"
#include "vtkPoints.h"
#include "vtkTetra.h"
#include "vtkDataSetMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkPointData.h"
#include "vtkLookupTable.h"
#include "vtkCellData.h"
#include "vtkCellArray.h"
#include "vtkIdList.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"


#include "myvtkanimator.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow) {
    //QObject::connect(pCam,SIGNAL(gotFrame(QImage)),this,SLOT(on_gotFrame_fromCam(QImage)));


    QString tString;
    ui->setupUi(this);
    //setup time
    this->qTimerTime = 100;

    //Declare RenderWindow
    renWin = vtkRenderWindow::New();
    //initiate myVtkReader
    myReader = myVtkReader();
    //Declare myGeomety
    myGeometry = vtkUnstructuredGrid::New();
    //Declare points
    points = vtkPoints::New();
    myAnimator = myVtkAnimator();

    //Read the Mesh from a file that in the Class specified
    myReader.readMesh(myGeometry,points);

    //Declare an Array where to store the Scalar read from a file
    //vtkDoubleArray *myArray = vtkDoubleArray::New();
    //Read the Scalars from a file
    myReader.readScalars(myAnimator.getRefAnimArray());
    myAnimator.setMaxReadScalarValue(myReader.getMaxReadScalarValue());
    myAnimator.setTotalPoints(myReader.getTotalPoints());
    // das soll Protected sein wird irgendwann intern ausgeführt
    myAnimator.reset();


    //Output the max. read Scalar value
    tString.setNum(myReader.getMaxReadScalarValue());
    ui->textEdit->append(tString);
    //assign read Scalars to myGeometry
    myGeometry->GetPointData()->SetScalars(myAnimator.getVarAnimArray());

    //myGeometry->GetPointData()->GetScalars()->SetLookupTable();
    // LookUpTable
    lut = vtkLookupTable::New();
    lut->SetNumberOfTableValues((int)myReader.getMaxReadScalarValue());
    lut->Build();




    /* Displaying the result */

    vtkDataSetMapper *mapper = vtkDataSetMapper::New();
    mapper->SetInputConnection(myGeometry->GetProducerPort());
    mapper->SetScalarRange(0,(int)myReader.getMaxReadScalarValue());
    mapper->SetLookupTable(lut);



    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);

    vtkRenderer *renderer = vtkRenderer::New();
    renderer->AddActor(actor);

    this->ui->qvtkWidget->SetRenderWindow(renWin);
    this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);


    /*Ende Testen*/
    vtkEventQtSlotConnect *myConnection = vtkEventQtSlotConnect::New();
    myConnection->Connect(ui->qvtkWidget->GetRenderWindow()->GetInteractor(),
                          vtkCommand::LeftButtonPressEvent,
                          this,
                          SLOT(onClickedMessageFromMyVtkInteractor()));
    QObject::connect(this->ui->animButton,SIGNAL(clicked()),this,SLOT(onClickedAnimateButton()));
    QObject::connect(&timer,SIGNAL(timeout()),this,SLOT(onTimerTimeOut()));
    QObject::connect(this->ui->resetButton,SIGNAL(clicked()),this,SLOT(onClickedResetButton()));

    int TSPos = this->ui->timeSlider->sliderPosition();
    tString.setNum(TSPos);
    this->ui->textEdit->setText(tString);

    //this->ui->pushButton->;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onClickedAnimateButton(){

    //int pos = this->ui->timeSlider->pos().x;
    //int pos = this->ui->timeSlider->cursor().pos().x();

    QString tString;
    int pos = this->ui->timeSlider->sliderPosition();
    tString.setNum(pos*this->qTimerTime);

    this->ui->textEdit->setText(tString);
    myAnimator.setProcessingTime(pos*this->qTimerTime);
    this->timer.start(qTimerTime);
}

void MainWindow::onClickedMessageFromMyVtkInteractor(){
    this->ui->textEdit->append("Clicked");
}
void MainWindow::onTimerTimeOut(){

    QString tString1;
    QString tString2;
    tString1.setNum(this->myAnimator.getProcessedPoints());
    tString1.append(";");
    tString2.setNum(this->myAnimator.getTotalPoints());
    tString1.append(tString2);
    this->ui->textEdit_2->append(tString1);

    if(this->myAnimator.getProcessedPoints() < this->myAnimator.getTotalPoints()){
        this->myAnimator.increaseProcessedTime();
        this->myAnimator.updateVarAnimArray();
        myGeometry->GetPointData()->SetScalars(myAnimator.getVarAnimArray());
        myGeometry->Modified();
        this->ui->qvtkWidget->GetRenderWindow()->Render();



        tString1.setNum(this->myAnimator.getProcessedTime()/1000.0);
        tString1.append("-time");
        this->ui->textEdit->setText(tString1);
        timer.start(qTimerTime);
    }
    else{
        timer.stop();

    }
}

void MainWindow::onClickedResetButton(){
    myAnimator.reset();
    myGeometry->GetPointData()->SetScalars(myAnimator.getVarAnimArray());
    myGeometry->Modified();
    this->ui->qvtkWidget->GetRenderWindow()->Render();
}

void MainWindow::on_timeSlider_sliderMoved(int position)
{
    QString tString;
    tString.setNum(position*this->qTimerTime);
    myAnimator.setProcessingTime(position*this->qTimerTime);
    //this->ui->textEdit->setText(tString);
}

void MainWindow::on_pushButton_clicked()
{

    int numCell = this->myGeometry->GetNumberOfCells();

    this->myGeometry->GetPoints();

    vtkCell *aCell = this->myGeometry->GetCell((int)(numCell/2));

    //getting point from Cells
    vtkPoints *tPoints = aCell->GetPoints();
    vtkDataArray *tArray = tPoints->GetData();
    //getting faces from Cells
    int numFaces = aCell->GetNumberOfFaces();

    vtkCell *face = aCell->GetFace(2);
    vtkIdList *list = face->GetPointIds();
    int numIds = list->GetNumberOfIds();
    QString tString;
    QString endString;

    tString.setNum(numIds);
    endString = "numFaces:";
    endString.append(tString);
    endString.append(" ");
    tString.setNum(list->GetId(0));
    endString.append(tString);
    endString.append(" ");

    tString.setNum(list->GetId(1));
    endString.append(tString);
    endString.append(" ");

    tString.setNum(list->GetId(2));
    endString.append(tString);
    endString.append(" ");


    //tString.setNum(numFaces);
    this->ui->textEdit->setText(endString);
}
