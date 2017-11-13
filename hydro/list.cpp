

#include <iostream>
#include <stdlib.h>
using namespace std;
#include "list.h"
#include <fstream>

FlowList::FlowList(const FlowList& list)
{
	copyList(list);	
}

FlowList& FlowList::operator =(const FlowList& rhs)
{
	if(this != &rhs)
	{
		destroy();
		copyList(rhs);
	}

	return *this;
}

FlowList::~FlowList()
{
	destroy();
}

//void FlowList::buildList(const ifstream&)

void FlowList::list_set_item(const ListItem& input)
{
	curr -> item = input;
}

void FlowList::list_set_item(const ListItem& input, Node*& dest)
{
	dest -> item = input;
}

void FlowList::list_set_item(const int year, const double flow)
{
	curr -> item.year = year;
	curr -> item.flow = flow;
}

//ListItem FlowList::lsjd();

void FlowList::addNode()
{
	if(headO == 0)
	{
		headO = new Node;
		curr = headO;
		curr -> next = 0;
		curr -> prev = 0;
	}

	else
	{
        curr = headO;
		findLast(curr);
		curr -> next = new Node;
		curr -> next -> prev = curr;
		nextNode(curr);

		curr -> next = 0;
	}
}

void FlowList::addNode(Node*& head)
{
	curr = head;
	if(curr == 0)
	{
		curr = new Node;
		head = curr;
		curr -> next = 0;
		curr -> prev = 0;
	}

	else
	{
		findLast(curr);
		curr -> next = new Node;
		curr -> next -> prev = curr;
		nextNode(curr);

		curr -> next = 0;
	}
}

void FlowList::findLast(Node*& curr)
{
	while(curr -> next != 0)
		nextNode(curr);
}

void FlowList::nextNode(Node*& curr)
{
	curr = curr -> next;
}

void FlowList::nextNode()
{
	curr = curr -> next;
}

void FlowList::prevNode(Node*& curr)
{
	curr = curr -> prev;
}

void FlowList::prevNode()
{
	curr = curr -> prev;
}

void FlowList::get_list_original()
{
	findHeadO();
	while(curr != 0)
	{
		cout << curr -> item.year << "	" << curr -> item.flow << endl;
		curr = curr -> next;
	}
}

void FlowList::get_list_sorted()
{
	findHeadS();
	while(curr != 0)
	{
		cout << curr -> item.year << "	" << curr -> item.flow << endl;
        nextNode();
	}
}

void FlowList::copyList(const FlowList& list)
{
	findHeadO();
	Node* temp = list.headO;
	copyNodes(headO, temp);

	findHeadS();
	temp = list.headS;
	copyNodes(headS, temp);
}

void FlowList::destroy()
{
	if(headO)
	{
		findHeadO();
		findLast(curr);
		prevNode(curr);
		while(curr != 0)
		{
			delete curr -> next;
			prevNode(curr);
		}
		delete headO;
		headO = 0;
	}
    
    if(headS)
    {
        findHeadS();
        findLast(curr);
        prevNode(curr);
        while(curr != 0)
        {
            delete curr -> next;
            prevNode(curr);
        }
        delete headS;
        headS = 0;
    }
}
    
void FlowList::destroy(Node*& head)
{
    if(head == headO && headO != 0)
    {
        findHeadO();
        findLast(curr);
        prevNode(curr);
        while(curr != 0)
        {
            delete curr -> next;
            prevNode(curr);
        }
        delete headO;
        headO = 0;
    }
        
    if(head == headS && headS != 0)
    {
        findHeadS();
        findLast(curr);
        prevNode(curr);
        while(curr != 0)
        {
            delete curr -> next;
            prevNode(curr);
        }
        delete headS;
        headS = 0;
    }
}

void FlowList::sortList()
{
	if(headO)
	{
        destroy(headS);
		Node* temp = headO;
		findHeadS();

		while(temp != 0)
		{
			insertNode(temp -> item);
			//cout << "flow is: " << curr -> prev -> item.flow << endl;
			nextNode(temp);
		}
	}
}

void FlowList::copyNodes(Node*& dest, Node*& source)
{
	if(source)
	{
		addNode(dest);
		*curr = *source;
		nextNode(source);
	}	
}

void FlowList::insertNode(const ListItem& item)
{

	Node* temp = new Node;
	findHeadS();

	if(curr == 0)
	{
		/*
		temp -> prev = curr;
		curr = temp;
		curr -> next = 0;
		headS = curr;
		*/

		addNode(headS);
		list_set_item(item);
        delete temp;
	
		//cout << curr->item.flow << endl;
	}

	else
	{

		while(item.flow > curr -> item.flow && curr -> next != 0)
		{
			nextNode(curr);
		}

		if(curr -> next == 0)
		{
			addNode(headS);
			list_set_item(item);
            delete temp;
		}
        
        else if(curr -> prev == 0)
        {
            list_set_item(item, temp);
            headS = temp;
            temp -> next = curr;
            temp -> prev = 0;
            curr -> prev = temp;
        }

		else
		{
			list_set_item(item, temp);
			temp -> next = curr;
			temp -> prev = curr -> prev;
			temp -> prev -> next = temp;
			curr -> prev = temp;
		}
	}
}

void FlowList::insertNode(Node*& dest, const ListItem& item)
{

	Node* temp = new Node;
	if(dest == headS)
	{
		findHeadS();

		if(curr == 0)
		{	

			addNode(headS);
			list_set_item(item);
	
		//cout << curr->item.flow << endl;
		}

		else
		{
			findHeadS();

			while(item.flow > curr -> item.flow && curr -> next != 0)
			{
				nextNode(curr);
		
			}

			if(curr -> next == 0)
			{
				addNode(headS);
				list_set_item(item);
			}

			else
			{
				list_set_item(item, temp);
				temp -> next = curr;
				temp -> prev = curr -> prev;
				temp -> prev -> next = temp;
				curr -> prev = temp;
			}
		}
	}

	else if(dest == headO)
	{
		findHeadO();
		addNode(headO);
		list_set_item(item);
	}
}

double FlowList::get_flow()
{
	return curr -> item.flow;
}

void FlowList::findHeadO()
{
	curr = headO;
}

void FlowList::findHeadS()
{
	curr = headS;
}

Node* FlowList::get_curr()
{
	return curr;
}

bool FlowList::isDuplicate(ListItem& item)
{
    findHeadO();
    while(curr != 0)
    {
        if(curr -> item.year == item.year)
            return true;
        
        else
            nextNode();
    }
    return false;
}

void FlowList::removeNode()
{
    if(curr -> next)
    {
        curr -> prev -> next = curr -> next;
        curr -> next -> prev = curr -> prev;
    }
    else
        curr -> prev -> next = curr -> next;
    
    delete curr;
    findHeadO();
}

void FlowList::set_numData(const int x)
{
    numData = x;
}

int FlowList::get_numData()
{
    return numData;
}

void FlowList::writeList(ofstream& outFile)
{
    findHeadS();
    while(curr!= 0)
    {
        outFile << curr -> item.year << "    " << curr -> item.flow << endl;
        nextNode();
    }
}




