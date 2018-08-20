#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int currentNodeID=0;
map<int, struct node*> mapping;
struct node{
    	int rank, currentChildCount=0;
    	string owner, address, mobile, phone;
    	float value;
    	int nodeID;
    	struct node *referenceNodeID, *referenceChildNodeID;
    	int childNodeID[10]; // max possible childs=10
};
int currentRootCount=0;
struct node* allRoots[10];

void encryptAndSave(struct node* cNode, string owner, string address, string mobile, string phone, float val, int nodeID){
    //use nodeID as key to encrypt data and save the data to the node
    cNode->owner = owner;
    cNode->address = address;
    cNode->mobile = mobile;
    cNode->phone = phone;
    cNode->value = val;
}


void newRootNode(string owner, string address, string mobile, string phone, float value){
    if(currentRootCount < 10){
        struct node* root = (node*)malloc(sizeof(struct node));
        allRoots[currentRootCount] = root;
        currentRootCount++;
        root->referenceNodeID = NULL;
        root->rank = 0;
        root->referenceChildNodeID = root;
        encryptAndSave(root, owner, address, mobile, phone, value, currentNodeID);
        root->nodeID = currentNodeID;
        mapping.insert(make_pair(currentNodeID, root));
        currentNodeID++;
    }else{
        cout << "Only 10 root nodes are allowed." << endl;
    }
}

void unioN(int childID, int parentID){
    struct node *childAdd=NULL, *parentAdd=NULL;
    for(map<int, struct node*>::iterator i=mapping.begin(); i!=mapping.end(); ++i){
        if(childAdd && parentAdd)
            break;
        if(i->first == childID){
            childAdd = i->second;
        }
        if(i->first == parentID){
            parentAdd = i->second;
        }
    }
     	if(parentAdd && childAdd){
            while(parentAdd->referenceNodeID){
                parentAdd = parentAdd->referenceNodeID;
            }
            while(childAdd->referenceNodeID){
                childAdd = childAdd->referenceNodeID;
            }
            if(childAdd->rank < parentAdd->rank){
                childAdd->referenceNodeID = parentAdd;
               // parentAdd->childNodeID.push_back(childAdd->nodeID); 
            }else{
                parentAdd->referenceNodeID = childAdd;
                //childAdd->childNodeID.push_back(parentAdd->nodeID);
                if(childAdd->rank == parentAdd->rank){
                    parentAdd->rank = 2*parentAdd->rank;
                }                    
            }
        }else{
            //cout << "parent or child ID not found";
        }
        
    
};

struct node* findByID(int id){
    struct node* adr=NULL;
   for(map<int, struct node*>::iterator i=mapping.begin(); i!=mapping.end(); ++i){
       if(i->first == id){
           adr = i->second;
       }

   }
   if(adr) {return adr;}
   else{
       cout << "not found";
       return adr;
   }
}

//void  


int main()
{
   	//IDs ofnodes start from 0 and goes on increasing as new nodes are created.
	newRootNode("Gaurav", "BLB", "8860449388", "xxx", 4.0);//id=0 because its first node created
    newRootNode("Ram", "Fbd", "8998898989", "xxxx", 5.0);//id=1because its second created
    unioN(0, 1);
    cout << findByID(1)->referenceNodeID->owner;
    return 0;
}
