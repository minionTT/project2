#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class element{
    public:
        element(){
            row = 0;
            column = 0;
        }
        element(int in1, int in2){
            row = in1;
            column = in2;
        }
        int print_row(){
            return row;
        }
        int print_col(){
            return column;
        }
    private:
        int row;
        int column;
};
class store{
    public:
        store(){
            val = 0;
            peak = 1;
        }
    public:
        int val;
        bool peak;
};

int main(int argc, char* argv[]){

    string infilename = "./";
    string outfilename = "./";
    infilename += argv[1];
    outfilename += argv[1];
    infilename += "/matrix.data";
    outfilename += "/final.peak";
    fstream infile (infilename);
    ofstream outfile (outfilename);

    int row,column;
    int i,j;
    int tmpin;
    //int input[2][1001];
    int num=0;
    
    queue <element> myqueue;
    queue <element> secqueue;

    if(infile.is_open()){
        infile >> row >> column;
        store input[column+1];

        for(i=1; i<=row; i++){
            for(j=1; j<=column; j++){
                infile >> tmpin;
                if(i==1){
                    input[j].peak = 1;

                    
                }else{
                    if(input[j].val >= tmpin){
                        if(input[j].peak == 1 ) {
                            element* in = (element*) new element(i-1,j);
                            myqueue.push( *in);
                            num++;
                        
                        }
                        
                    }
                    if(input[j].val > tmpin){
                        input[j].peak = 0;
                    }else{
                        input[j].peak = 1;
                    }
                }
                input[j].val = tmpin;
                if(j>1){
                    if(input[j-1].val > tmpin){
                        input[j].peak = 0;
                        if(i == row){
                            if(input[j-1].peak == 1){
                                element* in = (element*) new element(i,j-1);
                                secqueue.push( *in);
                                num++;
                            }
                        }
                    }else if(input[j-1].val < tmpin) {
                        input[j-1].peak = 0;
                    }else{
                        if(i == row){
                            if(input[j-1].peak == 1){
                                element* in = (element*) new element(i,j-1);
                                secqueue.push( *in);
                                num++;
                            }
                        }
                    }
                }
                
            }
        }

        if(input[j-1].peak == 1){
            element* in = (element*) new element(i-1,j-1);
            secqueue.push( *in);
            num++;
        }

        if(outfile.is_open()){
            outfile << num << endl;
            while(!myqueue.empty()){
                element out = myqueue.front();
                outfile << out.print_row() << " " << out.print_col() << endl;
                myqueue.pop();
            }
            while(!secqueue.empty()){
                element out = secqueue.front();
                outfile << out.print_row() << " " << out.print_col() << endl;
                secqueue.pop();
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
