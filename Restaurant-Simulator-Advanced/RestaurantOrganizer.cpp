/*
Student Name: Zehranaz Canfes
Student Number: 2017205138
Project Number: 2
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "RestaurantOrganizer.h"

using namespace std;

RestaurantOrganizer::RestaurantOrganizer(const vector<int>& tableCapacityInput){
    numberOfTables = tableCapacityInput.size();
    for(int i=0;i<numberOfTables;i++){
        tableCapacity[i] = tableCapacityInput[i];
        heap[i] = i;
        heapUp(i);
    }
}

void RestaurantOrganizer::addNewGroup(int groupSize, ofstream& outFile){
    int groupTable;
    if(tableCapacity[heap[0]] < groupSize){
        //maximum capacity is at top, so if the groupSize is larger than that value, that group cannot be seated.
        outFile << -1 << '\n';
        return;
    }
    groupTable = heap[0];//else, the groupSize is smaller than the maximum capacity and therefore the group can be seated.
    if(groupSize != 0) {
        tableCapacity[heap[0]] -= groupSize;//after the group is assigned to a table, the capacity must be decreased.
        heapDown(0);//to find the suitable place for the table in the heap
    }
    outFile << groupTable << "\n";
}

int get_right(int index, int size){//returns the right child in the heap.
    if(index * 2 + 2 < size)
        return index * 2 + 2;
    return -1;
}

int get_left(int index, int size){//returns the left child in the heap.
    if(index * 2 + 1 < size)
        return index * 2 + 1;
    return -1;
}

void RestaurantOrganizer::heapUp(int index){//the heap is constructed starting from the index to top.
    if(index == 0)
        return;
    int index_parent = (index - 1) / 2;
    if(index > 0 && tableCapacity[heap[index]] > tableCapacity[heap[index_parent]]){
        //if the index value is larger than its parent in the heap, they should be swapped.
        swap(heap[index], heap[index_parent]);
        heapUp(index_parent);//recursively continues to check the heap.
    }
}

void RestaurantOrganizer::heapDown(int index){
    //after the capacity of a table is decreased it must be relocated in the heap.
    if(index == numberOfTables)//if the heap is full, do nothing.
        return;
    int largestCapacity = index;
    int index_right = get_right(index, numberOfTables);
    int index_left = get_left(index, numberOfTables);

    if(index_right == -1 && index_left == -1)//if the index is a leaf, no need for heapDown.
        return;
    if(index_left != -1 && tableCapacity[heap[index_left]] > tableCapacity[heap[largestCapacity]])//finds the maximum capacity.
        largestCapacity = index_left;
    if(index_right != -1 && tableCapacity[heap[index_right]] > tableCapacity[heap[largestCapacity]])
        largestCapacity = index_right;
    if(largestCapacity == index) {//if the table capacity is in the right place check the table numbers.
        int min_index = index;
        if(index_left != -1 && tableCapacity[heap[index]] == tableCapacity[heap[index_left]]){
            if(heap[index_left] < heap[index])//find the minimum table number
                min_index = index_left;
        }
        if(index_right != -1 && tableCapacity[heap[index]] == tableCapacity[heap[index_right]]){
            if(heap[index_right] < heap[min_index])
                min_index = index_right;
        }
        if(min_index != index) {
            swap(heap[index], heap[min_index]);//swap with the minimum table number
            heapDown(min_index);
        }
    }
    else {//if the root is not the maximum
        if(index_left != -1 && index_right != -1 && tableCapacity[heap[index_right]] == tableCapacity[heap[index_left]]) {
            if (heap[index_right] > heap[index_left]) {//chooses the minimum table number
                swap(heap[index_left], heap[index]);
                heapDown(index_left);
            } else {
                swap(heap[index_right], heap[index]);
                heapDown(index_right);
            }
        }
        else {
            swap(heap[largestCapacity], heap[index]);
            heapDown(largestCapacity);
        }
    }
}

void RestaurantOrganizer::printSorted(ofstream& outFile){//Heap Sort
    int n = numberOfTables;
    while(numberOfTables > 0){
        outFile << tableCapacity[heap[0]] << " ";//takes the maximum element from the heap
        heap[0] = heap[numberOfTables - 1];
        heapDown(0);//recreate the heap structure
        numberOfTables--;
    }
}


// YOU CAN ADD YOUR HELPER FUNCTIONS


