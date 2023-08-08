#include<bits/stdc++.h>
#include<vector>

using namespace std;

//Global variables and arrays
int current_id;
bool vis[1000] = {false};
int mark[1000];
string students_answer[1000];

//Forward declaration of classes
class Student;
class StudentRegistration;
class Teacher;
class Exam;

//Declaration of commonly used functions
void main_menu();
void student_menu(int);

class Teacher
{
    string Owner_name;
    string password;
    vector<string> Quiz;
    vector<string> written;
    vector<char> quiz_answers;
    int quiz_indx, written_indx;

public:
    Teacher()
    {
        Owner_name = "ShafinAhmed";
        password = "welldone";

        //Pre settled quiz questions
        Quiz.push_back("How many bits is commonly called as one byte --> A - Six bits B - Eight bits C - Twelve bits D - Fifteen bits");
        quiz_answers.push_back('B');
        Quiz.push_back("Main circuit board in a computer is: --> (A) Decoder(B) Highlight(C) Select(D) Mother board");
        quiz_answers.push_back('D');

        //Pre settled written questions
        written.push_back("Discuss the importance of object oriented programming");
        written.push_back("Give the definition of a friend function");

        quiz_indx = 2;
        written_indx = 2;
    }
    ~Teacher(){}

    void add_questions(int op) //For adding questions by Teacher
    {
        if(op == 1){
            string s;
            cout << "          Enter the quiz question -->" << endl;
            fflush(stdin);
            getline(cin,s);
            fflush(stdin);
            Quiz.push_back(s);
            cout << "          Enter the quiz answer -->  ";
            fflush(stdin);
            char c;
            cin >> c;
            fflush(stdin);
            quiz_answers.push_back(c);
            quiz_indx++;
        }
        else if(op == 2){
            string s;
            cout << "          Enter the written question -->" << endl;
            fflush(stdin);
            getline(cin,s);
            fflush(stdin);
            written.push_back(s);
            cout <<  "Written Question " << written_indx+1 << " successfully added" << endl;
            written_indx++;
        }
    }
    void see_all_quiz_questions() //For displaying all quizes
    {
        int i;
        cout << endl;
        for(i=0; i<Quiz.size(); i++){
            cout << "Quiz " << i+1 << ": " << Quiz[i] << endl;
        }
        cout<<endl;
    }
    void see_all_written_questions() //For displaying all written question
    {
        int i;
        cout << endl;
        for(i=0; i<written.size(); i++)
            cout << "Written Question " << i+1 << ": " << written[i] << endl;
        cout << endl;
    }

    void see_submissions() //For showing Teacher the subimission of the students and assigning mark
    {
        cout << "Whose solution do you want to see?  -> Roll = ";
        int id;
        cin >> id;
        cout << "The solution of roll " << id << " is " << endl;
        cout <<  students_answer[id] << endl;
        cout << endl;
        cout << "Give Mark --> ";
        int m;
        cin >> m;
        mark[id] = m;
        vis[id] = true;
        cout << m << " Marks has been given to roll " << id << " successfully" << endl;
    }

    friend void exam(Teacher, int);
};

Teacher T;

void exam(Teacher t, int id)
{
    int op, i;
    char c;
    cout << "1.Quiz                 2.Written" << endl;
    cin >> op;
    if(op == 1){
        cout << ".....................QUIZ QUESTION....................." << endl;
        int score = 0;
        for(i=0; i<t.Quiz.size(); i++){
            cout << "Q " << i+1 << ":" << t.Quiz[i] << endl;
            cout << "Your answer -->  ";
            cin >> c;
            fflush(stdin);
            if(c == t.quiz_answers[i]){
                cout << "         Correct!" << endl;
                score++;
            }
            else{
                cout<< "           Wrong answer ! Correct answer is = " << t.quiz_answers[i] << endl;
            }
        }
        cout << "CONGRATS !!! YOUR SCORE IS = " << score << endl;
        cout << "\n.....................QUIZ COMPLETE.....................\n" << endl;
    }
    else if(op == 2){
        cout << "\n.....................WRITTEN QUESTIONS....................."<< endl;
        for(i=0; i<t.written.size(); i++)
            cout<< "Question No " << i+1 << " : " << t.written[i] << endl;
        cout << "Now submit your answer within 1000 words -->" << endl;
        string ans;
        fflush(stdin);
        getline(cin,ans);
        fflush(stdin);
        students_answer[id] = ans;
        cout << "\nYour solution has been submitted.\n" << endl;
    }
}

class Student{
    int roll;
    string email, username, password;
public:
    Student(){}

    Student(int i, string e, string u, string p)
    {
        roll = i;
        email = e;
        username = u;
        password = p;
    }

    ~ Student(){}

    void display()
    {
        cout << "Email = " << email << ", UserName = " << username << ", Password = " << password << endl;
    }
    friend class StudentRegistration;
    friend void StudentLogin(StudentRegistration);
};

class StudentRegistration
{
    Student s[1000];
    int total;

public:
    StudentRegistration()
    {
        //Registaring 2 demo students by default
        s[0].roll = 1, s[0].email = "first.student@gmail.com", s[0].username = "Tisha", s[0].password = "firstpassword";
        s[1].roll = 2, s[1].email = "second.student@gmail.com", s[1].username = "Titli", s[1].password = "secondpassword";
        total = 2;
    }
    ~StudentRegistration(){}
    void reg() //Registration Process
    {
        int roll;
        string username, password, email;
        cout << "Enter the following informations - " << endl;
        cout << "Roll = "; cin >> roll;
        cout << "Email = "; fflush(stdin); getline(cin,email);
        fflush(stdin);
        cout << "Username = "; getline(cin,username);
        fflush(stdin);
        cout << "Set a password = "; getline(cin, password);
        fflush(stdin);

        Student obj(roll, email, username, password);
        s[total] = obj;
        total++;

    }

    void display_all()
     {
         cout << "\n" << "Information of all the students:" << endl;
         int i, j;
         for(i=0; i<total; i++)
         {
             cout << "Student " << i+1 << ": ";
             s[i].display();
         }
         cout << endl;
     }

     friend class Student;
     friend void StudentLogin(StudentRegistration);

};

StudentRegistration user;

void StudentLogin(StudentRegistration temp)
{
    string u, p;
    cout << "Enter  -->" << endl;
    cout << "Username = ";
    fflush(stdin);
    getline(cin, u);
    fflush(stdin);
    cout << "Password = ";
    getline(cin, p);
    fflush(stdin);
    int j, index = -1, op;

    for(j=0; j<temp.total; j++)
    {
        if(temp.s[j].username == u && temp.s[j].password == p){
            index = j;
        }
    }
    if(index < 0){
        cout << "Invalid username or password" << endl;
        main_menu();
    }
    else
    {
        cout << "                  LOGIN SUCCESSFULL" << endl;
        int current_id = temp.s[index].roll;
        cout << "..................WELCOME ROLL " << current_id << ".................." << "\n" << endl;
        student_menu(current_id);
    }

}

void student_menu(int id)
{
    cout << "           1.Take an exam              2.See Result                3.Logout" << endl;
    int op;
    cin >> op;
    if(op == 1){
        exam(T, id);
        student_menu(id);
    }else if(op == 2){
        if(vis[id])
        {
            cout << "Congrats !! The Mark of your written exam is = " << mark[id] << endl;
        }
        else
            cout << "Your written paper has not been evaluated yet.\n" << endl;
        student_menu(id);
    }else if(op == 3){
        main_menu();
    }else{
        cout << "Invalid operation..Closing Program" << endl;
        exit(1);
    }
}

void func_register()
{
    user.reg();

    cout << "\n" << "           REGISTRATION SUCCESSFULL" << endl;
}

void teacher_menu()
{
    cout << "           1.Assign Mark           2.Set Questions                    3.Logout" << endl;
    int op;
    fflush(stdin);
    cin >> op;
    if(op == 1)
    {
        T.see_submissions();
        teacher_menu();
    }
    else if(op == 2)
    {
        cout << "           1.Add Quizes            2.Add written questions" << endl;
        int option;
        fflush(stdin);
        cin >> option;
        if(option == 1){
            while(1)
            {
                cout << "1.Add   2.Stop adding ->" << endl;
                cin >> op;
                if(op == 2)
                    break;
                else if(op == 1)
                    T.add_questions(option);
                else{
                    cout << "Invalid operation..Closing program" << endl;
                    exit(1);
                }
            }
            cout << "Displaying all the quizes set for the students ---"<< endl;
            T.see_all_quiz_questions();
            cout << endl;
        }
        else if(option == 2){
            while(1)
            {
                cout << "      1.Add              2.Stop adding" << endl;
                cin >> op;
                if(op == 2)
                    break;
                else if(op == 1)
                    T.add_questions(option);
                else{
                    cout << "Invalid operation..Closing program." << endl;
                    exit(1);
                }
            }
            cout << "Displaying all the written questions set for the students ---"<< endl;
            T.see_all_written_questions();
            cout << endl;
        }
        fflush(stdin);
        teacher_menu();
    }
    else if(op == 3)
    {
        fflush(stdin);
        main_menu();
    }
    else{
        cout << "Invalid operation..Closing program." << endl;
        exit(1);
        //teacher_menu();
    }
}

void main_menu()
{
    cout << "1.Student Register        2.Student Login               3.Teacher Login              4.Close" << endl;
    int op;
    cin >> op;
    if(op == 1){
        func_register();
        main_menu();
    }else if(op == 2){
        StudentLogin(user);
    }else if(op == 3){
        string s, p;
        cout << "Enter your Handle and password ---" << endl;
        cout << "Owner_name = ";
        fflush(stdin);
        getline(cin, s);
        fflush(stdin);
        cout << "Password = ";
        getline(cin, p);
        fflush(stdin);
        if(s == "Mr Safin Ahmmed" && p == "welldone"){
            cout << "\n                  WELCOME TO YOUR TEACHER ACCOUNT"<< endl;
            teacher_menu();
        }
        else
        {
            cout << "Incorrect OwnerName or password" << endl;
            main_menu();
        }
    }else if(op == 4){
        exit(1);
    }
}


int main()
{
    cout << "\n------------------------------------WELCOME----------------------------\n" << endl;
    main_menu();
}
