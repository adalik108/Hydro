
#ifndef HYDRO_H
#define HYDRO_H

#include "list.h"

int readData(ifstream& input, FlowList& list);

int menu();

void display(FlowList& list);

void displayHeader();

void addData(FlowList& list);

void removeData(FlowList& list);

double average(FlowList& list);

double median(FlowList& list);

void saveData(FlowList& list);

void pressEnter();

void openFile_w(const char* file, ofstream& outFile);

void openFile_r(const char* file, ifstream& inFile);

int char_to_int(const char* a);

double char_to_double(const char* a);

char* get_input(ifstream& input);

ListItem set_item(ifstream& input);

void nextTask(const int x, FlowList& list);



#endif
