#include<bits/stdc++.h>

using namespace std;

int page_size;

class Page{

    public:

        Page(/* args */);
        ~Page();
        int no_of_records;
        int prev_add;
        int next_add;
        int start_add_for_free_space;
        int space_left;
        vector<pair<int,int>> data;

};

Page::Page(/* args */){
    no_of_records = 0;
    prev_add = -1;
    next_add = -1;
    start_add_for_free_space = 0;
    space_left = page_size- 16;
}

Page::~Page(){

}

vector<Page> heap_file;

int main(){
    int option, primary_key, size;
    cin>>page_size;
    // cout<<page_size<<endl;
    while(1){
        cin>>option;
        if(option==1){
            cin>>size>>primary_key;
            // cout<<"inside 1\n";
            // add this into file
            int needed_size = size + 4;
            bool added = false;
            for(int i=0;i<heap_file.size();i++){
                if(heap_file[i].space_left >= (needed_size)){
                    // add the record to this page, and then break;
                    heap_file[i].no_of_records++;
                    heap_file[i].data.push_back({primary_key,size});
                    heap_file[i].space_left -= needed_size;
                    added = true;
                    break;
                }
            }
            if(!added){
                // if we could add the record any prev record, then we create a new page and then append the page into the file
                Page new_page;
                // cout<<new_page.space_left<<"\n";
                new_page.space_left -= needed_size;
                new_page.data.push_back({primary_key,size});
                new_page.no_of_records++;
                heap_file.push_back(new_page);
                // cout<<"yes\n";
            }
        }else if(option==2){
            // show the status
            cout<<heap_file.size()<<" ";
            for(int i=0;i<heap_file.size();i++){
                cout<<heap_file[i].no_of_records<<" ";
            }
            cout<<endl;
        }else if(option==3){
            cin>>primary_key;
            //search for the primary key
            bool notfound = true;
            for(int i=0;i<heap_file.size();i++){
                for(int j=0;j<heap_file[i].data.size();j++){
                    if(primary_key == heap_file[i].data[j].first){
                        cout<<i<<" "<<j<<endl;
                        notfound = false;
                        break;
                    }
                }
                if(!notfound){
                    break;
                }
            }
            if(notfound){
                cout<<-1<<" "<<-1<<endl;
            }
        }else{
            // cout<<"inside 4\n";
            break;
        }
    }
    return 0;
}