# Brainfuck Interpreter
___

Brainfuck coder and decoder made in C.

- [Brainfuck Interpreter](#brainfuck-interpreter)
- [Install](#install)
- [Run](#run)
- [Example](#example)

# Install

To download the repo, you can either download the .zip file for this project, or use git commands as bellow :
```shell
git clone https://github.com/GouruRK/brainfuck-interpreter.git
```

# Run

Compile it using the `make` command :
```shell
cd brainfuck-interpreter
make
```

Once compile, use the following command to show the runtime options
```shell
./brainfuck --help
```
Such as bellow
```
./brainfuck [-d, --decode sentence] [-e, --encode sentence] [-h, --help]
        [-d, --decode] Indicate to decode the given sentence
                Require a non null string that contains a brainfuck sentence
                A sentence must be composed by the characters : '<', '>', ',', '.', '+', '-', '[' and ']'
        [-e, --encode] Indicate to encode the given sentence
                Require a non null sentence
        [-h, --help] Print this message
```

# Example

Remember that brainfuck only allow the following characters : `'<'`, `'>'`, `','`, `'.'`, `'+'`, `'-'`, `'['` and `']'`. Spaces (`' '`) are allowed but skipped, as they don't belong to brainfuck's characters.

* Encoding
```shell
./brainfuck -e "Hello World"
+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------.
```

* Decoding 
```shell
./brainfuck -d "+++++++[>++++++++++<-]>++.<++[>++++++++++<-]>+++++++++.+++++++..+++.>+++[>++++++++++<-]>++.<+++++[>++++++++++<-]>+++++.<++[>++++++++++<-]>++++.+++.------.--------."
Hello World
```
