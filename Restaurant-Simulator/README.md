# Cmpe 250 Assignment 1

There is a restaurant called CMPE250 Family Restaurant in Rumeli Hisarüstü. This restaurant is
located between the North and South Campus of Bogazici University. You are expected to assign each
incoming customer to a table by considering the following constraints:

* This restaurant has n number of tables, where n is an integer between 5 to 50 ( 5 ≤ n ≤ 50 ).
* There are two entrances to this restaurant, where one of them is located at the north side of the
restaurant, and the other one is located at the south side of the restaurant.
* Tables are named incrementally from north to south.
  - For instance, if n = 12, [north entrance –> 1 2 3 4 5 6 7 8 9 10 11 12 <– south entrance].
![image](https://user-images.githubusercontent.com/56366573/187289819-9ab8864a-8079-4ed5-ba5f-05bf3a0bbaf1.png)

* The smallest table number is 1.
* If a customer enters the restaurant via the north entrance, he/she will sit to the closest empty
table to the north entrance.
* If a customer enters the restaurant via the south entrance, he/she will sit to the closest empty
table to the south entrance.
* Initially, each table is empty.
Here are some additional information to ease your job:
* Tables in the restaurant are for one person each, and customers arrive as single.
* You don’t need to consider the case where a customer arrives and cannot find an empty table. In
our test scenarios, whenever a customer arrives, there will already be an empty table for that
person.
To implement this project, you will be provided some code written by the assistants, and you are
going to implement the missing part.
The files you will be provided are: Table.h, Table.cpp, Restaurant.h, Restaurant.cpp, and main.cpp.
The file you should fill in is: Restaurant.cpp. You only need to complete the execute() method. So, for
this project any code written outside Restaurant.cpp will be useless.
## Input
Your code will be tested with a text file (i.e., input.txt). This text file consists of two lines.
* In the first line, total number of tables ( n ) is stated in the integer format (e.g., 15, 23).
* In the second line, there is a list of strings, where each string is separated with a comma.
  - “N” means that customer arrives from the north entrance.
  - “S” means that customer arrives from the south entrance.
  - If there is an integer (let’s call it i ) in the second line, it means that customer, who
was sitting in table i , leaves.
The input file will not send a customer into the restaurant if it is already full. Moreover, i will always
refer to a table occupied by a customer.

**NOTE:** The main.cpp as provided already receives the input in this format.

## Output
Your code is expected to produce a text file (i.e., output.txt) as an output. This text file should output
each table’s final assignment status, where 0 represents an empty table, and 1 represents an
occupied table.

**NOTE:** The main.cpp as provided already prints the output in this format.
The code as provided also produces some output to terminal for debugging purposes, which is fine.
You can print anything you like onto terminal. The output to the file output.txt is all that counts.
