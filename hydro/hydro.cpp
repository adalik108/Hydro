/*
 Bugs:
 
    
 */



#include <iostream>
#include <stdlib.h>
using namespace std;
#include "hydro.h"
#include <fstream>
//#include "list.h"
#include <string>

int main()
{
    ifstream input;
    FlowList list;
    list.set_numData(readData(input, list));
    displayHeader();
    while(nextTask(menu(), list));
}

void displayHeader()
{
    cout << "Program:  Flow Sudies - Fall 2017 \n" << "Version:  1.0 \n" << "Lab Section: B04 \n" << "Produced by: Aaron Dalik \n";
    pressEnter();
}

void pressEnter()
{
    cout << "\n<<<< Press Enter to Continue >>>>\n";
    clearBuffer();
}

int menu()
{
    int a;
    cout << "\nPlease select from the following operations\n" << "    1.  Display flow list, average, and median\n" << "    2.  Add data\n" << "    3.  Save data into the file\n";
    cout << "    4.  Remove data\n" << "    5.  Quit\n" << "    Enter your choice (1, 2, 3, 4, or 5) :\n";
    getNumInput(a);
    
    return a;
}

void openFile_r(const char* file, ifstream& inFile)
{
    inFile.open(file);
    if(inFile.fail())
    {
        cerr << "file failed to open\n";
        exit(1);
    }
}

void openFile_w(const char* file, ofstream& outFile)
{
    outFile.open(file, ios::trunc);
    if(outFile.fail())
    {
        cerr << "file failed to open\n";
        exit(1);
    }
}

int readData(ifstream& input, FlowList& list)
{
    int x = 0;
    openFile_r("/Users/aaron.dalik/Documents/Engg_Year_2/ENCM_339/Hydro/hydro/flow.txt", input);
    ListItem item;
    
    while(!input.eof())
    {
        //ListItem item;
        item = set_item(input);
        if(validItem(item))
        {
            list.addNode();
            list.list_set_item(item);
            x++;
        }
    }
    input.close();
    
    return x;
}

void getNumInput(ifstream& input, int& dest)
{
    input >> dest;
    
    if(cin.fail())
        dest = Y_LIM_HIGH + 1;
}

void getNumInput(ifstream& input, double& dest)
{
    input >> dest;
    
    if(cin.fail())
        dest = F_LIM_LOW - 1;
}

void getNumInput(int& dest)
{
    cin >> dest;
    
    if(cin.fail())
        dest = Y_LIM_HIGH + 1;
}

void getNumInput(double& dest)
{
    cin >> dest;
    
    if(cin.fail())
        dest = F_LIM_LOW - 1;
}

ListItem set_item(ifstream& input)
{
    ListItem item;
    getNumInput(input, item.year);
    getNumInput(input, item.flow);
    
    return item;
}

void printList_original(FlowList& list)
{
    cout << "Flow List: \n";
    list.get_list_original();
    //exit(1);
}

int nextTask(const int x, FlowList& list)
{
    int a = 1;

    switch(x){
        case 1: display(list);
            break;
            
        case 2: addData(list);
            break;
            
        case 3: saveData(list);
            break;
            
        case 4: removeData(list);
            break;
            
        case 5: cout << "\nProgram terminated successfully.\n";
            a = 0;
            break;
            
        //case 6: a = 2
            
        default: cout << "\nInvalid request.\n";
            break;
    }
    
    if(a)
    {
        clearBuffer();
        pressEnter();

    }
   // clearBuffer();
    return a;
}

void display(FlowList& list)
{
    list.sortList();
    cout << "Year" << "    " << "Flow (in millions of cubic meters)" << endl;
    cout << "____" << "    " << "___________________________________" << endl;
    
    list.get_list_sorted();
    
    cout << "...\n";
    cout << "The annual average of the flow is:  " << average(list) << " million cubic meters\n";
    cout << "The median flow is:  " << median(list) << " million cubic meters\n";
}

double average(FlowList& list)
{
    double sum = 0;
    list.findHeadO();
    while(list.get_curr() != 0)
    {
        sum += list.get_flow();
        list.nextNode();
    }
    
    return sum/list.get_numData();
}

double median(FlowList& list)
{
    int i = 0;
    list.findHeadS();
    while(i < (list.get_numData() / 2))
    {
        list.nextNode();
        i++;
    }
    
    return list.get_flow();
}

void addData(FlowList& list)
{
    ListItem item;
    cout << "\nPlease enter a year:  ";
    getNumInput(item.year);
    cout << "\nPlease enter a flow:  ";
    getNumInput(item.flow);
    
    if(!validItem(item))
        cerr << "\nInvalid data\n";
    
    else if(!list.isDuplicate(item.year))
    {
        list.addNode();
        list.list_set_item(item);
        list.set_numData(list.get_numData() + 1);
        cout << "\nNew record inserted successfully.\n";
    }
    
    else
        cerr << "\nError: Duplicate data.\n";
}

void removeData(FlowList& list)
{
    int year;
    cout << "\nPlease enter the year you want to remove:  ";
    getNumInput(year);
    if(list.isDuplicate(year))
    {
        list.removeNode();
        cout << "\nRecord was successfully removed.\n";
        list.set_numData(list.get_numData() - 1);
    }
    else
        cerr << "\nError: No such data\n";
}

void saveData(FlowList& list)
{
    ofstream outFile;
    openFile_w("/Users/aaron.dalik/Documents/Engg_Year_2/ENCM_339/Hydro/hydro/flow.txt", outFile);
    list.writeList(outFile);
    cout << "\nData was saved into the file.\n";
    outFile.close();
}

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //cin.ignore();
}

bool validItem(ListItem& item)
{
    if(item.year < Y_LIM_LOW || item.year > Y_LIM_HIGH || item.flow < F_LIM_LOW)
        return false;
    
    return true;
}

