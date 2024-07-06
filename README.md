# Brainfuck Interpreter
___

Brainfuck coder and decoder made in C.

- [Brainfuck Interpreter](#brainfuck-interpreter)
- [Install](#install)
- [Run](#run)
- [Examples](#examples)

# Install

To download the repo, you can either download the .zip file for this project, or use git commands as bellow :
```shell
git clone https://github.com/GouruRK/brainfuck-interpreter.git
```

# Run

Compile it using the `make` command which produce "bin/brainfuck":
```shell
cd brainfuck-interpreter
make
```

Once compile, use the following command to show the runtime options
```shell
./bin/brainfuck --help
```
Such as bellow
```
Brainfuck interpreter

./brainfuck [OPTIONS ...] <FILE | INPUT>
        -d, --decode    Indicate to decode the given input
        -e, --encode    Indicate to encode the given input
        -h, --help      Print this message
```

# Examples

Remember that brainfuck only allow the following characters : `'<'`, `'>'`, `','`, `'.'`, `'+'`, `'-'`, `'['` and `']'`. Spaces (`' '`) are allowed but skipped, as they don't belong to brainfuck's characters.

* Encoding
```shell
$ ./brainfuck -e "Hello World"
+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------.
$ ./brainfuck -e examples/hello_world.txt
+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------.
```

* Decoding 
```shell
$ ./brainfuck -d "+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------."
Hello World
$ ./brainfuck -d examples/hello_world.bf
Hello World
```
