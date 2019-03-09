# Some-Useful-Programs

Just some exercise.

So don't treat them seriously.  :)

---

Chenxi Yu

2019.3.3

# Description 

## 1.calculator

A calculator supporting + - * / ^ operators.

## 2.the 8 puzzle

This program solves the 8 puzzle. \
Given a 3 * 3 board. each grid contains a unique number in 0~8. \
You can swap 0 with its neighbor grid in four directions. (up, down, left, right) \
Can you get the board below? \
 \
1 2 3 \
4 5 6 \
7 8 0 \
 \
If impossible, print "impossible" to the standard output file. \
 \
Derived from problem 1077 on poj (link: http://poj.org/problem?id=1077 )

## 3.sudoku

Sudoku solver.

Test case usage: \
\
`$ ./sudoku_solver < sudoku_case`

## 4.the missionaries and cannibals

### Description
The missionaries and cannibals problem is usually stated as follows: Three missionaries and three cannibals are on one side of a river, along with a boat that can hold one or two people. Find a way to get everyone to the other side, without ever leaving a group of missionaries in one place (including the boat) outnumbered by the cannibals in that place. Now the problem has been extended to be more complicated. There are m missionaries and m cannibals who want to cross the river. And the boat is also enlarged to be capable of supporting n people. In order to make all of them cross the river safely what is the least number of steps? Notice that when the boat goes across the river there must be at least one missionary or cannibal on the boat.

### input
The input consists of only one line, and is made of two positive number m and n, where m ≤ 1000 and n ≤ 100.
### output
Output the least number of steps needed. If the problem can't be solved, print -1 as the result.

### link

http://aiintro.openjudge.cn/practice/1/
