#include <iostream>
#include<fstream>
#include <string>
using namespace std;
class Expense
{
private:
    int Id;
    string Title;
    string Category;
    float amount;
    string date;
public:
    Expense()
    {
        Id = 0;
        Title = "";
        Category = "";
        amount = 0.0;
        date = "";
    }
    void setData(int i, string t, string c, float a, string d)
    {
        Id = i;
        Title = t;
        Category = c;
        amount = a;
        date = d;
    }
    void input()
    {
        int categoryChoice;
        cout << "Enter Expense ID: ";
        cin >> Id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, Title);
        cout << "Enter Category: ";
        cout << "Select Category:\n1.Food\n2.Transport\n3.Education\n4.Shopping\n5.Other\nEnter Choice: ";
        cin >> categoryChoice;
        switch (categoryChoice)
        {
        case 1: {
            Category = "Food";
            break;
        }
        case 2:
        {
            Category = "Transport";
            break;
        }
        case 3:
        {
            Category = "Education";
            break;
        }
        case 4:
        {
            Category = "Shopping";
            break;
        }
        default:
        {
            Category = "Other";
            break;
        }
        }
        cin.ignore();
        cout << "Enter Amount: ";
        cin >> amount;
        cin.ignore();
        cout << "Enter Date(Format DD/MM/YY): ";
        getline(cin, date);
    }
    void update()
    {
        int categoryChoice;
        cout << "Enter New Title: ";
        getline(cin, Title);
        cout << "Select New Category:\n1.Food\n2.Transportaion\n3.Education\n4.Shopping\n5.Other\nEnter Choice: ";
        cin >> categoryChoice;
        switch (categoryChoice)
        {
        case 1: {
            Category = "Food";
            break;
        }
        case 2:
        {
            Category = "Transport";
            break;
        }
        case 3:
        {
            Category = "Education";
            break;
        }
        case 4:
        {
            Category = "Shopping";
            break;
        }
        default:
        {
            Category = "Other";
            break;
        }
        }
        cout << "Enter New Amount: ";
        cin >> amount;
        cin.ignore();
        cout << "Enter New Date(Format DD/MM/YY): ";
        getline(cin, date);
    }
    int getId()
    {
        return Id;
    }
    float getamount()
    {
        return amount;
    }
    string getCategory()
    {
        return Category;
    }
    string getDate()
    {
        return date;
    }
    string getTitle()
    {
        return Title;
    }
    void display()
    {
        cout << "\nExpense ID: " << Id << endl;
        cout << "Title: " << Title << endl;
        cout << "Category: " << Category << endl;
        cout << "Amount: " << amount << endl;
        cout << "Date: " << date << endl;
    }
    friend void compareExpense(const Expense& e1, const Expense& e2);
}; 
void compareExpense(const Expense& e1, const Expense& e2)
{
    if (e1.amount > e2.amount) {
        cout << "First expense is greater" << endl;
    }
    else if (e1.amount < e2.amount) {
        cout << "Second expense is greater" << endl;
    }
    else
    {
        cout << "Both are equal" << endl;
    }
}
void saveFile(Expense expenses[], int count)
{
    ofstream file("Expenses.txt");
    for (int i = 0; i < count; i++)
    {
        file << expenses[i].getId() << endl;
        file << expenses[i].getTitle() << endl;
        file << expenses[i].getCategory() << endl;
        file << expenses[i].getamount() << endl;
        file << expenses[i].getDate() << endl;
    }
    file.close();
}
void loadFile(Expense expenses[], int& count, int size)
{
    ifstream file("Expenses.txt");
        int id;
        string title;
        string category;
        float amount;
        string date;
        while (file >> id)
        {
            file.ignore();
            getline(file, title);
            getline(file, category);
            file >> amount;
            file.ignore();
            getline(file, date);
            if (count < size)
            {
                expenses[count].setData(id, title, category, amount, date);
                count++;
            }
        }
        file.close();
}
int main()
{
    int size;
    int choice;
    int count = 0;
    cout << "====Welcome to Expense Tracker=====" << endl;
    cout << "How many expenses you want to add?\n";
    cin >> size;
    Expense* expenses = new Expense[size];
    do {
        cout << "\nSelect an option and press coressponding number.\n1.Enter Your Expenses\n2.View All Expenses\n3.Search any of your expenses\n4.Delete Any Expense\n5.Update Expense\n6.Total Expense\n7.Category Summary\n8.Load Previous Data\n9.Compare Expenses\n10.Save and Exit" << endl;
        cin >> choice;
        switch (choice) {
        case 1: {
            if (count < size)
            {
                expenses[count].input();
                count++;
            }
            else {
                cout << "Storage Full" << endl;
            }
            break;
        }

        case 2: {
            if (count == 0)
            {
                cout << "No Expenses Found!" << endl;
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    expenses[i].display();
                    cout << endl;
                }
            }
            break;
        }
        case 3: {
            int searchId;
            bool found = false;
            cout << "Enter your Expense Id for search: ";
            cin >> searchId;
            for (int i = 0; i < count; i++)
            {
                if (expenses[i].getId() == searchId) {
                    expenses[i].display();
                    found = true;
                    break;
                }

            }
            if (!found)
            {
                cout << "Expense Record not Found!!!" << endl;
            }
            break;
        }
        case 4:
        {
            int deleteId;
            cout << "Enter the Expense Id you want to delete: ";
            cin >> deleteId;
            bool found = false;
            for (int i = 0; i < count; i++)
            {
                if (expenses[i].getId() == deleteId)
                {
                    found = true;
                    for (int j = i; j < count - 1; j++) {
                        expenses[j] = expenses[j + 1];
                    }
                    count--;
                    cout << "Deleted Successfully!" << endl;
                    break;
                }

            }
            if (!found)
            {
                cout << "Expense Not Found!" << endl;
            }
            break;
        }
        case 5:
        {
            int updateId;
            bool found = false;
            cout << "Enter Expense ID you want to update:";
            cin >> updateId;
            for (int i = 0; i < count; i++)
            {
                if (expenses[i].getId() == updateId)
                {
                    found = true;
                    cout << "Previous Details: " << endl;
                    expenses[i].display();
                    cout << endl;
                    cout << "Update the Expense: ";
                    expenses[i].update();
                    cout << "updated successfully!!!";
                    break;
                }
            }
            if (!found)
            {
                cout << "Expense Not Found!!!" << endl;
            }
            break;
        }
        case 6:
        {
            float total = 0.0;
            for (int i = 0; i < count; i++)
            {
                total += expenses[i].getamount();
            }
            cout << "Total Expenses are: " << total <<endl;
            break;
        }
        case 7:
        {
            float food = 0;
            float transport = 0;
            float education = 0;
            float shopping = 0;
            float other = 0;

            for (int i = 0; i < count; i++)
            {
                if (expenses[i].getCategory() == "Food")
                {
                    food += expenses[i].getamount();
                }
                else if (expenses[i].getCategory() == "Transport")
                {
                    transport += expenses[i].getamount();
                }
                else if (expenses[i].getCategory() == "Education")
                {
                    education += expenses[i].getamount();
                }
                else if (expenses[i].getCategory() == "Shopping")
                {
                    shopping += expenses[i].getamount();
                }
                else
                {
                    other += expenses[i].getamount();
                }
            }

            cout << "\nFood: " << food;
            cout << "\nTransport: " << transport;
            cout << "\nEducation: " << education;
            cout << "\nShopping: " << shopping;
            cout << "\nOther: " << other << endl;

            break;
        }
        case 8:
        {
            count = 0;
            loadFile(expenses, count, size);
            cout << "Data Loaded Successfully!!" << endl;
            break;
        }
        case 9:
        {
            int id1, id2;
            int i1 = -1, i2 = -1;
            cout << "Enter first expense ID: ";
            cin >> id1;
            cout << "Enter second expense ID: ";
            cin >> id2;
            for (int i = 0; i < count; i++)
            {
                if (expenses[i].getId() == id1)
                    i1 = i;

                if (expenses[i].getId() == id2)
                    i2 = i;
            }
            if (i1 != -1 && i2 != -1)
            {
                compareExpense(expenses[i1], expenses[i2]);
            }
            else
            {
                cout << "One or both expenses not found!" << endl;
            }
            break;
        }
        case 10:
        {
            char choice;
            cout << "Do you want to save before exit?(y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                saveFile(expenses, count);
                cout << "Data Saved Successfully." << endl;
            }
            cout << "Bye" << endl;
            break;
        }
        default:
        {
            cout << "Invalid Entry!!!" << endl;
            break;
        }
        }
       }while (choice != 10);
       delete[] expenses;
    return 0;
}