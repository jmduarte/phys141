# CLI tutorial



## Current directory
Now you have logged in. How do you know where you are?
Run
```bash
pwd
```
This tells you your `p`resent `w`orking `d`irectory. 

## Listing all the files and directories
Run
```bash
ls
```
to list all the files in the current directory.

## Creating a directory
Now in this directory, you want to create another one with the name `MY_COOL_DIRECTORY`.
Run 
```bash
mkdir MY_COOL_DIR
```
`mkdir` stands for `m`a`k`e `dir`ectory. 
Now, run `ls` and make sure that the directory you created is indeed there.

## Moving around
You want to go into the directory you just created.
Run 
```bash
cd MY_COOL_DIR
``` 
`cd` stands for `c`hange `d`irectory.
What happens if you run jus `cd`? Do it! It takes you to your `home` directory. 

So, if you are ever lost, don't worry, just `cd` and you will be `home`.

## Creating file
Next, we want to create a file named `my_super_cool_file.txt`. 
There are a couple of ways of doing this. If you just want to create an empty file, you can simply `touch my_super_cool_file.txt`.
If you want to write something in the file, you can open it in a cli editor such as `vim` or `emacs`.

## Downloading a file
You found [this](https://raw.githubusercontent.com/ericmichael/cooltxt/master/cool.txt) file on the internet and you absolutely cannot not have it.
Run `wget https://raw.githubusercontent.com/ericmichael/cooltxt/master/cool.txt` to get the file.

## Moving a file
You meant to download the file in parent directory.
Run 
```bash
mv cool.txt ..
```
In linux, `.` represents the current directory, `..` represents the parent directory.

