# Brainfuck Interpreter
___

Brainfuck encoder, decoder and compiler made in C.

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
        -d, --decode    Decode the brainfuck code to ASCII
        -e, --encode    Encode the ASCII input into brainfuck code
        -c, --compile   Compile the brainfuck code to C
        -h, --help      Print this message
```

> [!NOTE]
> This program always print out in stdout. Remember that to create file with the output you can use redirections as explained below or chain programms using `xargs` \
> See in the [Examples](#examples) section

# Examples

Remember that brainfuck only allow the following characters : `'<'`, `'>'`, `','`, `'.'`, `'+'`, `'-'`, `'['` and `']'`. Spaces and some other separators are allowed but skipped, as they don't belong to brainfuck's characters.

* Encode
```shell
$ ./brainfuck -e "Hello World"
+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------.
$ ./brainfuck -e examples/hello_world.txt
+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------.
```

* Decode 
```shell
$ ./brainfuck -d "+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------."
Hello World
$ ./brainfuck -d examples/hello_world.bf
Hello World
$ ./bin/brainfuck -e examples/hello_world.txt | xargs ./bin/brainfuck -d 
Hello World
```

* Compile
```shell
$ ./brainfuck -c examples/hello_world.bf > temp.c
$ make temp
$ ./temp
Hello World
```
