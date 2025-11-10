#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;


class Admin{
    struct Item{
        string name;
        int id;
        double price;
        int quantity;
    };
    vector<Item> inventory;

    void add_item_to_file(Item& item)
    {
        fstream file("stock.txt", ios::in);
        if(!file) {
            ofstream createfile("stock.txt");
            createfile.close();
        }
        file.close();

        fstream outfile("stock.txt", ios::app);
        outfile<<left<<setw(15)<<item.id<<setw(15)<<item.name<<setw(15)<<item.price<<setw(15)<<item.quantity<<endl;
        outfile.close();
    }
    void load_from_file()
    {
        inventory.clear();
        fstream file("stock.txt",ios::in);
        if(!file)
        {
            ofstream createfile("stock.txt");
            createfile.close();
        }
        Item temp;
        while(file>>temp.id>>temp.name>>temp.price>>temp.quantity)
        {
            inventory.push_back(temp);
        }
        file.close();
        cout<<"\n                \033[1;35mStock Availability\033[0m          \n";
        cout<<"\033[4m"<<left<<setw(53)<<""<<"\033[0m"<<endl;  //FOR CREATING A LINE
        cout<<"\033[1;33m"<<left<<setw(15)<<"Item ID"<<setw(15)<<"Name"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<"\033[0m\n";
        for(int i=0;i<inventory.size();i++)
        {
            cout<<left<<setw(15)<<inventory[i].id<<setw(15)<<inventory[i].name<<setw(15)<<inventory[i].price<<setw(15)<<inventory[i].quantity<<endl;
        }
        cout<<"\033[4m"<<left<<setw(53)<<""<<"\033[0m\n\n"<<endl;  //FOR CREATING A LINE
    }
public:
    void load()
    {
        load_from_file();
    }

    void admin_menu()
    {
        cout << "\n=====================================\n";
        cout << "|           ADMIN's ROLE            |\n";
        cout << "=====================================\n";
        cout << "|  1. Add Itmes                     |\n";
        cout << "|  2. Update Items                  |\n";
        cout << "|  3. Delete Items                  |\n";
        cout << "|  4. Display Items                 |\n";
        cout << "|  5. Search Items                  |\n";
        cout << "|  6. Exit Admin's Role             |\n";
        cout << "=====================================\n";
    }
    void add_Items()
    {
        cout<<"\n\033[1;31m"; // bright red
        cout<<">>> NOTE: If nothing left to enter, hit ENTER at Item ID column <<<";
        cout<<"\033[0m \n"; // resets the styling and back to normal
        cout<<"\n\033[1;4;33m";
        cout<<left<<setw(48)<<""<<endl;
        cout<<"\033[0m \n";
        int i=1;
        cin.ignore();
        while(true)
        {
            Item new_item;
            cout<<i<<".\n";
            i++;
            cout << "Enter Item ID (or press Enter to stop): "; //if hits enter the loop exits if not then the flow of instructions follow as below
            string input;
            getline(cin, input);
            if (input.empty()) break;
            new_item.id = stoi(input);

            cout << "Enter Name: ";
            getline(cin, new_item.name);

            cout << "Enter Price: ";
            cin >> new_item.price;

            cout << "Enter Quantity: ";
            cin >> new_item.quantity;
            cin.ignore(); // clear buffer

            inventory.push_back(new_item);
            cout<<"\n\033[1;32m";
            cout << "Item added successfully!\n";
            cout<<"\033[0m \n";
            add_item_to_file(new_item);
        }
        cout<<"\033[1;4;33m";
        cout<<left<<setw(48)<<""<<endl;
        cout<<"\033[0m \n";
        return;
    }
    int getId(int update_id)
    {
        for(int i=0;i<inventory.size();i++)
        {
            if(inventory[i].id==update_id) return i;
        }
        return -1;
    }
    int getName(string item_name)
    {
        for(int i=0;i<inventory.size();i++)
        {
            if(inventory[i].name==item_name) return i;
        }
        return -1;
    }
    float getPrice(string item_name)
    {
        for(int i=0;i<inventory.size();i++)
        {
            if(inventory[i].name==item_name) return inventory[i].price;
        }
        return -1;
    }
    void update_file()
    {
        ofstream file("stock.txt",ios::trunc); //clears the file
        file.close();
        for(int i=0;i<inventory.size();i++)
        {
            add_item_to_file(inventory[i]);
        }
    }
    void update_Items()
    {
        cout<<"\n\033[1;33m"<<"<<<You are at Update Items track>>>\n"<<"\033[0m";
        int update_id;
        cout<<"\nEnter the Item ID to be Update:";
        cin>>update_id;
        int result=getId(update_id);
        if(result!=-1)
        {
            cout<<"Item-ID "<<"\033[1;33m"<<update_id<<"\033[0m"<<" FOUND\n";
            cout<<"\033[4m";
            cout<<left<<setw(48)<<""<<endl;
            cout<<"\033[0m \n";
            cout<<"\033[1;33m"<<left<<setw(15)<<"Item ID"<<setw(15)<<"Name"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<"\033[0m";
            cout<<" \n";
            cout<<left<<setw(15)<<inventory[result].id<<setw(15)<<inventory[result].name<<setw(15)<<inventory[result].price<<setw(15)<<inventory[result].quantity<<endl;
            cout<<"\033[4m";
            cout<<left<<setw(48)<<""<<endl;
            cout<<"\033[0m \n";
            cout<<"\nEnter what to update for the above item(1.Name or 2.Price or 3.Quantity):";
            int what;
            cin>>what;
            switch(what)
            {
                case 1: {
                    cout<<"Enter the New Name(previously it was "<<"\033[1;33m"<<inventory[result].name<<"\033[0m"<<"):";
                    cin.ignore();
                    getline(cin, inventory[result].name);
                    cout<<"\033[1;32m \nUpdated Successfully\n \033[0m";
                }break;
                case 2: {
                    cout<<"Enter the New Price(previously it was "<<"\033[1;33m"<<inventory[result].price<<"\033[0m"<<"):";
                    cin>>inventory[result].price;
                    cout<<"\033[1;32m \nUpdated Successfully\n \033[0m";
                }break;
                case 3: {
                    cout<<"Enter the New Quantity(previously it was "<<"\033[1;33m"<<inventory[result].quantity<<"\033[0m"<<"):";
                    cin>>inventory[result].quantity;
                    cout<<"\033[1;32m \nUpdated Successfully\n \033[0m";
                }break;
                default:cout<<"\033[1;31m"<<"\nERROR>>>"<<"\033[0m"<<"\033[1;33m"<<"check the choice correctly\n"<<"\033[0m";break;
            }
            update_file();
        }
        else
        {
            cout<<"\n\033[1;31m SORRY>>> \033[0m Item-ID "<<"\033[1;33m"<<update_id<<"\033[0m"<<" NOT FOUND\n";
        }
    }

    void del_Items()
    {
        int del_id;
        cout<<"Enter the Element ID to be deleted:";
        cin>>del_id;
        int result=getId(del_id);
        if(result!=-1)
        {
            string is_confirm;
            cout<<"\n\033[1;34mAre you SURE!!!\033[0m\n\nIf SURE type \033[1;31m YES \033[0m otherwise type \033[1;31m NO \033[0m";
            cout<<"TYPE:";
            cin.ignore();
            getline(cin,is_confirm);
            if("YES"==is_confirm || "yes"==is_confirm)
            {
                inventory.erase(inventory.begin()+result);
                cout<<"\033[1;32m \nDeleted Successfully\n \033[0m";
            }
            else
            {
                cout<<"\n\033[1;33m>>>Thank You for your CONFIRMATION<<< \033[0m \n";
            }
            update_file();
        }
        else
        {
            cout<<"\nItem with ID "<<"\033[1;33m"<<del_id<<"\033[0m"<<"\033[1;32m NOT able to delete\033[0m.\033[1;33m Since it is not present in your Stock.\033[0m \n";
        }
    }
    void show_Items()
    {
        cout<<"\033[4m";
        cout<<left<<setw(48)<<""<<endl;
        cout<<"\033[0m \n";
        cout<<"\033[1;33m"<<left<<setw(15)<<"Item ID"<<setw(15)<<"Name"<<setw(15)<<"Price"<<setw(15)<<"Quantity\n"<<"\033[0m";
        cout<<" \n";
        if(inventory.size()!=0)
        {
            for(int i=0;i<inventory.size();i++)
            {
                cout<<left<<setw(15)<<inventory[i].id<<setw(15)<<inventory[i].name<<setw(15)<<inventory[i].price<<setw(15)<<inventory[i].quantity<<endl;
            }
        }
        else
        {
            cout<<"\033[1;31m NO Items\033[0m\n";
        }
        cout<<"\033[4m";
        cout<<left<<setw(48)<<""<<endl;
        cout<<"\033[0m \n";
    }
    void search_Items()
    {
        int search_item;
        cout<<"\nEnter the Item ID to be Search:";
        cin>>search_item;
        int result=getId(search_item);
        if(result!=-1)
        {
            cout<<"Item-ID "<<"\033[1;33m"<<search_item<<"\033[0m"<<" FOUND\n";
            cout<<"\033[4m";
            cout<<left<<setw(48)<<""<<endl;
            cout<<"\033[0m \n";
            cout<<"\033[1;33m"<<left<<setw(15)<<"Item ID"<<setw(15)<<"Name"<<setw(15)<<"Price"<<setw(15)<<"Quantity\n"<<"\033[0m";
            cout<<" \n";
            cout<<left<<setw(15)<<inventory[result].id<<setw(15)<<inventory[result].name<<setw(15)<<inventory[result].price<<setw(15)<<inventory[result].quantity<<endl;
            cout<<"\033[4m";
            cout<<left<<setw(48)<<""<<endl;
            cout<<"\033[0m \n";
        }
        else
        {
            cout<<"\nItem-ID \033[1;33m "<<search_item<<"\033[0m NOT Found\n";
        }
    }
    int stock_check(string item_name)
    {
        return getName(item_name);
    }
    int getQuantity(string item_name)
    {
        for(int i=0;i<inventory.size();i++)
        {
            if(inventory[i].name==item_name) return inventory[i].quantity;
        }
        return -1;
    }
    void update_quantity(int qty,int res)
    {
        inventory[res].quantity-=qty;
    }
};

class Cashier{
    struct Bill_Item{
        string name;
        int quantity;
        float price;
    };
    vector<Bill_Item> Bill;

public:
    int getBill_Number()
    {
        int  bill_no=0;
        fstream file("bill_number.txt",ios::in);
        if(!file.is_open())
        {
            ofstream createfile("bill_number.txt");
            createfile<<bill_no;
            createfile.close();
        }
        else
        {
            file>>bill_no;
            file.close();
        }

        bill_no++;
        ofstream outfile("bill_number.txt",ios::trunc);
        outfile<<bill_no;
        outfile.close();
        return bill_no;
    }
    void cashier_menu()
    {
        cout << "\n=====================================\n";
        cout << "|           CASHIER's ROLE          |\n";
        cout << "=====================================\n";
        cout << "|  1. Create Bill                   |\n";
        cout << "|  2. Check Stock                   |\n";
        cout << "|  3. Exit Cashier's Role           |\n";
        cout << "=====================================\n";
    }
    void display_bill(int bill_num)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        cout<<"\n\n===============================================================\n";
        cout<<"                          Billing                            ";
        cout<<"\n---------------------------------------------------------------\n";
        cout<<"Bill No: "<<bill_num<<endl;
        cout << "Date & Time: "
             << 1900 + ltm->tm_year << "-"
             << 1 + ltm->tm_mon << "-"
             << ltm->tm_mday;

        cout << " | "
             << ltm->tm_hour << ":"
             << ltm->tm_min << ":"
             << ltm->tm_sec << endl;
        cout<<"---------------------------------------------------------------\n";
        cout<<"\033[1;33m"<<left<<setw(15)<<"S.No"<<setw(15)<<"Item Name"<<setw(15)<<"Quantity"<<setw(15)<<"Price"<<setw(15)<<"Total"<<"\033[0m";
        cout<<"\n---------------------------------------------------------------\n";
        float sub_total=0.0;
        for(int i=0;i<Bill.size();i++)
        {
            cout<<left<<setw(15)<<i+1<<setw(15)<<Bill[i].name<<"\033[1;33m"<<setw(15)<<Bill[i].quantity<<setw(15)<<Bill[i].price<<setw(15)<<(Bill[i].quantity)*(Bill[i].price)<<"\033[0m"<<endl;
            sub_total+=(Bill[i].quantity)*(Bill[i].price);
        }
        cout<<"\n----------------------------------------------------------------\n";
        cout<<right<<setw(57)<<"Grand Total: "<<fixed<<setprecision(2)<<sub_total;
        cout<<"\n----------------------------------------------------------------\n";
        cout<<"                    \033[1;33mTHANK YOU! VISIT AGAIN\033[0m         ";
        cout<<"\n----------------------------------------------------------------\n\n";
    }
    void check_stock(Admin &admin)
    {
        admin.load();
    }
    void create_bill(Admin& admin)
    {
        Bill_Item temp;
        cout << "\n\033[1;31m>>>Enter items for the bill\033[0m(press \033[1;33mENTER\033[0m for ITEM_NAME to \033[1;33mFINISH Billing\033[0m)\n";
        cin.ignore();
        while(1)
        {
            cout << "\nItem name: ";
            getline(cin, temp.name);

            if (temp.name.empty()) break;

            int result;
            temp.price=admin.getPrice(temp.name);
            result=admin.stock_check(temp.name);
            if(result!=-1)
            {
                cout<<"\nAvailability for "<<"\033[1;33m"<<temp.name<<" is "<<admin.getQuantity(temp.name)<<"\033[0m\n";
                cout << "Quantity: ";
                cin >> temp.quantity;
                cin.ignore();
                if(admin.getQuantity(temp.name)>=temp.quantity)
                {
                    admin.update_quantity(temp.quantity,result);
                    Bill.push_back(temp);
                }
                else{
                    cout<<"\n\033[1;31m==========Out of Stock==========\033[0m\n";
                }
            }
            else{
                cout<<"\n\033[1;31m==========Not in Stock==========\033[0m\n";
            }
        }
        admin.update_file();
        int bill_no=getBill_Number();
        display_bill(bill_no);
    }
};



int main() {
    Admin a1;
    a1.load();
    while(1)
    {
        int choice;
        cout<<"\033[1;33m";
        cout<<"1.Admin\n2.Cashier\n3.Exit\nEnter the choice:";
        cout<<"\033[0m";
        cin>>choice;
        if(choice==3) break;
        switch(choice)
        {
            case 1:
            {
                while(1)
                {
                    a1.admin_menu();
                    cout<<"\nEnter the choice:";
                    cin>>choice;
                    if(choice==6) break;
                    switch(choice)
                    {
                        case 1:a1.add_Items();break;
                        case 2:a1.update_Items();break;
                        case 3:a1.del_Items();break;
                        case 4:a1.show_Items();break;
                        case 5:a1.search_Items();break;
                        default:cout<<"\n\n<<<<<\033[1;31mError in Entered choice\033[0m>>>>>\n\n";
                    }
                }
                cout<<"\033[1;32m\n==========Exiting Admin's Role==========\n\n\033[0m";
            }
            break;

            case 2:{
                Cashier c1;

                while(1)
                {
                    c1.cashier_menu();
                    cout<<"Enter the choice:";
                    cin>>choice;
                    if(choice==3)break;
                    switch(choice)
                    {
                        case 1:c1.create_bill(a1);break;
                        case 2:c1.check_stock(a1);break;
                        default:cout<<"\n\n<<<<<\033[1;31mError in Entered choice\033[0m>>>>>\n\n";break;
                    }
                }
                cout<<"\033[1;32m\n==========Exiting Cashier's Role==========\n\n\033[0m";
            }
            break;

            default:
                cout<<"\n<<<<<\033[1;31mKindly Re-Enter the choice for your Role\033[0m>>>>>\n\n";
        }
    }
}

