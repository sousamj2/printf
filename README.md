*This project was created as part of the 42 curriculum by marisous*

# Table of Contents

1. [Description](#description)
   1. [Format specifier grammar](#format-specifier-grammar)
   2. [Supported conversions](#supported-conversions)
   3. [Supported flags (bonus)](#supported-flags-bonus)
   4. [Internal architecture](#internal-architecture)
2. [Instructions](#instructions)
   1. [Building the library](#building-the-library)
   2. [Linking against it](#linking-against-it)
   3. [Makefile rules](#makefile-rules)
   4. [Testing](#testing)
3. [Resources](#resources)
   1. [Tutorials & references](#tutorials--references)
   2. [AI usage](#ai-usage)
   3. [System setup](#system-setup)


---


# Description

The goal of this project is to re-implement the standard `printf(3)` function from the C library as `ft_printf`.  The function accepts a format string and a variadic number of arguments, writes the formatted output to stdout, and returns the total number of characters written — matching the behaviour described in the POSIX specification.

The implementation is compiled into a static archive, `libftprintf.a`, which bundles the printf sources together with the functions from the previous `libft` project (located in the `libft/` sub-directory).


## Format specifier grammar

```
%[flags][width][.precision]conversion
```

| Component    | Description |
|---|---|
| `flags`      | Zero or more of: `-`, `0`, `#`, `+`, ` ` (space) |
| `width`      | A decimal integer specifying the minimum field width |
| `.precision` | A `.` followed by a decimal integer; for strings: max chars printed; for numbers: min digits |
| `conversion` | One mandatory letter from the table below |


## Supported conversions

| Specifier | Argument type      | Output |
|---|---|---|
| `c`       | `int`              | Single character |
| `s`       | `char *`           | Null-terminated string (`(null)` for `NULL`) |
| `p`       | `void *`           | Pointer address in `0x…` hex (`(nil)` for `NULL`) |
| `d` / `i` | `int`              | Signed decimal integer |
| `u`       | `unsigned int`     | Unsigned decimal integer |
| `x`       | `unsigned int`     | Unsigned hexadecimal, lowercase |
| `X`       | `unsigned int`     | Unsigned hexadecimal, uppercase |
| `%%`      | *(none)*           | A literal `%` character |


## Supported flags (bonus)

| Flag    | Effect |
|---|---|
| `-`     | Left-justify within the field width (default is right-justified) |
| `0`     | Pad the field with leading zeros instead of spaces |
| `#`     | Prefix `0x` / `0X` for `x` / `X` conversions; always present for `p` |
| `+`     | Always print a sign (`+` or `-`) for numeric conversions |
| ` `     | Prefix a space for positive numbers when `+` is not active |

Flags may be combined freely, e.g. `%-+10d` left-justifies a signed integer in a 10-character field, always showing the sign.


## Internal architecture

The project is organised around the following call chain:

```
ft_printf()
  └─ ft_handle_vargs()        — parse one % specifier and dispatch
       ├─ ft_next_conv()      — scan flags / width / precision / conversion
       ├─ ft_char_formatted() — handle %c
       ├─ ft_str_formatted()  — handle %s (uses ft_putstr_fd_n)
       └─ ft_itoa_formatted() — handle %p / %d / %i / %u / %x / %X
            ├─ formated_number()     — build digit string + prefix
            │    ├─ ft_prenum_handler()  — allocate sign / 0x prefix
            │    └─ ft_ibasetoa()        — convert integer to string in base N
            └─ ft_striter()   — uppercase the hex string for %X
```

| File | Responsibility |
|---|---|
| `ft_printf.c` | Entry point; literal character loop, `%%` handling, dispatch |
| `ft_variadic_handler.c` | `ft_handle_vargs` + `ft_next_conv` |
| `ft_number_handler.c` | `ft_itoa_formatted`, `formated_number`, `ft_prenum_handler` |
| `ft_string_handler.c` | `ft_str_formatted`, `ft_char_formatted`, `ft_putstr_fd_n`, `ft_putchars_n_fd` |
| `ft_ibasetoa.c` | `ft_ibasetoa` — arbitrary-base integer to string |
| `ft_striter.c` | `ft_striter` — in-place character mapping |
| `ft_printf.h` | Public API, `t_format`, `t_fnum`, `e_flags`; full Doxygen documentation |
| `libft/` | Subset of libft functions bundled into the archive |


---


# Instructions


## Building the library

```bash
make
```

Running `make` from the `printf/` directory compiles all object files into `objs/` and links them into the static archive `libftprintf.a`.


## Linking against it

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o my_program
./my_program
```

Alternatively, use the provided `run` target which compiles `main.c` and links it against the archive in one step:

```bash
make run
./run
```


## Makefile rules

| Rule | Effect |
|---|---|
| `make` / `make all` | Compile all object files and create `libftprintf.a` |
| `make clean` | Remove the `objs/` directory |
| `make fclean` | `clean` + remove `libftprintf.a` |
| `make re` | `fclean` then `all` |
| `make run` | Compile and link `main.c` against the archive, producing `./run` |
| `make norm` | Run Norminette on all sources and the header, showing only issues |
| `make eclean` | Generate `compile_commands.json` via `bear`, then `fclean` (for Emacs LSP) |
| `make test` | Print the values of `NAME`, `OBJS`, and `SRCS` for cross-checking |


## Testing

> [!NOTE]
> `main.c` and the `run` binary in the repository are **not part of the submitted version**.
> They are kept for local testing and can be built with `make run`.

A quick sanity check for each specifier:

```c
ft_printf("char:    %c\n",  'A');
ft_printf("string:  %s\n",  "hello");
ft_printf("pointer: %p\n",  (void *)main);
ft_printf("int:     %d\n",  -42);
ft_printf("uint:    %u\n",  3000000000u);
ft_printf("hex lc:  %x\n",  255);
ft_printf("hex uc:  %X\n",  255);
ft_printf("percent: %%\n");
```

To check for memory leaks, run with Valgrind:

```bash
make run
valgrind --leak-check=full ./run
```


---


# Resources


## Tutorials & references

- [printf(3) — Linux manual page.](https://www.man7.org/linux/man-pages/man3/printf.3.html)
- [stdarg(3) — Variadic argument handling in C.](https://www.man7.org/linux/man-pages/man3/stdarg.3.html)
- [ar(1) — Creating and maintaining static libraries.](https://www.man7.org/linux/man-pages/man1/ar.1.html)
- [Compiler and Makefile overview.](https://www.youtube.com/watch?v=GExnnTaBELk)


## AI usage

For conceptual questions and hints during development I used a ChatGPT project configured with the same CS50-style policy as in the libft and get_next_line projects: hints and correctness checks only, no full solutions.

Additionally, I used an AI agent (Google Antigravity) for the following:

- Generating the Doxygen documentation (`@brief`, `@param`, `@return`, `@var`) placed in `ft_printf.h`.
- Writing and proofreading this README file.


## System setup

My personal dotfiles (Emacs, Alacritty, tmux) are available at:

<https://github.com/sousamj2/.reticencias.git>

Emacs was the editor used throughout this project. The LSP integration for C (`clangd`) was set up via the `compile_commands.json` generated by the `eclean` Makefile rule.
