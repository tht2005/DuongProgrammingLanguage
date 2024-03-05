# Duong's compiler
## About
	My basic compiler for learning.
## Build
	# Install Make first
	$ ./make
After that you'll get your compiler in `bin` directory.
## Run
	# from the project's directory
	$ cd bin
	$ duong <filename>


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
	There are some basic data types provided in duong: int, string, float, array.
### Array declaration
	array<int> a(10)		# declare an array with size of 10
	array<int> a(10, 0)		# declare an array with size of 10, all value equal 0
	
	print a[i]			# access i-th element of array
### Assignment
	int n = 5	# declare n = 5
	let n = 7	# assign n = 7
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
	write s, ' ', 123, "!!"	# use ',' seperator in write command

calc(int a, int b) => int		# a function with integer return-value
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
	main()
		int n
		read n
		array<int> a(n)
		int i = 0
		while i < n
			read a[i]
			let i = i + 1