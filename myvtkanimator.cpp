#include "myvtkanimator.h"

myVtkAnimator::myVtkAnimator() {
    refAnimArray = vtkDoubleArray::New();
    varAnimArray = vtkDoubleArray::New();
    total_points = 0;
    processed_points = 0;
    processed_time = 0.0;
}

vtkDoubleArray * myVtkAnimator::getRefAnimArray(){
    return refAnimArray;
}


void myVtkAnimator::setMaxReadScalarValue(double maxVal){
    this->maxReadScalarValue = maxVal;
}

void myVtkAnimator::resetVarAnimArray(){
    if(this->total_points != 0){
        int i=0;
        this->varAnimArray->SetNumberOfValues(this->total_points);
        for(i=0;i<this->total_points;i++){
            varAnimArray->SetValue(i,this->maxReadScalarValue);

        }
    }
}
void myVtkAnimator::updateVarAnimArray(){
    int i;
    this->processed_points = 0;
    for(i=0;i<this->total_points;i++){
        if(refAnimArray->GetValue(i) < this->processed_time/1000.0){
            varAnimArray->SetValue(i,refAnimArray->GetValue(i));
            this->processed_points++;
        }

    }
}


vtkDoubleArray* myVtkAnimator::getVarAnimArray(){
    return this->varAnimArray;
}

void myVtkAnimator::setTotalPoints(int inTP){
    this->total_points = inTP;
}

int myVtkAnimator::getTotalPoints(){
    return this->total_points;
}
int myVtkAnimator::getProcessedPoints(){
    return this->processed_points;
}
double myVtkAnimator::getProcessedTime(){
    return this->processed_time;
}

void myVtkAnimator::increaseProcessedTime(){
    this->processed_time += this->processing_time;
}

void myVtkAnimator::reset(){
    this->resetVarAnimArray();
    this->processed_time = 0.0;
    this->processed_points = 0;
}

void myVtkAnimator::setProcessingTime(int time){
    this->processing_time = time;
}
