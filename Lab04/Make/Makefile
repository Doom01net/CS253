# This is a Makefile.  Its purpose is to create the program “small”.
#
# The rules, below, indicate what depends on what, and how to build
# things when they get out-of-date.  It is VERY important to know that
# what looks like eight leading spaces is really a leading tab
# character.  Leading spaces won’t work--it MUST be a tab character.
#
# For the following questions, do the command if there is one,
# and then answer the question.  If you need another line for you
# answer, continue it on the next line.
#
# As an example, I’ve already answered (1), which has nothing to do
# with anything else in this lab.
#
# Question 1 is worth 0.09 points; questions 2–14 are worth 0.07
# points each.
#
#  1) Command:  date +%A
#     Question: Describe the output of that command.
#     Answer:   It’s today’s day of the week.
#
#  2) Command:  make
#     Question: Describe what happens.  Don’t just write the commands;
#     		describe what each command does.
#     Answer: make compiles and links the files to make an executable   
# 
#  3) Command:  ./small
#     Question: What is the output?  Reproduce the output exactly.
#     Answer:   Hi from main at main.cc:15
#		        Hi from foo at foo.cc:14
#
#  4) Command:  make
#     Question: Why did nothing much happen?
#     Answer:  Because no changes were made to source files, thus make is saying that the program 'small' is up to date, meaning to changes need to be done  
#
#  5) Command:  rm small; make
#     Question: What got remade, and why?
#     Answer:   deleted small exec and ran make again, 'small' is remade
#
#  6) Command:  rm foo.o; make 
#     Question: What got remade, and why?
#     Answer:   foo.o got deleted, the whole program got remade, .o file and 'small' exec file
#
#  7) Command:  make clean 
#     Question: What did that do?
#     Answer:   make ran, but the .o file got deleted as unecassary
#
#  8) Command:  make 
#     Question: What got remade, and why?
#     Answer: make ran, the program fully got remade.
#
#  9) Question: Why does main.o depend on foo.h?
#		I know that it’s because the Makefile says so.
#		Why was that dependency put into the Makefile?
#     Answer:  the dependency main.o depends on foo.h is in the makefile because the delcaration header file is important and declares something we need. 
#
# 10) Command:  Create a new function bar() in bar.cc & bar.h,
# 		similar to foo.cc.  Change main.cc to call the new
# 		bar() function, and type “make”.
#     Question: Why did it fail?
#     Answer:   because Makefile doesn't specify the bar.* files
#
# 11) Command:  Fix the Makefile; verify with “make” until it compiles.
#     Question: Describe your changes.  Don’t just show the changed
#     		lines--describe the purpose of each change.
#     Answer:   I fixed the Makefile to have bar where ever there is foo.
#
# 12) Command:  Uncomment the CXXFLAGS= line, and type “make”.
#     Question: Why didn't anything happen?
#     Answer:   Because there were no changes made to source file
#
# 13) Command:  Force a rebuild with: make clean; make 
#     Question: What’s new about the commands executed?
#     Answer:   g++ ran with a lot of extra flags.
#
# 14) Command: 	make clean; ls -l clean
#     Question: The target is “clean”, but no file “clean” got created.
#     		Why not?
#     Answer:   because clean is a command.
#
# For extra fame & glory (but no extra points):
#
# 15) Command:  Consult the make manual at
# 		https://www.gnu.org/software/make/manual/make.html
#		and improve this Makefile by using $@ in the rule
#		that creates “small” itself.

# The CXX variable contains the name of the C++ compiler.  You can’t
# have plus signs in a Make variable, so X is a rotated plus sign.
CXX=g++

CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

small: main.o bar.o
	$(CXX) $(CXXFLAGS) main.o bar.o -o small

main.o: main.cc bar.h
	$(CXX) $(CXXFLAGS) -c main.cc

bar.o: bar.cc bar.h
	$(CXX) $(CXXFLAGS) -c bar.cc

clean:
	-rm -f small *.o
