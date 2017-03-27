# hide
Keep your files locked from the eyes of strangers when you want them to be, recover them when you want to. 
# Set up
1. This is a command line too developed for mac computers. Might work just fine on Linux aswell (have not tested).  

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

