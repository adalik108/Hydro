
#ifndef HYDRO_H
#define HYDRO_H

#include "list.h"

#define Y_LIM_LOW 0
#define Y_LIM_HIGH 4999
#define F_LIM_LOW 0

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

void getNumInput(ifstream& input, int& dest);

void getNumInput(ifstream& input, double& dest);

void getNumInput(int& dest);

void getNumInput(double& dest);

ListItem set_item(ifstream& input);

int nextTask(const int x, FlowList& list);

void clearBuffer();

bool validItem(ListItem& item);

#endif
