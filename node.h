#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Node
{
public:
    int positionX, positionY;
    T data;
    Node *next, *down;
    
    Node(){
        next = nullptr;
        down = nullptr;
    };
    Node(int _positionX,int _positionY) {
        positionX = _positionX;
        positionY=_positionY;
        next = nullptr;
        down = nullptr;
    }

    Node(int positionX,int positionY,T data, Node *next,Node *down)
    : positionX(positionX), positionY(positionY),data(data),next(nullptr),down(nullptr) {}
};

#endif //SPARSE_MATRIX_NODE_H
