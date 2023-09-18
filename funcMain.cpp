#include "header.hpp"
#define MAX_SIZE 300

class LinkedListNode{
    public:
    string command;
    string description;
    LinkedListNode *next;
    LinkedListNode(string command, string description){
        this->command=command;
        this->description=description;
        this->next=NULL;
    }
};

//update player record
void updatePlayer(string playerName,int TotalQ, int score){
    ofstream file("profile.csv", ios::app);

    if(file.is_open()){
    
        file << playerName<<","<<TotalQ<<","<<score<<endl;
        file.close(); 
    }
    else
        cout<<"File error!"<<endl;
    
}

void findPlayer(){

    string name; //
    
    cout<<"Enter player name: "<<endl;
    cin>>name;

    vector<string> record;
    ifstream file;
    file.open("profile.csv");

    bool rfound = false;

    string f1,f2,f3;

    while(getline(file,f1,',') && !rfound){
        getline(file,f2,',');
        getline(file,f3,'\n');

        if(f1 == name){
            rfound = true;

            record.push_back(f1);
            record.push_back(f2);
            record.push_back(f3);
        }
    }
    file.close();
    if(record.empty()){
        cout<<"Player not found!"<<endl;

    }
    else{
        cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-"<<endl;
        cout<<"Player has been found:"<<endl;
        cout<<"Player Name: "<<record[0]<<endl;
        cout<<"Player attempted "<<record[1]<<" questions."<<endl;
        cout<<"Player achieved a score of "<<record[2]<<"."<<endl;
        cout<<"-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-"<<endl;

        getch();

        //cin.ignore(INT64_MAX, '\n'); // Eats previous "enter" press
        //cin.get();//exit on enter

    }

}

// void addCommand(){

    // vector<string> row;
    // string cname;
    // char cdef[MAX_SIZE];

    // cout<<"Enter the command's name you wish to add:";
    // cin>>cname;
    // cout<<endl;

    // cout<<"Enter the commands definiton:";
    // cin.ignore();
    // cin.getline(cdef,MAX_SIZE);

    // row.push_back(cname);
    // row.push_back(cdef);   //change these lines

    // commands.push_back(row);
       
    // cout<<"The new Command "<<cname<< " was added"<<endl;
    

// }
void insertCommand(LinkedListNode*& head, string& cmd, string& desc) {
    LinkedListNode* newNode = new LinkedListNode(cmd, desc);
    if (!head) {
        head = newNode;
    } else {
        LinkedListNode* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}
void deleteCommand(LinkedListNode*& head, const string& cmdToDelete) {
    if (!head) {
        return; // List is empty
    }

    if (head->command == cmdToDelete) {
        LinkedListNode* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    LinkedListNode* current = head;
    while (current->next) {
        if (current->next->command == cmdToDelete) {
            LinkedListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}



// void removeCommand(){
//     string cname;
//     cout<<"Enter the command you wish to delete: "<<endl;
//     cin>>cname;
//     int check = 0;
//     for(int i=0;i<commands.size();i++){
       
        
//         if(cname == commands[i][0]){
            
//             cout<<"the command - ";
//             for(int j=0;j<commands[i].size();j++)
//                 cout<<commands[i][j];
//             cout<<"- is being deleted!"<<endl;
//             commands.erase(commands.begin() + i);
//             check =1;
            
//             break;
//         }

//     }
//     if(check==0){
//         cout<<"This command was not found in our dataset."<<endl;
//     }
//     else{
//         cout<<"Deleted the command from the data Base"<<endl;
//     }
    
// }


//read question file and store in 2d Linked List
LinkedListNode* construct_List()
{
    ifstream inputFile("command.csv"); // Change the file name as per your CSV file
    
    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        exit(0);
    }
    
    string line;
    getline(inputFile, line); // Read and discard the header line
    
    LinkedListNode* head = nullptr; // Initialize the linked list
    
    while (getline(inputFile, line)) {
        // Assuming the CSV format is "command,description"
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string cmd = line.substr(0, commaPos);
            string desc = line.substr(commaPos + 1);
            insertCommand(head, cmd, desc); 
        }
        
    } 
    inputFile.close(); 
    
    return head;
 }

//randomize vector to generate set of questions to be pulled
// vector<int> randomizeSetTillN(int n,vector<int> Qnums){
    
//vector<int> Qnums{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    
    // vector<int> set = Qnums;
    // vector<int> finalSet;
    
    // srand( (unsigned)time( NULL ) );

    // int i=rand();
    // int j=rand();
    
    // float  vq =(float) rand()*0.0001;
	// int v = floor(vq);

    // for(j=0;j<v;j++){
    //      random_shuffle(set.begin(), set.end());
    
    // }

    // vector<int>::iterator k;

    // for(k=set.begin();k<(set.begin()+n);k++)
    // {
    //     finalSet.push_back(*k); // appending elements in a vector
    // }
    

    // return finalSet;
// }
int getLinkedListLength(LinkedListNode* head) {
    int length = 0;
    LinkedListNode* current = head;
    while (current) {
        length++;
        current = current->next;
    }
    return length;
}

LinkedListNode* selectRandomCommands(LinkedListNode* head, int n) {
    int length = getLinkedListLength(head);

    if (n >= length) {
        return head; // Return the entire list if n is greater or equal to the length
    }

    // Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    vector<int> selectedIndices;
    LinkedListNode* current = head;

    while (selectedIndices.size() <= n) {
        int index = rand() % length;

        // Ensure that the index is unique
        if (find(selectedIndices.begin(), selectedIndices.end(), index) == selectedIndices.end()) {
            selectedIndices.push_back(index);
        }
    }

    LinkedListNode* newHead = nullptr;
    LinkedListNode* tail = nullptr;

    for (int index : selectedIndices) {
        current = head; // Reset the traversal
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        // Create a new node and add it to the result linked list
        insertCommand(newHead, current->command, current->description);

        if (!tail) {
            tail = newHead;
        } else {
            tail = tail->next;
        }
    }

    return newHead;
}

// Question* linkedlist(int TotalQ, vector<int> Qnums, vector<vector<string>> commands, vector<int> order){
 
    // Question* previous = NULL;
    // Question* start = NULL;
	
    // //vector<vector<string>> commands; // 2d vector 
    // //string file = "commands.csv";
    // //commands = readList(file); // Questions stored here

    // vector<int> Qorder = order; // randomizing the order of questions in the CSV file


    // for(auto it: Qorder) // auto- takes the type of the vector (Qorder); iterating over Qorder; it -> iterator (it = Qorder[i])
    // {
    //     Question* question = new Question; // object of struct Question
    //     question->next = NULL;

    //     if (start == NULL)
    //         start = question;

    //     question->cname = commands[it][0];
    //     question->qnum = it;
    //     string def=""; // for the command's definition 
    //     for(int j=1;j<commands[it].size();j++){
    //         def = def + commands[it][j];
    //     }
    //     question->cdef = def;

    //     if (previous != NULL)
    //         previous->next = question; //to store to store the cuurent node in the next of the previous node(previous->next  <---  question)
         
    //     previous = question;//updating previous to current question
		
    // }

    // cout<<endl<<"The questions generated at random are: "<<endl;

    // return start;
    // //for(Question* p = start; p != NULL; p = p->next)
    // //{
    // //    cout<<p->cname<<" "<<p->cdef<<endl;   
    // //}
// }

void rule(){
    cout<<"----------------------------------------------------------------------------------"<<endl;
    cout<<"When Playing the game you will get the number of questions you have asked for."<<endl;
    cout<<"At the end of every question you will get +1 for correct and -1 for wrong answer"<<endl;
    cout<<" and final score will be show n at the end."<<endl;
    cout<<"----------------------------------------------------------------------------------"<<endl;
    cout<<"Press Enter To Continue..."<<endl;
    cin.ignore(INT64_MAX, '\n'); // Eats previous enter press
    cin.get();//exit on enter


}


void game(){
    // vector<int> Qnums{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    
   
    string name;
    cout<<"Enter Player Name:\n";
    cin>>name;
    
    cout<<"Welcome "<<name<<endl;

    int TotalQ = 5;
    while (true) // 5-30
    {
        cout<<"How many questions would you like to attempt(choose between 5-30):\n";
            cin>>TotalQ;
        if (TotalQ<=4 || TotalQ>30) // not 5-30
        {
            cout<<"Invalid number of questions. Please choose between 5 and 30";
        }
        else
            break;
    }

    // vector<int> Qorder = randomizeSetTillN(TotalQ,Qnums); //randomize function is called from here now
     LinkedListNode *selected = selectRandomCommands(construct_List(), TotalQ-1);

    int q = 0; // question number counter
    LinkedListNode *p = selected;
    for (p = p->next; p != NULL; p = p->next) {

        q++;
        cout << "Question number " << q << ":- " << endl;

        cout << "What is the command '" << p->command << "' used for?" << endl;
        int correctOption = rand() % 3;
        LinkedListNode *randomCommand =selectRandomCommands(construct_List(), 2); 

        for(int it=0;it<3;it++){
            if(it==correctOption)
                cout<<it+1<<" "<< p->description <<endl;
            else
            {   
                 cout<<it+1<<" "<< randomCommand->description <<endl;
                randomCommand=randomCommand->next;
            }     
        }

        
    //     // Generate 3 random options, including the correct answer.
    //     unordered_set<LinkedListNode *> options;
    //     options.insert(p);
    //     while (options.size() < 3) {
    //         LinkedListNode *randomCommand = selectRandomCommands(construct_List(), 1);

    //         // Ensure that the random option is distinct from the correct answer and other options.
    //         if (randomCommand->description != p->description &&
    //             options.find(randomCommand) == options.end()) {
    //             options.insert(randomCommand);
    //         }
    //     }

    //     // Copy the options to a vector so that we can iterate over them.
    //     vector<LinkedListNode *> optionVector;
    //     for (auto it = options.begin(); it != options.end(); it++) {
    //         optionVector.push_back(*it);
    //     }

    //     // Shuffle the options.
    //     random_shuffle(optionVector.begin(), optionVector.end());

    //     // Print the options.
    //     for (int i = 0; i < 3; i++) {
    //         cout << i + 1 << ". " << options[i]->description << endl;
    //     }

        int choice = 0;
        cout << endl << "Enter the chosen option: " << endl;
        cin >> choice;
        cout << endl;
        if(correctOption + 1 == choice)
            {cout<<"correct"<<endl;
            score++;}
        else{cout<<"wrong"<<endl; score--;}

    //     // Check the answer.
    //     if (options[choice - 1] == p) {
    //         cout << "Correct! There is no negative marking for choosing the correct option." << endl;
    //     } else {
    //         cout << "Incorrect." << endl;
    //     }
    // }

    // cout << "Your final score is " << score << endl << "Bye!" << endl;


    // Update the player's score in the database.
    updatePlayer(name, TotalQ, score);
    }
}



void menu(){
    cout<<endl;
    cout<<"Welcome the Linux Command MCQ Game."<<std::endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"Please select an option Listed below:"<<std::endl;
    cout<<"1. Game Rules"<<std::endl;
    cout<<"2. Play Game"<<std::endl;
    cout<<"3. Load Previous Game"<<std::endl;
    cout<<"4. Add Command"<<std::endl;
    cout<<"5. Remove Command"<<std::endl;
    cout<<"6. Exit"<<std::endl;
    
    int choice=0;
    cin>>choice;
    switch(choice){
        case 1:
           // rule();
            //menu();
        case 2:
            //game();
            //menu();
        case 3:   
            //findPlayer();         
            //menu();
        case 4:
           // insertCommand();
            ///menu();
        case 5:
            //deleteCommand();
            //menu();
        case 6:

            break;
        default:
            std::cout<<"choice doesnt exist, exiting game.\n";
            break;

}
}

int main(){
    
    //std::cout<<choice<<std::endl;
    //LinkedListNode* head = construct_List();
    game();
    // construct_List(); //Questions stored
    //menu();
    return 0;
}