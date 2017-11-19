
#ifndef LIST_H
#define LIST_H

struct ListItem
{
	int year;
	double flow;
};

struct Node
{
	ListItem item;
	Node* next;
	Node* prev;
};

class FlowList
{
	private:
		Node* headS;
		Node* headO;
		Node* curr;
        int numData;


	public:
		FlowList(): headO(0), headS(0), curr(0)
		{};

		FlowList(const FlowList& list);

		~FlowList();

		FlowList& operator =(const FlowList& rhs);

		void list_set_item(const ListItem& input);

		void list_set_item(const ListItem& input, Node*& dest);

		void list_set_item(const int year, const double flow);

		void addNode();

		void addNode(Node*& head);

		void findLast(Node*& curr);

		void nextNode(Node*& curr);

		void nextNode();

		void prevNode(Node*& curr);

		void prevNode();

		ListItem list_get_item();

		void get_list_original();

		void get_list_sorted();

		void copyList(const FlowList& list);

		void destroy();
    
        void destroy(Node*& head);

		void copyNodes(Node*& dest, Node*& source);

		void sortList();

		void insertNode(const ListItem& item);

		void insertNode(Node*& dest, const ListItem& item);

		double get_flow();

		void findHeadO();

		void findHeadS();

		Node* get_curr();
    
        bool isDuplicate(const int year);
    
        void removeNode();
    
        void set_numData(const int x);
    
        int get_numData();
    
        void writeList(ofstream& outFile);
    
};



#endif
