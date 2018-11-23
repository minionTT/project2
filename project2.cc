#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class node{
    public:
        node(){
            num = 0;
            up = NULL;
            down = NULL;
            left = NULL;
            right = NULL;
            back = NULL;
            fin = FALSE;
            in = FALSE;
        }
        node(int in){
            num = in;
            up = NULL;
            down = NULL;
            left = NULL;
            right = NULL;
            back = NULL;
            fin = FALSE;
            in = FALSE;        
        }
        int print_row(){
            return row;
        }
        int print_col(){
            return column;
        }
    private:
        int num;
        node *up;
        node *down;
        node *left;
        node *right;
        node *back;
        bool fin;
        bool in;
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
    node* preNode;
    char leftTypeIn;
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
        }else if(rootNode.down != NULL){
            myQueue.push(rootNode.down);
        }else if(rootNode.left != NULL){
            mwQueue.push(rootNode.left);
        }else if(rootNode.right != NULL){
            myQueue.push(rootNode.right);
        }
        preNode = rootNode;
        rootNode.in = TRUE;

        while(!myQueue.isEmpty()){
            node currNode = myQueue.front();
            myQueue.pop();
            currNode.back = preNode;
            if(currNode.up != NULL){
                if(currNode.up->in == FALSE){
                    myQueue.push(curuNode.up);
                    currNode.up->in = TRUE;
                }else{
                    currNode.up->down = NULL;
                    currNode.up = NULL;
                }   
            }else if(currNode.down != NULL){
                if(currNode.down->in == FALSE){
                    myQueue.push(curuNode.down);
                    currNode.down->in = TRUE;
                }else{
                    currNode.down->up = NULL;
                    currNode.down = NULL;
                } 
            }else if(currNode.left != NULL){
                if(currNode.left->in == FALSE){
                    myQueue.push(curuNode.left);
                    currNode.left->in = TRUE;
                }else{
                    currNode.left->right = NULL;
                    currNode.left = NULL;
                } 
            }else if(currNode.right != NULL){
                if(currNode.right->in == FALSE){
                    myQueue.push(curuNode.right);
                    currNode.right->in = TRUE;
                }else{
                    currNode.right->left = NULL;
                    currNode.right = NULL;
                } 
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
