###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother JonesL, CS235
# Author:
#     Devin Cenatiempo
# Summary:
#     Implements the deque class (stack + queue)
#     Also uses the deque class in a Lab line simulation
# Time:
#     It took me about 5 hours to create this program
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
