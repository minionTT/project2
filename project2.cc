#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class node{
    public:
        node(){
            num = 0;
            step = 1073741824;
            up = NULL;
            down = NULL;
            left = NULL;
            right = NULL;
            back = NULL;
            fin = FALSE;
            in = FALSE;
            end = FALSE;
        }
        node(int in){
            num = in;
            step = 1073741824;
            up = NULL;
            down = NULL;
            left = NULL;
            right = NULL;
            back = NULL;
            fin = FALSE;
            in = FALSE;
            end = FALSE;      
        }
        int print_row(){
            return row;
        }
        int print_col(){
            return column;
        }
    private:
        int num;
        int step;
        node *up;
        node *down;
        node *left;
        node *right;
        node *back;
        bool fin;
        bool in;
        bool end;
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
    outfilename += "/final.path";
    fstream infile (infilename);
    ofstream outfile (outfilename);

    int row,column;
    int i,j;
    char typeIn;
    int bat;
    node* leftNode;
    node* newNode;
    node* rootNode;
    char leftTypeIn;
    bool end;
    int outCount;
    //int input[2][1001];
    int num=0;
    
    queue <node> myQueue;
    queue <element> secqueue;

    if(infile.is_open()){
        infile >> row >> column >> bat;
        store lastIn[column];

        for(i=0; i<row; i++){                                      //read in data
            for(j=0; j<column; j++){
                infile >> typeIn;
                if(typeIn == '0' || typeIn == 'R'){
                    newNode = new node(i*column + j);
                    lastIn[j].upNode = newNode;
                    if(leftTypeIn == '0' || leftTypeIn == 'R'){
                        leftNode->right = newNode;
                        newNode->left = leftNode;
                    }
                    leftNode = newNode;
                    if(typeIn == 'R'){
                        rootNode = newNode;
                    }
                    if(i == 0){
                        lastIn[j].upNode = newNode;
                        lastIn[j].type = typeIn;
                    }else{
                        if(lastIn[j].type == '0' || lastIn[j].type == 'R'){
                            lastIn[j].upNode->down = newNode;
                            newNode->up = lastIn[j].upNode;
                            
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
                leftTypeIn = typeIn;
            }
        }

        if(rootNode.up != NULL){
            myQueue.push(rootNode.up);
            rootNode.up->in = TRUE;
            rootNode.up->back = rootNode;
            rootNode.up->down = NULL;
            rootNode.up->step = 1;
        }else if(rootNode.down != NULL){
            myQueue.push(rootNode.down);
            rootNode.down->in = TRUE;
            rootNode.down->back = rootNode;
            rootNode.down->up = NULL;
            rootNode.down->step = 1;            
        }else if(rootNode.left != NULL){
            mwQueue.push(rootNode.left);
            rootNode.left->in = TRUE;
            rootNode.left->back = rootNode;
            rootNode.left->right = NULL;
            rootNode.left->step = 1; 
        }else if(rootNode.right != NULL){
            myQueue.push(rootNode.right);
            rootNode.right->in = TRUE;
            rootNode.right->back = rootNode;
            rootNode.right->left = NULL;
            rootNode.right->step = 1; 
        }
        rootNode.in = TRUE;
        rootNode.step = 0;

        while(!myQueue.isEmpty()){
            node currNode = myQueue.front();
            myQueue.pop();
            end = TRUE;
            if(currNode.up != NULL){
                if(currNode.up->in == FALSE){
                    myQueue.push(curuNode.up);
                    currNode.up->in = TRUE;
                    currNode.up->back = currNode;
                    currNode.up->down = NULL;
                    currNode.up->step = currNode.step + 1;
                    end = FALSE;
                }else{
                    currNode.up->down = NULL;
                    currNode.up = NULL;
                }   
            }
            if(currNode.down != NULL){
                if(currNode.down->in == FALSE){
                    myQueue.push(curuNode.down);
                    currNode.down->in = TRUE;
                    currNode.down->back = currNode;
                    currNode.down->up = NULL;
                    currNode.down->step = currNode.step + 1;
                    end = FALSE;
                }else{
                    currNode.down->up = NULL;
                    currNode.down = NULL;
                } 
            }
            if(currNode.left != NULL){
                if(currNode.left->in == FALSE){
                    myQueue.push(curuNode.left);
                    currNode.left->in = TRUE;
                    currNode.left->back = currNode;
                    currNode.left->right = NULL;
                    currNode.left->step = currNode.step + 1;
                    end = FALSE;
                }else{
                    currNode.left->right = NULL;
                    currNode.left = NULL;
                } 
            }
            if(currNode.right != NULL){
                if(currNode.right->in == FALSE){
                    myQueue.push(curuNode.right);
                    currNode.right->in = TRUE;
                    currNode.right->back = currNode;
                    currNode.right->left = NULL;
                    currNode.right->step = currNode.step + 1;
                    end = FALSE;
                }else{
                    currNode.right->left = NULL;
                    currNode.right = NULL;
                } 
            }
            if(end == TRUE){
                currNode.end = TRUE;
            }
        }

        if(outfile.is_open()){
            //outfile << num << endl;
            
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
