# If we try to run make after the changes, only the target say_hello will be executed. 
# That's because only the first target in the makefile is the default target. 
# Often called the default goal, this is the reason you will see 'all' 
# as the first target in most projects. It is the responsibility of 'all' to call other targets. 
# We can override this behavior using a special phony target called .DEFAULT_GOAL.
# Let's include that at the beginning of our makefile:

.DEFAULT_GOAL := build

# As the name suggests, the phony target .DEFAULT_GOAL can run only one target at a time. 
# This is why most makefiles include 'all' as a target that can call as many targets as needed.
# all: say_hello build

build:
	gcc -Wall -lm serp_general.c -o serpg && ./serpg && python ../grafico-serp.py genfractal.dat
