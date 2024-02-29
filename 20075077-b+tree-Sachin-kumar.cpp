//all leaves are at same level
//root has atleast two children
//each node except root has most m children and atleast m/2  children.
//maxm nodekeys = m-1 and minm nodekeys = m/2  - 1 
//sachin kumar
//20075077



#include <bits/stdc++.h>
using namespace std;



const int m=2;



class node
{
    public:
    int nodesize;
    bool isleafnode;
    int *nodekeys;
    node **childptr;
    node()
    {
        nodekeys=new int[m];
        childptr=new node *[m+1];
        nodesize=0;
        
    }
   
};
class bplustree
{
   public:
   node* root;
   bplustree()
   {
        root=NULL;
   }
   node* findparentnode(node* curroot , node* curchild)
   {
       node* parentnode;
        if(curroot->isleafnode||curroot->childptr[0]->isleafnode)
       return NULL;
       for(int i=0;i<curroot->nodesize+1;i++)
       {
                    if(curroot->childptr[i]==curchild)
                   {
                       parentnode=curroot;
                       return parentnode;
                   }
                   else
                   {
                       parentnode = findparentnode(curroot->childptr[i],curchild);
                       if(parentnode!=NULL)
                       return parentnode;
                       
                   }
       }
       return parentnode;
   }
   
   
   
        void internalinserting(int ele,node* cur,node* newleafnode)
        {
                 if(cur->nodesize<m)
                  {
                  
                  int id=0;
                  while( id < cur->nodesize && ele>cur->nodekeys[id] ) 
                  ++id;
                  for(int j=cur->nodesize;j>id ;j--)
                  {
                      cur->nodekeys[j]=cur->nodekeys[j-1];
                  }
                  cur->nodekeys[id]=ele;
                  cur->nodesize++;
                  cur->childptr[id+1]=newleafnode;
                  }
                  else
                  {
                      
                      
                       
                      node* newparentsecond=new node; 
                       int tmpnodekeys[m+1];
                       node* tmpptrs[m+2];
                       for(int i=0;i<m+1;i++)
                       {
                           tmpptrs[i]=cur->childptr[i];
                           
                       }
                       for(int i=0;i<m;i++)
                       {
                           tmpnodekeys[i]=cur->nodekeys[i];
                           
                       }
                       int i=0;
                      
                       while(i<m&&ele>tmpnodekeys[i]) 
                       ++i;
                       int j;
                       for( j=m+1;j>i;j--)
                       {
                           tmpnodekeys[j]=tmpnodekeys[j-1];
                       }
                       tmpnodekeys[i]=ele;
                       for(int j=m+2;j>i+1;j--)
                       {
                           tmpptrs[j]=tmpptrs[j-1];
                       }
                       tmpptrs[i+1]=newleafnode;
                       
                       //cur
                       //newparentsecond
                       newparentsecond->isleafnode=false;
                       cur->nodesize = (m+1)/2;
                       newparentsecond->nodesize = m - (m+1)/2;
                       for(int i=0,j=cur->nodesize+1;i<newparentsecond->nodesize;i++,j++) //nodesize +1 so that same ele is not written twice first ele go the parent
                       {
                           newparentsecond->nodekeys[i]=tmpnodekeys[j];
                       }
                       for(int i=0,j=cur->nodesize+1;i<newparentsecond->nodesize+1;i++,j++)
                       {
                           newparentsecond->childptr[i]=tmpptrs[j];
                       }
                       
                       if(cur==root)
                       {
                           node* newgrandparent = new node;
                           newgrandparent->nodekeys[0]=cur->nodekeys[cur->nodesize];
                           newgrandparent->childptr[0]=cur;
                           newgrandparent->childptr[1]=newparentsecond;
                           newgrandparent->isleafnode=false;
                           newgrandparent->nodesize=1;
                           root=newgrandparent;
                       }
                       else
                       {
                           internalinserting(cur->nodekeys[cur->nodesize],findparentnode(root,cur),newparentsecond);
                       }
                        
                       
                       
                   }
                       
                       
  }
   void search_ele(int ele)
   {
      if(root == NULL)
      {
          cout<<"\nbplus tree is empty()!..";
      }
      else
      {
          node* cur=root;
          while(cur->isleafnode == false)
          {
              for(int i=0;i<cur->nodesize;i++)
              {
                  if(ele<cur->nodekeys[i])
                  {
                      cur=cur->childptr[i];
                      break;
                  }
                  if(i == cur->nodesize-1)
                  {
                      cur=cur->childptr[i+1];
                      break;
                  }
              }
          }
          for(int i=0;i<cur->nodesize;i++)
          {
              if(cur->nodekeys[i]==ele)
              {
                  cout<<"\nelement found in the tree!..";
                  return;
              }
          }
          cout<<"\nnot present in the bplus tree!..";
      }
   }
   void insert_ele()
   {
       cout<<"\nenter element to be inserted : ";
       int ele;
       cin>>ele;
       
       if(root==NULL)
       {
           root=new node;
           root->nodekeys[0]=ele;
           root->isleafnode=true;
           root->nodesize=1;
       }
       else
       {
           node* cur=root;
           node* parnode;
           while(cur->isleafnode==false)
           {
               parnode=cur;
               for(int i=0;i<cur->nodesize;i++)
               {
                   if(ele<cur->nodekeys[i])
                   {
                       cur=cur->childptr[i];
                       break;
                   }
                   if(i == cur->nodesize-1)
                   {
                       cur=cur->childptr[i+1];
                       break;
                   }
               }
           }
           if(cur->nodesize < m)
           {
               int id=0;
               while( id < cur->nodesize && ele>cur->nodekeys[id] ) 
               ++id;
               for(int j=cur->nodesize;j>id ;j--)
               {
                   cur->nodekeys[j]=cur->nodekeys[j-1];
               }
               cur->nodekeys[id]=ele;
               ++cur->nodesize;
               cur->childptr[cur->nodesize]=cur->childptr[cur->nodesize-1];
               cur->childptr[cur->nodesize-1]=NULL;
               
               
           }
           else
           {
               node* newleafnode = new node;
               int ar[m+1];
               for(int i=0;i<m;i++)
               {
                   ar[i]=cur->nodekeys[i];
               }
               
               int id=0;
               while( id < m && ele>ar[id] ) 
               ++id;
               for(int j=m+1;j>id ;j--)
               {
                   ar[j]=ar[j-1];
               }
               ar[id]=ele;
               newleafnode->isleafnode=true;
               cur->nodesize = (m+1)/2;
               newleafnode->nodesize = m+1 - (m+1)/2;
               cur->childptr[cur->nodesize]=newleafnode;
               newleafnode->childptr[newleafnode->nodesize]=cur->childptr[m];   // for right sibling giving pointer to newly formed node 
               cur->childptr[m]=NULL;
               for(int i=0;i<cur->nodesize;i++)
               {
                   cur->nodekeys[i]=ar[i];
               }
               for(int i=0,j=cur->nodesize;i<newleafnode->nodesize;i++,j++)
               {
                   newleafnode->nodekeys[i]=ar[j];
                   
               }
               
               if(cur==root)
               {
                node* newparent =  new node;
                newparent->nodekeys[0]=newleafnode->nodekeys[0];
                newparent->childptr[0]=cur;
                newparent->childptr[1]=newleafnode;
                newparent->isleafnode=false;
                newparent->nodesize=1;
                root=newparent;
               }
               else
               {
                   // we have a parent 
                   //newleafnode
                   //cur
                    internalinserting(newleafnode->nodekeys[0],parnode,newleafnode);

                   
                   
                   
               }
               
               
           }
       }
       
   }
   
   void displaybplustree(node* rootnode)
   {
       if(rootnode!=NULL)
       {
           for(int i=0;i<rootnode->nodesize;i++)
           {
               cout<<rootnode->nodekeys[i]<<" ";
           }
       }
       cout<<"\n";
       if(rootnode->isleafnode==false)
       {
           for(int i=0;i<rootnode->nodesize+1;i++)
           {
               displaybplustree(rootnode->childptr[i]);
           }
       }
   }
   
   
   
};

int main()
{
    
    bplustree tree;
    
    int ch;
    while(1)
    {
    cout<<"\nenter 1 for insertion , 2 for showing all  and 3 for searching :  \n";
    cin>>ch;
    switch(ch)
    {
        case 1:
        tree.insert_ele();
        break;
        
        case 2:
        tree.displaybplustree(tree.root);
        break;
        case 3:
        int dm;
        cout<<"\nenter element to be searched : ";
        cin>>dm;
        tree.search_ele(dm);
        
        
        
        
    }
    
        
        
    }
    
    
    

    return 0;
}