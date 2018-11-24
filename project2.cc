#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class node{
    public:
        node(){
            num = 0;
            step = 1073741824;
            rmn = 1073741824;
            up = NULL;
            down = NULL;
            left = NULL;
            right = NULL;
            back = NULL;
            Fin = false;
            in = false;
            upFin = true;
            downFin = true;
            leftFin = true;
            rightFin = true; 
        }
        node(int in){
            num = in;
            step = 1073741824;
            rmn = 1073741824;
            up = NULL;
            down = NULL;
            left = NULL;
            right = NULL;
            back = NULL;
            Fin = false;
            in = false;
            upFin = true;
            downFin = true;
            leftFin = true;
            rightFin = true;     
        }
        int num;
        int step;
        int rmn;
        node *up;
        node *down;
        node *left;
        node *right;
        node *back;
        bool Fin;
        bool in;
        bool upFin;
        bool downFin;
        bool leftFin;
        bool rightFin;
};
class store{
    public:
        store(){
            upNode = NULL;
            type = '1';
        }
    public:
        node* upNode;
        char type;
};

int main(int argc, char* argv[]){

    string infilename = "./";
    string outfilename = "./";
    infilename += argv[1];
    outfilename += argv[1];
    infilename += "/floor.data";
    outfilename += "/Final.path";
    fstream infile (infilename);
    ofstream outfile (outfilename);

    int row,column;
    int i,j;
    char typeIn;
    int bat;
    node* leftNode;
    node* newNode;
    node* rootNode;
    node* outNode;
    node* currNode;
    char leftTypeIn;
    bool end;
    int direc;
    //int input[2][1001];
    int num=0;
    
    queue <node*> myQueue;
    queue <int> secQueue;
    stack <int> dir;

    if(infile.is_open()){
        infile >> row >> column >> bat;
        store lastIn[column];

        for(i=0; i<row; i++){                                      //read in data
            for(j=0; j<column; j++){
                infile >> typeIn;
                //cout << typeIn << endl;
                if(typeIn == '0' || typeIn == 'R'){
                    newNode = new node(i*column + j);
                    if(leftTypeIn == '0' || leftTypeIn == 'R'){
                        leftNode->right = newNode;
                        leftNode->rightFin = false;
                        newNode->left = leftNode;
                        newNode->leftFin = false;
                        cout << "left " << leftNode->num << " new " << newNode->num << endl;
                    }
                    leftNode = newNode;
                    leftTypeIn = typeIn;
                    if(typeIn == 'R'){
                        rootNode = newNode;
                    }
                    if(i == 0){
                        lastIn[j].upNode = newNode;
                        lastIn[j].type = typeIn;
                    }else{
                        if(lastIn[j].type == '0' || lastIn[j].type == 'R'){
                            lastIn[j].upNode->down = newNode;
                            lastIn[j].upNode->downFin = false;
                            newNode->up = lastIn[j].upNode;
                            newNode->upFin = false;
                            //if(typeIn == 'R'){
                            //    cout << lastIn[j].upNode->num << endl;
                            //}
                            
                            lastIn[j].upNode = newNode;
                            lastIn[j].type = typeIn;
                        }else{
                            lastIn[j].upNode = newNode;
                            lastIn[j].type = typeIn;
                        }
                    }
                }else if(typeIn == '1'){
                    lastIn[j].upNode = NULL;
                    lastIn[j].type = typeIn;
                }
            }
        }
        cout << "root = " << rootNode->num << endl;
        if(rootNode->up != NULL){
            outNode = rootNode->up;
            myQueue.push(rootNode->up);
            cout << rootNode->up->num << endl;
            rootNode->up->in = true;
            rootNode->up->back = rootNode;
            rootNode->up->down = NULL;
            rootNode->up->step = 1;
        }else if(rootNode->down != NULL){
            outNode = rootNode->down;
            myQueue.push(rootNode->down);
            rootNode->down->in = true;
            rootNode->down->back = rootNode;
            rootNode->down->up = NULL;
            rootNode->down->step = 1;            
        }else if(rootNode->left != NULL){
            outNode = rootNode->left;
            myQueue.push(rootNode->left);
            rootNode->left->in = true;
            rootNode->left->back = rootNode;
            rootNode->left->right = NULL;
            rootNode->left->step = 1; 
        }else if(rootNode->right != NULL){
            outNode = rootNode->right;
            myQueue.push(rootNode->right);
            rootNode->right->in = true;
            rootNode->right->back = rootNode;
            rootNode->right->left = NULL;
            rootNode->right->step = 1; 
        }
        rootNode->in = true;
        rootNode->step = 0;

        while(!myQueue.empty()){
            currNode = myQueue.front();
            myQueue.pop();
            end = true;
            if(currNode->up != NULL){
                if(currNode->up->in == false){
                    myQueue.push(currNode->up);
                    currNode->up->in = true;
                    currNode->up->back = currNode;
                    currNode->up->down = NULL;
                    currNode->up->downFin = true;
                    currNode->up->step = currNode->step + 1;
                    end = false;
                }else{
                    currNode->up->down = NULL;
                    currNode->up->downFin = true;
                    currNode->up = NULL;
                    currNode->upFin = true;
                }   
            }
            if(currNode->down != NULL){
                if(currNode->down->in == false){
                    myQueue.push(currNode->down);
                    currNode->down->in = true;
                    currNode->down->back = currNode;
                    currNode->down->up = NULL;
                    currNode->down->upFin = true;
                    currNode->down->step = currNode->step + 1;
                    end = false;
                }else{
                    currNode->down->up = NULL;
                    currNode->down->upFin = true;
                    currNode->down = NULL;
                    currNode->downFin = true;
                } 
            }
            if(currNode->left != NULL){
                if(currNode->left->in == false){
                    myQueue.push(currNode->left);
                    currNode->left->in = true;
                    currNode->left->back = currNode;
                    currNode->left->right = NULL;
                    currNode->left->rightFin = true;
                    currNode->left->step = currNode->step + 1;
                    end = false;
                }else{
                    currNode->left->right = NULL;
                    currNode->left->rightFin = true;
                    currNode->left = NULL;
                    currNode->leftFin = true;
                } 
            }
            if(currNode->right != NULL){
                if(currNode->right->in == false){
                    myQueue.push(currNode->right);
                    currNode->right->in = true;
                    currNode->right->back = currNode;
                    currNode->right->left = NULL;
                    currNode->right->leftFin = true;
                    currNode->right->step = currNode->step + 1;
                    end = false;
                }else{
                    currNode->right->left = NULL;
                    currNode->right->leftFin = true;
                    currNode->right = NULL;
                    currNode->rightFin = true;
                } 
            }
            if(end == true){
                currNode->Fin = true;
                currNode->rmn = 0;
                currNode->upFin = true;
                currNode->downFin = true;
                currNode->leftFin = true;
                currNode->rightFin = true; 
            }
        }

        while(outNode->Fin != true){
            currNode = outNode;
            secQueue.push(currNode->num);
            num++;
            while(currNode->Fin != true){
                if(currNode->upFin != true){
                    currNode = currNode->up;
                    secQueue.push(currNode->num);
                    dir.push(1);
                    num++;
                }else if(currNode->downFin != true){
                    currNode = currNode->down;
                    secQueue.push(currNode->num);
                    dir.push(2);
                    num++;
                }else if(currNode->leftFin != true){
                    currNode = currNode->left;
                    secQueue.push(currNode->num);
                    dir.push(3);
                    num++;
                }else if(currNode->rightFin != true){
                    currNode = currNode->left;
                    secQueue.push(currNode->num);
                    dir.push(4);
                    num++;
                }
            }
            currNode = currNode->back;
            secQueue.push(currNode->num);
            num++;
            while(currNode != rootNode){
                direc = dir.top();
                dir.pop();
                if(direc == 1){
                    if(currNode->up->Fin == true){
                        currNode->upFin = true;
                    }
                    currNode->Fin = currNode->upFin & currNode->downFin & currNode->leftFin & currNode->rightFin;
                    currNode = currNode->back;
                    secQueue.push(currNode->num);
                    num++;
                }else if(direc == 2){
                    if(currNode->down->Fin == true){
                        currNode->downFin = true;
                    }
                    currNode->Fin = currNode->upFin & currNode->downFin & currNode->leftFin & currNode->rightFin;
                    currNode = currNode->back;
                    secQueue.push(currNode->num);
                    num++;
                }else if(direc == 3){
                    if(currNode->left->Fin == true){
                        currNode->leftFin = true;
                    }
                    currNode->Fin = currNode->upFin & currNode->downFin & currNode->leftFin & currNode->rightFin;
                    currNode = currNode->back;
                    secQueue.push(currNode->num);
                    num++;
                }else if(direc == 4){
                    if(currNode->right->Fin == true){
                        currNode->rightFin = true;
                    }
                    currNode->Fin = currNode->upFin & currNode->downFin & currNode->leftFin & currNode->rightFin;
                    currNode = currNode->back;
                    secQueue.push(currNode->num);
                    num++;
                }
            }
        }

        if(outfile.is_open()){
            outfile << num << endl;
            int pri;
            while(!secQueue.empty()){
                pri = secQueue.front();
                secQueue.pop();
                outfile << pri/column << " " << pri%column << endl;
            }
    
            outfile.close();
        }else{
            cout << "Unable to open file_out" << endl;
        }

        infile.close();
    }else{
        cout << "Unable to open file_in" << endl;
    }

    return 0;
}
