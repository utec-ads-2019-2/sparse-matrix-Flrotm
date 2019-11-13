#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
#include <vector>
#include <iostream>


using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *x;
    Node<T> *y;
    int rows, columns;

public:
    Matrix(unsigned int rows, unsigned int columns);
    void set(int setx, int sety, T data);
    T operator()(unsigned int x, unsigned int y) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;
    void print() const;

    ~Matrix();


};
template<typename T>
Matrix<T>::Matrix(unsigned int _rows, unsigned int _columns) {
    rows = _rows;
    columns = _columns;
    x = new Node<T>();
    y = new Node<T>();
    x->down = new Node<T>(0,0);

    Node<T> *temp = x->down;

    for (int i = 1; i < _rows; ++i){
        temp->down = new Node<T>(i,0);
        temp = temp->down;
    }

    y->next = new Node<T>(0,0);
    temp = y->next;

    for (int i = 1; i < _columns; ++i){
        temp->next = new Node<T>(i,0);
        temp = temp->next;
    }

}
template<typename T>


void Matrix<T>::set(int setx, int sety, T data) {
    if(setx>rows or sety>columns){
     throw out_of_range("Fuera del rango");
    }

        auto *fila = this->x;
        auto *columna = this->y;

            for (int i = 0; i < setx; ++i) {
                fila=fila->down;
            }
            for (int i = 0; i < sety; ++i) {
                columna = columna->next;
            }
            if(fila->next!= nullptr){
            while (fila->next->positionX <setx){
                fila=fila->next;
            }}
            if(columna->down != nullptr){
            while (columna->down->positionY <sety){
                columna=columna->down;
            }
        }
    auto Set = new Node<T>(setx,sety, data,fila->next,columna->down);
    fila->next=Set;
    columna->down=Set;
    }


template<typename T>
T Matrix<T>::operator()(unsigned int X,unsigned int Y) const {

   auto *temp=this->y;
    for (int i =0; i <Y ; ++i) {
    temp=temp->next;
    }
if(temp->down!= nullptr){
    while(temp->down!=nullptr ){
        if (temp->down->positionX==X){
            return temp->down->data;
        }
        temp = temp->down;
    }
} else return 0;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {


    auto mult= new Matrix<T>(rows,columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <columns ; ++j) {
            mult->set(i, j, (((*this)(i, j) * scalar)));
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> other) const {
    return Matrix<T>(0, 0);
}

template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> other) const {
   if(columns!=other.columns or rows!=other.rows){
       throw out_of_range("Matrices con diferente numero de columnas o filas");
    }
    auto suma= new Matrix<T>(rows,columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <columns ; ++j) {
            suma->set(i,j,(((*this)(i, j)+other(i,j))));
        }
    }

}

template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> other) const {

    if(columns!=other.columns or rows!=other.rows){
        throw out_of_range("Matrices con diferente numero de columnas o filas");
    }
    auto resta= new Matrix<T>(rows,columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <columns ; ++j) {
            resta->set(i,j,(((*this)(i, j)-other(i,j))));
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {

    auto traspuesta= new Matrix<T>(rows,columns);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <columns ; ++j) {
            traspuesta->set(i,j,(((*this)(j,i))));
        }

    }
}

template<typename T>
void Matrix<T>::print() const {

    for (int i= 1; i < rows; ++i){
        for (int j=1;j<columns;++j){
            cout<<(*this)(i, j)<<"\t";
        }
        cout << endl;
    }
}



template<typename T>
Matrix<T>::~Matrix() {

}



#endif //SPARSE_MATRIX_MATRIX_H
