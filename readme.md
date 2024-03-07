# Duong's compiler
## About
	A C-based programming language.
## Require
	Install CC (C compiler)
	Install Make
## Build
	$ ./make
After that you'll get your compiler in `bin` directory.
## Command
	# from the project's directory
	$ cd bin		# or add the bin directory to your system path
	
	# Example
	
	$ ./duong --help				# help
	$ ./duong --version				# get current version
	$ ./duong <filename>				# compile with default output name
	$ ./duong <filename> -o <output> 		# compile with custom output name


## Syntax
### Welcome
This is your basic programming code in duong:
```
main()
	write "Hello, World!"	# You can comment the code like this
###
Or like this
###
```	
Like C/C++, the program should start at the `main()` function.
You `must` tab before `write` function because it's a statement in `main()` function.
### Data types
	There are some basic data types provided in duong: int, float, string, char.
### Array declaration
	int a[10]			# not have a default value, you should initialize it
	
	print a[i]			# access i-th element of array
### Assignment
	int n = 5	# declare n = 5
	let n = 7	# assign n = 7
### Operators
	+, -, *, /, % 	(math operator for int and float)
	+		(string concentration, ex: "a" + "b" == "ab")
	+=, -=, *=, /=, %=
### Input
	main()
		int n
		read n			# read n
		
		string s
		read n, s		# read n then read s
### Function
How you declare and call functions:
```
foo(string s)				# a procedure
	write s ' ' 123 "!!"		# use spaces to seperate data in write command
	write s ' '123"!!"		# in some special case don't need space

calc(int a, int b) => int		# a function with an integer return-value
	return a + b

main()
	foo("Hello, World!")
	# print: Hello, World! 123!!
	print calc(1, 2)
	# print: 3
```
### Flow control
#### Comparison
	Operators: ==, !=, <, >, <=, >=
`Int` and `Float` should be compared by value, string is compared by lexicographic order.
#### If, else if, else
	main()
		int n
		read n
		if n == 5
			# do something
		else if n < 5
			# do something
		else
			# do something
#### while
	int a[100]
	
	main()
		int n
		read n
		int i = 0
		while i < n
			read a[i]
			let i = i + 1