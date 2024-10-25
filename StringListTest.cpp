// cmpt225a2undo.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "StringList.h"
using std::string;
using std::cout;
using std::endl;
bool test(bool nextTest, bool result);
void printResult(bool result);
bool testDefaultConstructor();
bool testCopyConstructor();
bool testAssignmentOperator();
bool testSizeEmpty();
bool testGet();
bool testIndex();
bool testContains();
bool testSet();
bool testInsertBefore();
bool testInsertBack();
bool testInsertFront();
bool testRemove();
bool testRemoveAll();
bool testEquals();
int main()
{
 bool result = true;
 result = test(testDefaultConstructor(), result);
 result = test(testCopyConstructor(), result);
 result = test(testAssignmentOperator(), result);
 result = test(testSizeEmpty(), result);
 result = test(testGet(), result);
 result = test(testIndex(), result);
 result = test(testContains(), result);
 result = test(testSet(), result);
 result = test(testInsertBefore(), result);
 result = test(testInsertBack(), result);
 result = test(testInsertFront(), result);
 result = test(testRemove(), result);
 result = test(testRemoveAll(), result);
 result = test(testEquals(), result);
 if (result) {
cout << "All tests passed" << endl;
}
 else {
cout << "Some tests failed" << endl;
}
}
bool test(bool nextTest, bool result)
{
 if (!nextTest) {
 result = false;
 }
 return result;
}
void printResult(bool result)
{
 if (result) {
cout << ": passed" << endl;
}
 else {
cout << ": failed" << endl;
}
}
bool testDefaultConstructor()
{
 cout << "test default constructor";
 bool result = true;
 StringList lst;
 result = test(lst.empty(), result);
 result = test(lst.size() == 0, result);
 result = test(lst.toString() == "{}", result);
 printResult(result);
 return result;
}
bool testCopyConstructor()
{
 cout << "test copy constructor";
 bool result = true;
 StringList lst;
 StringList lst2(lst);
 result = test(lst == lst2, result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 result = test(lst.size() == 3, result);
 result = test(lst.get(0) == "A", result);
 result = test(lst.get(1) == "B", result);
 result = test(lst.get(2) == "C", result);
 result = test(lst.toString() == "{\"A\", \"B\", \"C\"}", result);
 StringList lst3(lst);
 result = test(lst == lst3, result);
 printResult(result);
 return result;
}
bool testAssignmentOperator()
{
 cout << "test assignment operator";
 bool result = true;
 StringList lst;
 StringList lst2;
 // lst2 = lst;
 result = test(lst == lst2, result);
 result = test(lst.empty(), result);
 result = test(lst2.empty(), result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 result = test(lst.size() == 3, result);
 result = test(lst.get(0) == "A", result);
 result = test(lst.get(1) == "B", result);
 result = test(lst.get(2) == "C", result);
 result = test(lst.toString() == "{\"A\", \"B\", \"C\"}", result);
 lst2 = lst;
 result = test(lst == lst2, result);
 result = test(lst2.size() == 3, result);
 result = test(lst2.get(0) == "A", result);
 result = test(lst2.get(1) == "B", result);
 result = test(lst2.get(2) == "C", result);
 result = test(lst2.toString() == "{\"A\", \"B\", \"C\"}", result);
 printResult(result);
 return result;
}
bool testSizeEmpty()
{
 cout << "test size empty";
 bool result = true;
 StringList lst;
 result = test(lst.empty(), result);
 result = test(lst.size() == 0, result);
 lst.insertBack("A");
 result = test(!lst.empty(), result);
 result = test(lst.size() == 1, result);
 lst.insertBack("B");
 result = test(!lst.empty(), result);
 result = test(lst.size() == 2, result);
 lst.insertBack("C");
 result = test(!lst.empty(), result);
 result = test(lst.size() == 3, result);
 for (int i = 0; i < 10; i++)
 {
 lst.insertBack("D");
 }
 result = test(!lst.empty(), result);
 result = test(lst.size() == 13, result);
 printResult(result);
 return result;
}
bool testGet()
{
 cout << "test get";
 bool result = true;
 StringList lst;
 lst.insertFront("A");
 lst.insertFront("B");
 lst.insertFront("C");
 result = test(lst.get(0) == "C", result);
 result = test(lst.get(1) == "B", result);
 result = test(lst.get(2) == "A", result);
 lst.remove(1);
 result = test(lst.get(0) == "C", result);
 result = test(lst.get(1) == "A", result);
 lst.remove(0);
 result = test(lst.get(0) == "A", result);
 printResult(result);
 return result;
}
bool testIndex()
{
 cout << "test index";
 bool result = true;
 StringList lst;
 result = test(lst.index("A") == -1, result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 result = test(lst.index("A") == 0, result);
 result = test(lst.index("B") == 1, result);
 result = test(lst.index("C") == 2, result);
 result = test(lst.index("D") == -1, result);
 lst.remove(1);
 result = test(lst.index("A") == 0, result);
 result = test(lst.index("C") == 1, result);
 result = test(lst.index("B") == -1, result);
 result = test(lst.index("D") == -1, result);
 lst.remove(0);
 result = test(lst.index("C") == 0, result);
 result = test(lst.index("A") == -1, result);
 result = test(lst.index("B") == -1, result);
 result = test(lst.index("D") == -1, result);
 printResult(result);
 return result;
}
bool testContains()
{
 cout << "test contains";
 bool result = true;
 StringList lst;
 result = test(!lst.contains("A"), result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C"); // lst == {"A", "B", "C"}
 result = test(lst.contains("A"), result);
 result = test(lst.contains("B"), result);
 result = test(lst.contains("C"), result);
 result = test(!lst.contains("D"), result);
 lst.remove(1); // lst == {"A", "C"}
 result = test(lst.contains("A"), result);
 result = test(lst.contains("C"), result);
 result = test(!lst.contains("B"), result);
 result = test(!lst.contains("D"), result);
 lst.remove(0); // lst == {"C"}
 result = test(lst.contains("C"), result);
 result = test(!lst.contains("A"), result);
 result = test(!lst.contains("B"), result);
 result = test(!lst.contains("D"), result);
 printResult(result);
 return result;
}
bool testSet()
{
 cout << "test set";
 bool result = true;
 StringList lst;
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 result = test(lst.toString() == "{\"A\", \"B\", \"C\"}", result);
 lst.set(0, "D");
 result = test(lst.toString() == "{\"D\", \"B\", \"C\"}", result);
 lst.set(1, "E");
 result = test(lst.toString() == "{\"D\", \"E\", \"C\"}", result);
 lst.set(2, "F");
 result = test(lst.toString() == "{\"D\", \"E\", \"F\"}", result);
 printResult(result);
 return result;
}
bool testInsertBefore()
{
 cout << "test insert before";
 bool result = true;
 StringList lst;
 lst.insertBefore(0, "A");
 result = test(lst.toString() == "{\"A\"}", result);
 lst.insertBefore(0, "B");
 result = test(lst.toString() == "{\"B\", \"A\"}", result);
 lst.insertBefore(1, "C");
 result = test(lst.toString() == "{\"B\", \"C\", \"A\"}", result);
 lst.insertBefore(1, "D");
 result = test(lst.toString() == "{\"B\", \"D\", \"C\", \"A\"}", result);
 lst.insertBefore(4, "E");
 result = test(lst.toString() == "{\"B\", \"D\", \"C\", \"A\", \"E\"}", 
result);
 printResult(result);
 return result;
}
bool testInsertBack()
{
 cout << "insert back";
 bool result = true;
 StringList lst;
 lst.insertBack("A");
 result = test(lst.toString() == "{\"A\"}", result);
 lst.insertBack("B");
 result = test(lst.toString() == "{\"A\", \"B\"}", result);
 lst.insertBack("C");
 result = test(lst.toString() == "{\"A\", \"B\", \"C\"}", result);
 printResult(result);
 return result;
}
bool testInsertFront()
{
 cout << "insert front";
 bool result = true;
 StringList lst;
 lst.insertFront("A");
 result = test(lst.toString() == "{\"A\"}", result);
 lst.insertFront("B");
 result = test(lst.toString() == "{\"B\", \"A\"}", result);
 lst.insertFront("C");
 result = test(lst.toString() == "{\"C\", \"B\", \"A\"}", result);
 printResult(result);
 return result;
}
bool testRemove()
{
 cout << "remove";
 bool result = true;
 StringList lst;
 lst.insertBack("A");
 lst.remove(0);
 result = test(lst.empty(), result);
 result = test(lst.toString() == "{}", result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.remove(0);
 result = test(lst.get(0) == "B", result);
 result = test(lst.toString() == "{\"B\"}", result);
 lst.remove(0);
 result = test(lst.empty(), result);
 result = test(lst.toString() == "{}", result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 lst.remove(1);
 result = test(lst.toString() == "{\"A\", \"C\"}", result);
 lst.removeAll();
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 lst.remove(2);
 result = test(lst.toString() == "{\"A\", \"B\"}", result);
 lst.removeAll();
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 lst.remove(0);
 result = test(lst.toString() == "{\"B\", \"C\"}", result);
 printResult(result);
 return result;
}
bool testRemoveAll()
{
 cout << "remove all";
 bool result = true;
 StringList lst;
 result = test(lst.empty(), result);
 result = test(lst.toString() == "{}", result);
 lst.insertBack("A");
 lst.removeAll();
 result = test(lst.empty(), result);
 result = test(lst.toString() == "{}", result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.removeAll();
 result = test(lst.empty(), result);
 result = test(lst.toString() == "{}", result);
 lst.insertBack("A");
 lst.insertBack("B");
 lst.insertBack("C");
 lst.removeAll();
 result = test(lst.empty(), result);
 result = test(lst.toString() == "{}", result);
 printResult(result);
 return result;
}
bool testEquals()
{
 cout << "equals";
 bool result = true;
 StringList lst1;
 StringList lst2;
 result = test(lst1 == lst2, result);
 result = test(lst2 == lst1, result);
 lst1.insertBack("A");
 result = test(lst1 != lst2, result);
 result = test(lst2 != lst1, result);
 lst2.insertBack("A");
 result = test(lst1 == lst2, result);
 result = test(lst2 == lst1, result);
 lst1.insertBack("B");
 result = test(lst1 != lst2, result);
 result = test(lst2 != lst1, result);
 lst2.insertBack("B");
 result = test(lst1 == lst2, result);
 result = test(lst2 == lst1, result);
 printResult(result);
 return result;
