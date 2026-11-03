# Compiler Design Labs (C++)

C++ programs written for the Compiler Design course at AIUB. They cover the front end of a compiler: lexical analysis of source text, simple syntax checks, regular expressions and automata, and intermediate code generation.

## Mid

- `Example1.cpp`, `Example2.c`: check whether a string is a valid identifier.
- `Example2.cpp`: detects single-line and multi-line comments.
- `Example3.cpp`: a small lexical analyser that labels operators, keywords, numbers and valid or invalid identifiers in a line of code.
- `Example4.cpp`, `Example5.cpp`: writing and reading text files.
- `Example6.cpp`, `22-47046-1(task).cpp`: tokenise a source file and list the keywords it uses.
- `example7.cpp`: reports lines that are missing a closing `;`.
- `example8.cpp`: reports missing `;` and mismatched `()`, `{}` and `[]` brackets by line.
- `22-47046-1.cpp`: lists the user-defined functions and operators in a C++ file.
- `LabPerformence.cpp`: lists the unique operators and preprocessor lines in a C++ file.
- `info.txt`, `sourcecode.txt`, `semicolne.txt`, `NewFile.txt`, `NewFile1.txt`: sample input files.

## Final

- `expression.cpp`: checks whether a string matches the regular expression `(ab|c)*`.
- `NFA.cpp`, `FinalPerformence.cpp`, `FinalPerformence.c`: build an NFA transition table from a regular expression.
- `NFAtoDFA.cpp`: converts an NFA with epsilon moves to a DFA by subset construction.
- `Interm code generator.cpp`: generates three-address code with temporaries for arithmetic expressions, handling `*` and `/` before `+` and `-`.
- `example9.cpp`, `22-47046-1.cpp`: validate identifiers in declarations and the expressions after `return` in a C++ source file.
- `example7.cpp`, `example8.cpp`: the semicolon and bracket checks from the Mid set.
- `lexical_analyzer_from_txtFile.txt`: C++ source (saved as text) for a keyword finder that reads code from a file.
- `program.cpp`: sample input program.

## Build

Each `.cpp` file is a standalone program:

```bash
g++ "file.cpp" -o program
```

Several programs read input from absolute Windows paths (for example `C://Study Matirial//...`). Point them at the sample files in the same folder before running.
