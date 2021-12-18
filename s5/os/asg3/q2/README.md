## IPC Using Message Queues

Interprocess communication between unrelated processes

The ftok , msgget , msgget and msgrevc commands are used to create and use the message queues

# Files:

```
ci.c        # Course Instructor program
st.c        # Student program
ta.c        # Teaching assistant program
```

# Commands to run:

```bash
make                # Compiles all 3 programs
./ci                # Enter 5 marks to be sent to student and TA
./st                # View all 5 students marks (in a seperate terminal)
./ta                # Calculated grades and average mark and returns it to CI
make clean          # Removes object and binary files
```
