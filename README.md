# What am I looking at here
Basically a program that makes files unreadable and back to readable at will. 
# Set up
1. This is a command line tool using some UNIX system commands. Developed and used on a mac but might work just fine on Linux aswell (but I have not verified that).  

2. Type 'make' in this directory.

3. Type 'sudo mv hide_these_files /usr/local/bin/hide_these_files' or exchange '/usr/local/bin' for any other path 
under the '$PATH' environment variable.

# Use
Tips: The environment variable '$PWD' can be used, it will be translated into the directory where you are located in the terminal. 

After you have done the set up:

Type: 'hide_these_files_please [directory] [secret-key]' 

The files will be modified into '.encrypted' files. To decrypt them use the exact same command. 

[directory]: A path to the directory where the file or the files you want encrypted/decrypted reside.
[secret-key]: A key used to encrypt/decrypt your files (must not included spaces..).

