/*Jie Ling Zhao 
 CS323-33 Project 4
 Heap Sort
 C++
 Feb22-2016
 */

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

ifstream inputfile;
ofstream output1;
ofstream output2;


class HeapSort{
public:
    
    int maxsize;
    int front = 1;
    int * heapAry;
    int indexCounter;
 
    //constructor
    HeapSort(int counter){
        maxsize = counter;
        heapAry = new int[counter];
        indexCounter=0;
    }
    //Destructor
    ~HeapSort(){
        delete[] heapAry;
        output1<<"HeapArray is now deleted by Destructor \n"<<endl;
    }
   
    void insertOneDataItem(int newbubble){
        
        if(!isHeapFull()){
        heapAry[++indexCounter]=newbubble;
        bubbleUp();
        heapAry[0]=indexCounter;
            //output1<< printf("\nInsert: %3d ***",newbubble);
            output1<< "Inserting-> " << setw(3) << newbubble <<":"<< setfill(' ') <<"\t";
            printHeap();
            output1<<endl;
        return;
        }
    }
    
    void buildHeap(ifstream& myfile, ofstream& output){
        int infile;
        while (myfile>>infile){
            insertOneDataItem(infile);
        }
        output1<<"\nHEAP COMPLETE: "<<endl;
        printHeap();
        
    }
    
    void bubbleUp(){

                int childIndex  = indexCounter;
                int parentIndex = childIndex/2;
                int temp;
        
                while (childIndex != 1 && heapAry[parentIndex] > heapAry[childIndex]) {
                    //swap child and parent
                    temp = heapAry[childIndex];
                    heapAry[childIndex]  = heapAry[parentIndex];
                    heapAry[parentIndex] = temp;
        
                    //move parent and child index along the array
                    childIndex  = parentIndex;
                    parentIndex = childIndex/2;
                }//while
    }//bubble up
    
    
    void bubbleDown() {
        int lowestIndex, temp;
        int parentIndex= 1;
        int leftChild=2;
        int rightChild=3;
        
        while (leftChild <=indexCounter || rightChild <= indexCounter) {
            if (rightChild > indexCounter) {
                if (leftChild > indexCounter) {
                    return;
                }
                else lowestIndex = leftChild;
            }
            else if (heapAry[leftChild] < heapAry[rightChild])
                lowestIndex = leftChild;
            else
                lowestIndex = rightChild;
            if (heapAry[parentIndex] > heapAry[lowestIndex]) {
                temp = heapAry[lowestIndex];
                heapAry[lowestIndex]    = heapAry[parentIndex];
                heapAry[parentIndex] = temp;
                parentIndex = lowestIndex;
                leftChild  = 2*parentIndex;
                rightChild = 2*parentIndex+1;
            }
            else 
                return;
        }
    }
    
    void deleteHeap(){
        output2<<"\nHEAPSORT "<<endl;
        output2<<"This is the sorted outcome: "<<endl;
        
        cout<<"DeleteHeap is being Called\n "<<endl;
        while (!isHeapEmpty()) {
            deleteRoot();
        }//while
        output1<<"Heap is now Empty! "<<endl;
    }
    
    
    
    //remove if else statements for FULL HEAP
    void printHeap(){

         if(indexCounter<=10){
             //within the 10 times
             for (int i=1; i<=indexCounter;i++) {
                 //output1<<heapAry[i]<<" ";
                 output1<< setw(3) << setfill(' ') << heapAry[i] <<" ";
                }
             
         }
         else{
             //after 10th time, just print 10 numbers for each line
             for(int i = 1; i<=10; i++){
                 //output1<<heapAry[i]<<" ";
                 output1<< setw(3) << setfill(' ') << heapAry[i] <<" ";
             }
             
         }//else
    
    }
    
    bool isHeapEmpty(){
        if(indexCounter==0){
            return true;
        }
        return false;
    }//isHeapEmpty
    
    
    bool isHeapFull(){
        if(indexCounter>=maxsize){
            return true;
        }
        return false;
        
    }//isHeapFull

    
    
    void deleteRoot(){
      
        
        if (!isHeapEmpty()){
            int root = heapAry[front];
            heapAry[front] = heapAry[indexCounter];
            indexCounter--;
            output1<<"\n\nDeleting the root:  < "<<root << " > \n";
            bubbleDown();
            output1<<"\nUpdated Heap "<<endl;
            printHeap();
            
            output2<<"Deleted: "<<root<<endl;
            
        }//if
        
        return;
    
    }//deleteRoot
    


};//STACK CLASS




int main(int argc, char* argv[]){
    int counter = 0;
    int in;
    
    inputfile.open(argv[1]);
    output1.open(argv[2]);
    output2.open(argv[3]);

    if(argc <4){
        cout<< "No enough file argument found!" <<endl;
        exit(1);
    }

    while(inputfile >> in){
        counter++;
    }
    
    //ArraySize Allocation
    HeapSort myHeap(counter);
    inputfile.close();
    //REOPEN
    inputfile.open(argv[1]);
    
    cout<<"Index Counter is "<<counter<<endl;
    output1<<"OUTPUT FILE 1 "<<endl<<endl;
    output2<<"OUTPUT FILE 2 "<<endl;
    myHeap.buildHeap(inputfile, output1);

    myHeap.deleteHeap();
    
    inputfile.close();
    output1.close();
    output2.close();
    
    
    

}//main
