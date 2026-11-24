all: speedTypingTest

speedTypingTest: speedTypingTest.c
	gcc -o speedTypingTest speedTypingTest.c
