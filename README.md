# cpp-chat
###A C++ sockets chat program.

Francisco Aguilera
falven@rams.colostate.edu
829884287

##Building:
The project uses CMake to generate a Makefile. The provided Makefile should work fine on department machines, however, in case you would like to run the program elsewhere, or re-generate the Makefile:

*The project requires out-of-source builds. Create a directory somewhere outside the source to hold the build files.
`mkdir ~/Desktop/cpp-chat-build`

*Then simply run Cmake with the proper generator and source directory.
`cmake -G "Unix Makefiles" ~/Desktop/cpp-chat/`

*Change directories to the build tree.
`cd ~/Desktop/cpp-chat-build/`

*Make the project.
`make`

*Run the project.
`./chat ...`

##Invocation:
`chmod a+x chat // if not built, make the file executable by all`
`./chat [-h] -p port -s ip`

##Examples:
*```Franciscos-Mbp:cpp-chat-build Falven$ ./chat -h
Usage: ./chat [-h] -p port -s ip```

*`Franciscos-Mbp:cpp-chat-build Falven$ ./chat -s 10.10.10.3 -p 54321`

*`Franciscos-Mbp:cpp-chat-build Falven$ ./chat -p 54321 -s 10.10.10.3`

##Questions:

1. Q: The following were questions asked to the TA throughout the project.
I'm having trouble getting my local IP and a random port at the same time. It seems to me that getaddrinfo requires that either node or service, but not both, may be NULL. When iterating the results with a specific port, I only get loopback addresses.

1. R: While using getaddrinfo() keep the first argument as NULL [which is basically 'node']. And you can pass a port to be "0", this will allocate one of the port number from the pool of free ports.

1. A: This ended up being incorrect, after much searching and struggling through this issue, I found that I needed to pass my machine's hostame to getaddrinfo, as collected from gethostname, instead of NULL.

2. Q: The spec says that we need to send 16 bit binary of the version (457) and then the 16 bit binary of the size of the message. However, when you say 16 bit binary do you mean pseudo binary? Like each character you send from the buffer is a 1 and 0? Or do you mean to serialize the 16 bit numbers to the buffer?

2. R: You can use "int16_t" data type. (Which give you 16 bit integer on any system) Then you can copy this value to char buffer using "memcpy"

2. A: Serialize the 16 bit numbers to the buffer.

3. Q: Do we need to send the total size of the message including the header (version and size)? Or just the size of the message portion.

3. R: Size field should specify size of message only.

3. A: The string length is the length of the message in bytes.

4. Q: How would you de-serialize the values from the buffer, I am using memcpy again, but I am getting an EXC_BAD_ACCESS error when writing to my variables.

4. R: ...

4. A: Don't remember what was going on, but it was fixed in the end. :)
