# nm-otool

This 42 curriculum projects aims to create two executables emulating the behaviour of the ```nm``` and ```otool``` commands.

## Main take away of the projet

* Understanding of mach-o and elf file structure
* Use of the mach-o library
* Parsing of binary file
* Structure and organisation of the project : code factoring

## How to make it work ?

First git clone the repository on your computer than go into the folder.

Clone my library for the project : [libft](https://github.com/xemxav/libft).

```make | make ft_nm | make ft_otool```

### Usage :

Both executable accept 64 and 32 bits object files.


``` ./ft_nm [file1] [file2] [file...]```

Will output the equivalent of the ```nm``` command. 
From man page:
```
The nm utility shall display symbolic information appearing in the
object file, executable file, or object-file library named by file.
If no symbolic information is available for a valid input file, the
nm utility shall report that fact, but not consider it an error
condition.
```

``` ./ft_oool [file1] [file2] [file...]```

Will output the equivalent of the ```otool -t``` command. From man page :

```
The   otool  command  displays  specified  parts  of  object  files  or
libraries
-t : Display the contents of the (__TEXT,__text) section. 
```

If no object files are listed as arguments, ```ft_nm``` and ```ft_otool``` assumes the file is a.out.