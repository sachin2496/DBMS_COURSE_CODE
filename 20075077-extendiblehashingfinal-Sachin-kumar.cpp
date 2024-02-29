#include<bits/stdc++.h>
using namespace std;
void display();
int m;
int directory_size=1;

class bucket
{
    public:
    int size;
    int localdepth;
    vector<int> elemntarray;
    bucket()
    {
        size=0;
    }


};
int hashf(int l,int n)
{
    int d = int((int)pow(2,l)-1) & n;
    return d;
}

class directory
{
    public:
    int globaldepth;
    int dirsize;
    
    directory()
    {
        globaldepth=0;
        dirsize=1;

    }

}dir;

map<int,bucket*> mp;

void bucketsplit(int key)
{
    if(mp[key]->localdepth==dir.globaldepth)
            {
                dir.dirsize*=2;
                bucket* newbucket = new bucket();
                vector<int> tmpar;
                
                for(int j=0;j<mp[key]->elemntarray.size();j++)
                {
                    tmpar.push_back(mp[key]->elemntarray[j]);
                }
                mp[key]->elemntarray.clear();
                //tmpar.push_back(ele);
               int kk = (1 << (dir.globaldepth))| key;
               
               mp[kk]=newbucket;
               dir.globaldepth++;
               for(int i=dir.dirsize/2;i<dir.dirsize;i++)
               {
                    if(mp.find(i)==mp.end())
                    {
                    int khh = hashf(dir.globaldepth-1,i);
                    mp[i] = mp[khh];
                    }
               }

               
               mp[key]->localdepth++;
               newbucket->localdepth=dir.globaldepth;
               for(int i=0;i<tmpar.size();i++)
               {
                    int hk = hashf(dir.globaldepth,tmpar[i]);
                   // cout<<hk<<" ";
                    mp[hk]->elemntarray.push_back(tmpar[i]);
                    mp[hk]->size++;
                    
               }
                if(mp[key]->elemntarray.size()>m)
                {
                    bucketsplit(key);
                }



                      if(newbucket->elemntarray.size()>m)
                      {
                        bucketsplit(kk);
                      }      

               }
            else      //when initial localdepth not equal to global depth
            {
                bucket* newbucket = new bucket();
                 
                 vector<int> tmpar;
                
                for(int j=0;j<mp[key]->elemntarray.size();j++)
                {
                    tmpar.push_back(mp[key]->elemntarray[j]);
                }
                mp[key]->elemntarray.clear();
                //tmpar.push_back(ele);
                mp[key]->localdepth++;
                newbucket->localdepth=mp[key]->localdepth;
                int hk = key | (1<<mp[key]->localdepth-1);
                mp[hk]=newbucket;
                for(auto it : mp)
                {
                    if(it.second==mp[key])
                    {
                        int kh=hashf(mp[key]->localdepth,it.first);
                        mp[it.first]=mp[kh];

                    }
                }

                for(int i=0;i<tmpar.size();i++)
                {
                    int id = hashf(mp[key]->localdepth,tmpar[i]);
                    mp[id]->elemntarray.push_back(tmpar[i]);
                }



                //case when element exceeds array

                if(mp[key]->elemntarray.size()>m)
                {
                    bucketsplit(key);
                }



                if(newbucket->elemntarray.size()>m)
                {
                    bucketsplit(hk);
                }
            
            



            }

}

void insertion()
{
    int ele;
    cout<<"\nenter the element to be inserted : ";
    cin>>ele;
    int key = hashf(dir.globaldepth,ele);
    cout<<key;

    if(mp.find(key)==mp.end())
    {
        bucket* newbucket = new bucket();
        mp[key]=newbucket;
        //newbucket->size++;
        newbucket->localdepth=dir.globaldepth;
        newbucket->elemntarray.push_back(ele);

    }
    else
    {
        if(mp[key]->elemntarray.size() < m)
        {
                cout<<mp[key]->elemntarray.size()<<" ";
                mp[key]->elemntarray.push_back(ele);
                mp[key]->size++;
        }
        else
        {
            mp[key]->elemntarray.push_back(ele);
            bucketsplit(key);

        }
    }

}

void searching()
{
    int searchele;
    cout<<"\nenter the element to be searched : ";
    
    cin>>searchele;
    int hk = hashf(dir.globaldepth,searchele);

    for(int i=0;i<mp[hk]->elemntarray.size();i++)
    {
        if(searchele==mp[hk]->elemntarray[i])
        {
            cout<<" \n Hurray ! element found in the extendible  hash map \n ";
            return;
        }

    }
    cout<<"\n not found !!!";

}

void mergebucket(int key)
{
    //cout<<mp[key]->localdepth<<" ";
    if(mp[key]->localdepth<1)
    return;
    int hk = key ^ (1<<((mp[key]->localdepth)-1));
    cout<<hk<<" "<<key;
    vector<int> tmparray;
    for(int i=0;i<mp[key]->elemntarray.size();i++)
    {
        tmparray.push_back(mp[key]->elemntarray[i]);
    }
    for(int i=0;i<mp[hk]->elemntarray.size();i++)
    {
        tmparray.push_back(mp[hk]->elemntarray[i]);
    }
    if(mp[key]==mp[hk])
    return;
   // cout<<key<<" "<<hk<<" ";
    int dem   = min(key,hk);
    hk = max(key,hk);
    key  = dem;
    if(tmparray.size()<=m)
    {
        mp[hk]=mp[key];
        mp[key]->elemntarray.clear();
        for(int i=0;i<tmparray.size();i++)
        {
            mp[key]->elemntarray.push_back(tmparray[i]);
        }

        mp[key]->localdepth--;
        mergebucket(key);
    }
    else{
        return;
    }


}

void shrinkdirectory()
{
    int f=0;
    for(int i=0;i<dir.dirsize;i++)
    {
        if(mp[i]->localdepth==dir.globaldepth)
        {
            f=1;
            break;
        }
    }
    if(f==0)
    {
        dir.dirsize=dir.dirsize/2;
        dir.globaldepth--;
        shrinkdirectory();
    }
    else
    {
        display();
        return;
    }
}

void deletion()
{
    cout<<"\nenter the element to be deleted : ";
    int delele;
    cin>>delele;
    int hk = hashf(dir.globaldepth,delele);
    int f=0;
    for(int i=0;i<mp[hk]->elemntarray.size();i++)
    {
        if(delele==mp[hk]->elemntarray[i])
        {
            f=1;
            mp[hk]->elemntarray.erase(mp[hk]->elemntarray.begin()+i);
             mergebucket(hk);
             shrinkdirectory();
            
        }

    }
    if(f==0)
    cout<<"\n not found !!!";

}

void display()
{
    
    for(int i=0;i<dir.dirsize;i++)
    {
        if(mp.find(i)==mp.end())
        return;
        bucket* bkt = mp[i];
        //if(bkt->elemntarray.size()==0)
        cout<<"\n elements of bucket   " << i <<" : "<<"local depth is  "<<mp[i]->localdepth<< " and elements are : ";
        for(int j=0;j<bkt->elemntarray.size();j++)
        {
            cout<<bkt->elemntarray[j]<<" ";
        }
    }
}



int main()
{
    cout<<"\nenter the size of bucket : ";
    cin>>m;
    

    int choice;
    
    while(1)
    {
        cout<<"\nenter 1 for insertion , 2 for deletion , 3 for display , 4 for searching , 5 for exit :  ";
        cin>>choice;
    switch(choice)
    {
        case 1:
        insertion();
        break;
        case 2 :
        deletion();
        break;
        case 3 :
        display();
        break;
        case 4 :
        searching();
        break;
        case 5 :
        return 0;
    }
    }
    return 0;
}