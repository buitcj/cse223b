servers sync upon start up - if they can't find a server that has been initialized then they begin, otherwise they pull data from the other server

two-ish phase commit implemented

vector timestamps in place

the tribble set is a json-parsed string that contains 5 tribbles.  
the user info stores where the current set is and who the user is subscribed to.  Because the current set number always increases, knowing the current set, we can always find all previous sets

instructions for running have'nt changed, syntax is the same - but make sure to use a unique ID starting at 0 for the servers (i'm actually not sure if it matters, but I thought I remember implmementing something related)


I've copied in the include directory so that you will be able to compile

make sure to place the include directory at the same level as the src directory or else it won't be placed correctly
