#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

//List of classes used in this Programme

class TTADT;

class course;
class student;

class studentPointerNode;
class coursePointerNode;

class slot;
class day;
class time;


//A helper class Where I have some function, like stringLength, getline, etc
class helper
{
public:
	static int stringLength(char* c)
	{
		int l = 0;
		if (c != 0)
		{
			for (int i = 0; c[i] != '\0'; i++)
				l++;
		}
		return l;
	}

	static char* getStringFromBuffer(char* c)
	{
		char* str = 0;
		if (c != 0)
		{
			int len = stringLength(c);
			if (len != 0)
			{
				str = new char[len + 1];
				int i = 0;
				for (; c[i] != '\0'; i++)
					str[i] = c[i];
				str[i] = '\0';
			}
		}
		return str;
	}

	static bool compareString(char* a, char* b)
	{
		int l = 0;
		for (; a[l] != '\0' && b[l] != '\0'; l++)
		{
			if (b[l] != a[l])
				return false;
		}
		if (a[l] == '\0' && b[l] == '\0')
			return true;
		else
			return false;
	}

	static bool searchString(char* a, char* b)
	{
		int l = 0;
		int m = 0;

		for (; a[l] != '\0' && b[m] != '\0'; m++)
		{
			if (a[l] == b[m])
				l++;
			else
				l = 0;
		}

		if (a[l] == '\0')
			return true;
		else
			return false;
	}

	//Searching '#' in the string and removing it if found, helpful in searching 3-Hour session in timeTable 
	static bool searchTime(char* b)
	{
		int m = 0;
		bool flag = false;


		for (; b[m] != '\0'; m++)
		{
			if (b[m] == '#')
			{
				flag = true;
				break;
			}
		}
		m--;
		b[m] = '\0';

		return flag;
	}

	//Function that will read data from the file until one of the delimiters is reached, an alternate of getline() function
	static char* readData(ifstream & fin, char delimator1, char delimator2 = 0)
	{
		char* n = new char[100];

		int i = 0;

		fin >> n[i];

		while (n[i] != delimator1 && n[i] != delimator2)
		{
			i++;
			fin.get(n[i]);
		}
		n[i] = '\0';
		return getStringFromBuffer(n);
	}

	//Checking whther the first roll number that is stored in string is greater than the other or not
	static bool greaterRoll(char* str1, char* str2)
	{
		int l1 = stringLength(str1);
		int l2 = stringLength(str2);

		if (l2 > l1)
			return true;
		else if (l2 < l1)
			return false;
		else if (l1 == l2)
		{
			int i = 0;

			while (str1[i] != '\0')
			{
				if (str2[i] > str1[i])
					return true;
				else if (str2[i] < str1[i])
					return false;
				i++;
			}
		}
	}
};


//Defination of all the classes
class TTADT {
public:
	course* coursesList;
	course* lastCourse;

	student* studentList;
	student* lastStudent;

	day* daysList;
	day* lastDay;

	TTADT();
	void loadTimeTable(ifstream&);
	void loadStudentInfo(ifstream&);

	void courseCheck(char*, char*, course*&);
	void printCourseTimings(char*, char*);
	void printTimeTable();
	void printTimeTableWithStudentList();

	void printStudentList();
	void printStudentListWithListOfCourses();
	void findStudent(char*, student*&);

	void printStudentTimeTable(char*);
	void printCourse(day*, time*, char*);
	void saveClashes();

	void searchAndPrintCourse();
	void searchAndPrintStudent();
	void searchAndPrintSlot();

	void myPrintStudentListWithListOfCourses(student*);
	void myPrintStudentList(student*);
	void mySaveClashes(student*, ofstream&);

	void insertStudent(student*);
	void insertCourse(course*);
	void insertDay(day*);

	void checkDay(char*, day*&);
	void checkClash(student*, ofstream&);

	//A recursive function to destroy a tree after the implimentation of programme
	void studentDestructor(student*);
	~TTADT();
};

class student
{
public:
	char* rollNo;
	char* name;

	student* left;
	student* right;

	coursePointerNode* coursesList;
	coursePointerNode* lastCourse;

	void addACourse(course*);

	void print();
	void printStudentWithCoursesList();

	void checkClash(ofstream&);
	void printClash(ofstream&);

	student();
	student(char*, char*);

	~student();
};

class course
{
public:
	char* subject;
	char* section;

	slot* firstSlot;  //Pointer pointing to the slots occupied by the course
	slot* secondSlot;

	course* nextCourse;

	studentPointerNode* studentList;
	studentPointerNode* lastStudent;

	void linkStudent(student* s);

	course();
	course(char*, char*);

	void print();
	void printCourseWithStudentList();
	void printCourseName();

	bool checkSlots(day*, time*, char*);
	void slotChecking(slot*, slot*, student*, course*, ofstream&);

	void checkClash(student*, course*, ofstream&);
	void printClashes(ofstream&);

	~course();
};

class coursePointerNode
{
public:
	course* cPointer;
	coursePointerNode* nextCPointer;

	coursePointerNode();

	void checkClash(student*, coursePointerNode*, ofstream&);

	void print();
	void printClashes(ofstream&);

	~coursePointerNode();
};

class studentPointerNode
{
public:
	student* sPointer;
	studentPointerNode* nextSPointer;

	studentPointerNode();

	void print();
	~studentPointerNode();
};

class slot
{
public:
	day* d;
	char* venue;

	time* startTime;
	time* endTime;

	slot(char*, day*, time*, time*);

	bool checkIt(day*, time*, char*);
	bool checkClash(slot*);

	void print();
	void printClash(ofstream&);

	~slot();
};

class day
{
public:
	char* name;
	day* nextDay;

	day();
	day(char*);

	void print();
	void printClash(ofstream&);

	~day();
};

class time
{
public:
	int hours;
	int minutes;

	time(int, int);
	void print();

	time* IncrementTime(int);

	bool less(time*& t2);
	bool greater(time*& t2);

	void printClash(ofstream&);
	bool checkEquality(time*);

	~time();
};


//Definition of the functions of all the classes

studentPointerNode::~studentPointerNode()
{
	sPointer = 0;
}

day::~day()
{
	if (name != 0)
		delete[] name;
}

time::~time()
{

}

coursePointerNode::~coursePointerNode()
{

}

void time::printClash(ofstream & fout)
{
	fout << "(" << hours << ":" << minutes << ")";
}

//Function checking whether the first time is less than the second or not 
bool time::less(time * &t2)
{
	if (hours < t2->hours)
		return true;
	else if (hours == t2->hours)
	{
		if (minutes < t2->minutes)
			return true;
	}
	return false;
}

bool time::greater(time * &t2)
{
	if (hours > t2->hours)
		return true;
	else if (hours == t2->hours)
	{
		if (minutes >= t2->minutes)
			return true;
	}
	return false;
}

void day::printClash(ofstream & fout)
{
	fout << name;
}

day::day()
{
	name = 0;
	nextDay = 0;
}

void day::print()
{
	cout << name;
}

day::day(char* d = 0)
{
	name = helper::getStringFromBuffer(d);
	nextDay = 0;
}

void time::print()
{
	cout << hours << ":" << minutes;
}

//Function is taking an object of time and increasing required number of minutes in it and returning the same object
time* time::IncrementTime(int increment)
{
	minutes = minutes + increment;

	int count = 0;
	while (minutes >= 60)
	{
		minutes = minutes - 60;
		count++;
	}
	hours = hours + count;

	return this;
}

time::time(int h = 8, int m = 0)
{
	hours = h;
	minutes = m;
}

void slot::printClash(ofstream & fout)
{
	d->printClash(fout);
	startTime->printClash(fout);
}

bool slot::checkClash(slot * s2)
{
	if ((startTime->greater(s2->startTime)) && (startTime->less(s2->endTime)))
		return true;
	else
		return false;
}

//Checing the equality of two objects of time
bool time::checkEquality(time * t)
{
	if ((hours == t->hours) && (minutes == t->minutes))
		return true;
	else
		return false;
}

//checking whether a slot is equal to other or not, helping function of seraching a course by room, time and day
bool slot::checkIt(day * da, time * t, char* room)
{
	if (da == d)
	{
		if (t->checkEquality(startTime))
		{
			if (helper::compareString(room, venue))
				return true;
		}
	}
	return false;
}

slot::~slot()
{
	if (venue != 0)
		delete[]venue;

	if (startTime != 0)
		delete startTime;

	if (endTime != 0)
		delete endTime;
}

void slot::print()
{
	d->print();
	cout << ", ";
	startTime->print();
	cout << "-";
	endTime->print();

	cout << ", " << venue;
}

slot::slot(char* ven, day * da, time * startT, time * endT)
{
	startTime = new time(startT->hours, startT->minutes);
	endTime = new time(endT->hours, endT->minutes);

	d = da;
	venue = helper::getStringFromBuffer(ven);
}

void course::printClashes(ofstream & fout)
{
	fout << subject << "(" << section << ")\t";
}

void course::printCourseName()
{
	cout << "Subject:\t" << subject << "\nSection:\t" << section;
}

//Checking whether input data matches with any of the slot of a course
bool course::checkSlots(day * d, time * t, char* room)
{
	bool flag1 = false;
	bool flag2 = false;

	if (firstSlot)
		flag1 = firstSlot->checkIt(d, t, room);

	if (secondSlot)
		flag2 = secondSlot->checkIt(d, t, room);

	if (flag1 || flag2)
	{
		printCourseName();
		return true;
	}
	return false;
}

void coursePointerNode::printClashes(ofstream & fout)
{
	cPointer->printClashes(fout);
}

void coursePointerNode::print()
{
	if (cPointer)
		cPointer->print();
}

coursePointerNode::coursePointerNode()
{
	cPointer = 0;
	nextCPointer = 0;
}

student::student()
{
	rollNo = 0;
	name = 0;

	left = 0;
	right = 0;

	coursesList = 0;
	lastCourse = 0;
}

//Adding a new curse in the list
void student::addACourse(course * c)
{
	coursePointerNode* temp = new coursePointerNode;
	temp->cPointer = c;

	if (coursesList == 0)
	{
		coursesList = temp;
		lastCourse = temp;
	}
	else
	{
		lastCourse->nextCPointer = temp;
		lastCourse = temp;
	}
}

void studentPointerNode::print()
{
	if (sPointer)
		sPointer->print();
}

studentPointerNode::studentPointerNode()
{
	sPointer = 0;
	nextSPointer = 0;
}

//Linking a student with his/her course
void course::linkStudent(student * s)
{
	studentPointerNode* temp = new studentPointerNode;
	temp->sPointer = s;

	if (studentList == 0)
	{
		studentList = temp;
		lastStudent = temp;
	}
	else
	{
		lastStudent->nextSPointer = temp;
		lastStudent = temp;
	}
}

student::~student()
{
	delete[] rollNo;
	delete[] name;

	if (coursesList != 0)
	{
		coursePointerNode* curr = coursesList;
		coursePointerNode* prevCurr = 0;

		while (curr != 0)
		{
			prevCurr = curr;
			curr = curr->nextCPointer;
			delete prevCurr;
		}
	}
}

course::~course()
{
	if (subject != 0)
		delete[] subject;

	if (section != 0)
		delete[] section;

	if (firstSlot != 0)
		delete firstSlot;

	if (secondSlot != 0)
		delete secondSlot;

	if (studentList != 0)
	{
		studentPointerNode* curr = studentList;
		studentPointerNode* prevCurr = 0;

		while (curr != 0)
		{
			prevCurr = curr;
			curr = curr->nextSPointer;
			delete prevCurr;
		}
	}
}

void course::printCourseWithStudentList()
{
	if (subject)
		cout << subject;
	if (section)
		cout << "(" << section << ")\n";

	if (firstSlot)
		firstSlot->print();
	if (secondSlot)
	{
		cout << " || ";
		secondSlot->print();
	}
	cout << "\n";

	studentPointerNode* curr = studentList;

	int count = 1;

	while (curr != 0)
	{
		cout << count << "-\t";
		curr->print();
		count++;
		cout << "\n";
		curr = curr->nextSPointer;
	}
}

void course::print()
{
	cout << subject << "(" << section << ")\n";

	if (firstSlot)
		firstSlot->print();
	if (secondSlot)
	{
		cout << " || ";
		secondSlot->print();
	}
}

course::course()
{
	subject = 0;
	section = 0;

	firstSlot = 0;
	secondSlot = 0;

	nextCourse = 0;

	studentList = 0;
	lastStudent = 0;
}

course::course(char* sub, char* sec)
{
	subject = helper::getStringFromBuffer(sub);
	section = helper::getStringFromBuffer(sec);

	firstSlot = 0;
	secondSlot = 0;

	nextCourse = 0;

	studentList = 0;
	lastStudent = 0;
}

student::student(char* r, char* n)
{
	rollNo = helper::getStringFromBuffer(r);
	name = helper::getStringFromBuffer(n);

	left = 0;
	right = 0;

	coursesList = 0;
	lastCourse = 0;
}

void student::print()
{
	cout << name << " (" << rollNo << ")";
}

void student::printStudentWithCoursesList()
{
	cout << name << " (" << rollNo << ")";

	coursePointerNode* curr = coursesList;
	cout << "\n";
	int count = 1;

	while (curr != 0)
	{
		cout << "\n" << count << "- ";
		curr->print();
		count++;
		curr = curr->nextCPointer;
	}
}

//A recursive function
void TTADT::myPrintStudentListWithListOfCourses(student * list)
{
	if (!list)
		return;

	myPrintStudentListWithListOfCourses(list->left);
	list->printStudentWithCoursesList();
	cout << "\n\n";
	myPrintStudentListWithListOfCourses(list->right);
}

void TTADT::printStudentListWithListOfCourses()
{
	myPrintStudentListWithListOfCourses(studentList);
}

//Searching a student with Roll No. and assigning it's address to "s" pointer
void TTADT::findStudent(char* r, student * &s)
{
	student* curr = studentList;

	while (curr != 0)
	{
		if (helper::compareString(curr->rollNo, r))
		{
			s = curr;
			break;
		}

		if (helper::greaterRoll(r, curr->rollNo))
			curr = curr->left;
		else
			curr = curr->right;
	}
}


int totalStudents = 1;

void TTADT::myPrintStudentList(student * list)
{
	if (!list)
		return;

	myPrintStudentList(list->left);

	cout << totalStudents << "-\t";
	list->print();
	cout << "\n";
	totalStudents++;

	myPrintStudentList(list->right);
}

void TTADT::printStudentList()
{
	totalStudents = 1;
	myPrintStudentList(studentList);
	cout << "\n";
}

//Searching Course with Name and Section then printing it if found
void TTADT::printCourseTimings(char* name, char* section)
{
	course* curr = coursesList;

	bool flag = false;
	while (curr != 0)
	{
		if (helper::searchString(name, curr->subject))
		{
			if (helper::searchString(section, curr->section))
			{
				curr->print();
				flag = true;
				break;
			}
		}
		curr = curr->nextCourse;
	}

	cout << "\n\n";

	if (flag == false)
		cout << "Sorry!! We could not find any Course with this name in the list. Please make sure that spelling are correct and trye again.\n";
}

void TTADT::printStudentTimeTable(char* rollNo)
{
	student* curr = studentList;
	bool flag = false;

	while (curr != 0)
	{
		if (helper::compareString(rollNo, curr->rollNo))
		{
			curr->printStudentWithCoursesList();
			flag = true;
			break;
		}
		else if (helper::greaterRoll(rollNo, curr->rollNo))
			curr = curr->left;
		else
			curr = curr->right;
	}

	if (flag == false)
		cout << "Sorry!! We could not find any student associated with this Roll No. Please Check the roll no and try again.\n";
	cout << "\n\n";
}

//A recursive function to destroy the Tree of Student List
void TTADT::studentDestructor(student * s)
{
	if (s != 0)
	{
		studentDestructor(s->left);
		studentDestructor(s->right);
		delete s;
	}
}

TTADT::~TTADT()
{
	if (studentList != 0)
		studentDestructor(studentList);

	if (coursesList != 0)
	{
		course* curr = coursesList;
		course* prevCurr = 0;

		while (curr != 0)
		{
			prevCurr = curr;
			curr = curr->nextCourse;
			delete prevCurr;
		}
	}

	if (daysList != 0)
	{
		day* curr = daysList;
		day* prevCurr = 0;

		while (curr != 0)
		{
			prevCurr = curr;
			curr = curr->nextDay;
			delete prevCurr;
		}
	}
}

void TTADT::printTimeTableWithStudentList()
{
	course* curr = coursesList;

	int count = 1;
	while (curr != 0)
	{
		cout << count << "- ";
		curr->printCourseWithStudentList();
		count++;
		curr = curr->nextCourse;
		cout << "\n";
	}
}

void TTADT::printTimeTable()
{
	course* curr = coursesList;

	int count = 1;
	while (curr != 0)
	{
		cout << count << "- ";
		curr->print();
		count++;
		curr = curr->nextCourse;
		cout << "\n\n";
	}
}

//Loading all the data of the file named "Registration Data.txt"
void TTADT::loadStudentInfo(ifstream & fin)
{
	while (!fin.eof())
	{
		char* rollNo = helper::readData(fin, ',');

		if (!fin.eof())
		{
			char* name = helper::readData(fin, ',');
			char* sub = helper::readData(fin, ',');
			char* sec = helper::readData(fin, ',');

			course* coursePointer = 0;

			courseCheck(sub, sec, coursePointer);

			student* studentInList = 0;

			findStudent(rollNo, studentInList); //checking whether student exists in the list or not

			if (studentInList)
			{
				if (coursePointer)
				{
					coursePointer->linkStudent(studentInList);
					studentInList->addACourse(coursePointer);
				}
			}
			else
			{
				student* temp = new student(rollNo, name);

				if (coursePointer)
				{
					temp->addACourse(coursePointer);
					coursePointer->linkStudent(temp);
				}
				insertStudent(temp);
			}

			delete[] name;
			delete[] sub;
			delete[] sec;
		}
		delete[] rollNo;
	}
}

//Inserting a new student in the List(Tree)
void TTADT::insertStudent(student * s)
{
	if (studentList == 0)
		studentList = s;
	else
	{
		student* curr = studentList;
		student* prevCurr = 0;

		while (curr != 0)
		{
			prevCurr = curr;
			if (helper::greaterRoll(s->rollNo, curr->rollNo))
				curr = curr->left;
			else
				curr = curr->right;
		}

		if (helper::greaterRoll(s->rollNo, prevCurr->rollNo))
			prevCurr->left = s;
		else
			prevCurr->right = s;
	}
}

//Seraching a course with it's name and section and asigning(if found) it's address to "courseCheck"
void TTADT::courseCheck(char* sub, char* sec, course * &courseCheck)
{
	course* curr = coursesList;

	while (curr != 0)
	{
		if (helper::compareString(sub, curr->subject))
		{
			if (helper::searchString(sec, curr->section))
			{
				courseCheck = curr;
				break;
			}
		}
		curr = curr->nextCourse;
	}
}

TTADT::TTADT()
{
	coursesList = 0;
	lastCourse = 0;

	studentList = 0;
	lastStudent = 0;

	daysList = 0;
	lastDay = 0;
}

//Searching a day from the list of working days of university, and pointing "s" to it's address
void TTADT::checkDay(char* dayName, day * &s)
{
	day* curr = daysList;

	while (curr != 0)
	{
		if (helper::compareString(dayName, curr->name))
		{
			s = curr;
			break;
		}
		curr = curr->nextDay;
	}
}

//Inserting a new day in the list of days
void TTADT::insertDay(day * d)
{
	if (daysList == 0)
	{
		daysList = d;
		lastDay = d;
	}
	else
	{
		lastDay->nextDay = d;
		lastDay = d;
	}
}

//Loading all the data of the file named "TimeTable.txt"
void TTADT::loadTimeTable(ifstream & fin)
{
	for (int i = 0; i < 5; i++)
	{
		char* da = new char[20];
		da = helper::readData(fin, ',');

		char* delimator = new char[2];
		delimator[0] = '+';
		delimator[1] = '\0';

		day* d = 0;
		checkDay(da, d);
		if (d == 0)
		{
			d = new day(da);
			insertDay(d);
		}

		for (int j = 0;; j++)
		{
			char* venue = new char[15];
			venue = helper::readData(fin, ',');

			time* startTime = new time(8, 0);
			time* endTime = new time(8, 0);

			for (int k = 0;; k++)
			{
				char* subject = new char[30];
				char* section = new char[30];

				subject = helper::readData(fin, '(', ',');

				endTime->IncrementTime(80);

				if (subject)
				{
					if (helper::searchString(delimator, subject))
						break;

					if (helper::searchTime(subject))
						endTime->IncrementTime(90);

					section = helper::readData(fin, ')');

					char* comma = new char[1];
					fin >> comma[0];
					delete[] comma;

					course* courseInList = 0;
					courseCheck(subject, section, courseInList);       //Checking whether course already exists in courses list or not

					if (courseInList)
						courseInList->secondSlot = new slot(venue, d, startTime, endTime);
					else
					{
						course* temp = new course(subject, section);
						temp->firstSlot = new slot(venue, d, startTime, endTime);

						insertCourse(temp);
					}
				}

				endTime->IncrementTime(10);   //10 minute break after a session

				startTime->hours = endTime->hours;
				startTime->minutes = endTime->minutes;

				delete[] subject;
				delete[] section;
			}
			char* n = helper::readData(fin, ',');

			if (n)
				break;

			delete[] venue;
		}
		delete[] da;
	}
}

//Inserting a course in the list of courses
void TTADT::insertCourse(course * c)
{
	if (coursesList == 0)
	{
		coursesList = c;
		lastCourse = c;
	}
	else
	{
		lastCourse->nextCourse = c;
		lastCourse = c;
	}
}

//Searching a course by day, time, and room 
void TTADT::printCourse(day * d, time * t, char* room)
{
	course* curr = coursesList;
	bool flag = false;
	while (curr != 0)
	{
		if (curr->checkSlots(d, t, room))
		{
			flag = true;
			break;
		}
		curr = curr->nextCourse;
	}
	if (flag == false)
		cout << "There is no class at the given Slot.\n";
}

void student::printClash(ofstream & fout)
{
	fout << name << "\t" << rollNo << "\t";
}

//Checking whether a slot have a clash with other, if yes printing the data
void course::slotChecking(slot * s1, slot * s2, student * s, course * c, ofstream & fout)
{
	if (s1 && s2)
	{
		if (s1->d == s2->d)
		{
			if (s1->checkClash(s2))
			{
				s->printClash(fout);

				printClashes(fout);
				fout << "\t";
				c->printClashes(fout);

				s1->printClash(fout);
				fout << "\n";
			}
		}
	}
}

//Checking the clash of two courses
void course::checkClash(student * s, course * c2, ofstream & fout)
{
	slotChecking(firstSlot, c2->firstSlot, s, c2, fout);
	slotChecking(firstSlot, c2->secondSlot, s, c2, fout);
	slotChecking(secondSlot, c2->firstSlot, s, c2, fout);
	slotChecking(secondSlot, c2->secondSlot, s, c2, fout);
}

void coursePointerNode::checkClash(student * s, coursePointerNode * c2, ofstream & fout)
{
	if (cPointer && c2->cPointer)
		cPointer->checkClash(s, c2->cPointer, fout);
}

void student::checkClash(ofstream & fout)
{
	coursePointerNode* curr = coursesList;

	while (curr != 0)
	{
		coursePointerNode* curr2 = curr->nextCPointer;

		while (curr2 != 0)
		{
			curr->checkClash(this, curr2, fout);
			curr2 = curr2->nextCPointer;
		}
		curr = curr->nextCPointer;
	}
}

void TTADT::checkClash(student * s, ofstream & fout)
{
	if (s)
		s->checkClash(fout);
}

//A recursive function to check and save clashes of all the students
void TTADT::mySaveClashes(student * list, ofstream & fout)
{
	if (!list)
		return;

	mySaveClashes(list->left, fout);
	checkClash(list, fout);
	mySaveClashes(list->right, fout);
}

void TTADT::saveClashes()
{
	student* curr = studentList;
	ofstream fout;

	fout.open("Clashes.txt");

	mySaveClashes(studentList, fout);

	fout.close();

	cout << "Clashes are saved in the file named clashes.txt. Please check it in the Project Folder.\n\n";
}

void TTADT::searchAndPrintCourse()
{
	char* courseName = new char[40];
	char* section = new char[40];

	cout << "\nSubject:\t";
	cin.getline(courseName, 40);
	cout << "Section:\t";
	cin.getline(section, 40);

	cout << "\n";
	printCourseTimings(courseName, section);

	delete[] courseName;
	delete[] section;
}

void TTADT::searchAndPrintStudent()
{
	char* rollNo = new char[8];
	cout << "Roll No:\t";
	cin.getline(rollNo, 8);
	cout << "\n\n";
	printStudentTimeTable(rollNo);

	delete[] rollNo;
}

void TTADT::searchAndPrintSlot()
{
	char* da = new char[15];
	int hour;
	int minutes;
	time* tim = 0;
	char* classRoom = new char[20];

	day* d = 0;

	cout << "Day:\t";
	cin.getline(da, 15);

	checkDay(da, d);
	if (d)
	{
		cout << "\nTime(Hours):\t";
		cin >> hour;
		cout << "Time(Minutes):\t";
		cin >> minutes;
		cout << "\nClass Room:\t";
		cin >> classRoom;

		tim = new time(hour, minutes);
		cout << "\n";
		printCourse(d, tim, classRoom);
	}
	else
		cout << "Day name is not in the list of working days of University. Please, Try Again.\n";
	cout << "\n\n";

	delete[] da;
	delete[] classRoom;

	if (tim != 0)
		delete tim;
}

void main()
{
	ifstream fin1;
	ifstream fin2;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 1);

	TTADT t;

	fin1.open("Time Table.txt");

	if (fin1)
	{
		t.loadTimeTable(fin1);
		fin1.close();

		fin2.open("Registration data.txt");

		if (fin2)
		{
			t.loadStudentInfo(fin2);
			fin2.close();
			cout << "\n\n\n\n\n\n\t--------------------------------------------------------------------------------------------\n";
			cout << "\t-******************************************************************************************-\n";
			cout << "\t-******************************************************************************************-\n";
			cout << "\t-******************************************************************************************-\n";
			cout << "\t-\t ******MADE BY NAEEM AKHTAR(17L-4262) AND ZURAIN HAIDER(16L-4186)******            -\n";
			cout << "\t-********************COURSE INSTRUCTOR: SIR AAMIR WALI*************************************-\n";
			cout << "\t--------------------------------------------------------------------------------------------\n";
			cout << "\t-\t ******SECTION: CS-A(SPRING-2019)**************************************            -\n";
			cout << "\t-******************************************************************************************-\n";
			cout << "\t-******************************************************************************************-\n";
			cout << "\t-******************************************************************************************-\n";
			cout << "\t--------------------------------------------------------------------------------------------\n";
			Sleep('10');
			system("cls");

			//Both files are now opened and we can move forward
		start:
			SetConsoleTextAttribute(hConsole, 1);
			cout << "\t\tPROGRAM FUNCTIONALITIES \n\n";
			cout << "\t\t1- List of Courses In This Smester\n";
			cout << "\t\t2- list of Students Registered\n";
			cout << "\t\t3- List of Courses With Students Registered there\n";
			cout << "\t\t4- list of students With courses registed\n\n";
			cout << "\t\t5- Enter a Course to Search it's TimeTable\n";
			cout << "\t\t6- Enter the Roll No. of  a Student to Print His/Her TimeTable\n";
			cout << "\t\t7- Enter the Time Table of a slot to Print the Course\n";
			cout << "\t\t8- Generate File Having Clashes of the Students\n";
			cout << "\t\t9- Exit\n";

			int input;

			cout << "\n\t\tInput:\t";
			cin >> input;
			cin.ignore(1, '\n');

			system("cls");

			if (input == 1)
			{
				SetConsoleTextAttribute(hConsole, 6);
				t.printTimeTable();         //List of all the Courses in this Smester with TimeTable
				goto start;
			}
			else if (input == 2)
			{
				SetConsoleTextAttribute(hConsole, 6);
				t.printStudentList();       //List of all the students registered in this smester
				goto start;
			}
			else if (input == 3)
			{
				SetConsoleTextAttribute(hConsole, 6);
				t.printTimeTableWithStudentList(); //List of all the Courses in this Smester with TimeTable and list of students in each cours
				goto start;
			}

			else if (input == 4)
			{
				SetConsoleTextAttribute(hConsole, 6);
				t.printStudentListWithListOfCourses(); //List of all the students with the list of courses registered
				goto start;
			}
			else if (input == 5)
			{
				SetConsoleTextAttribute(hConsole, 6);
				//Enter the Name and Section of a course to print it's Timmings
				t.searchAndPrintCourse();
				goto start;
			}

			else if (input == 6)
			{
				SetConsoleTextAttribute(hConsole, 6);
				//Enter the Roll No of a Student to print his/her TimeTable
				t.searchAndPrintStudent();
				goto start;
			}

			else if (input == 7)
			{
				SetConsoleTextAttribute(hConsole, 6);
				// Enter Day, Time and Venue of a course to print the course
				t.searchAndPrintSlot();
				goto start;
			}
			else if (input == 8)
			{
				SetConsoleTextAttribute(hConsole, 6);
				t.saveClashes();
				goto start;
			}
			else if (input == 9)
			{
				goto Exit;
			}
			else
			{
				cout << "Invalid Selection. Please, Try again\n\n";
				goto start;
			}
		}
		else
			cout << "Sorry!! \"Registration data.txt\" can't be opened.\n";
	}
	else
		cout << "Sorry!! \"Time Table.txt\"  can't be opened.\n";

Exit:
	cout << "\n\n";
}