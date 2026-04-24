# LogLite Starter Code

This directory contains the starter code for the LogLite project.

## Files

| File | Description |
|------|-------------|
| `Makefile` | Build configuration (do not modify targets) |
| `main.c` | Entry point (mostly complete) |
| `types.h` | Data structure definitions (modify as needed) |
| `parser.h` | Parser function declarations |
| `parser.c` | Parser implementation (TODO: implement functions) |
| `query.h` | Query function declarations |
| `query.c` | Query implementation (TODO: implement functions) |
| `ai_log_template.md` | AI documentation template (rename to `ai_log.md`) |

## Building

```bash
# Build the project
make

# Build with sanitizers (for testing)
make sanitize

# Clean build artifacts
make clean
```

## Running

```bash
# Basic usage
./loglite logfile.log

# With input redirection
./loglite logfile.log < commands.txt

# With sanitizers (after make sanitize)
./loglite logfile.log < commands.txt
```

## Testing with Valgrind

```bash
# Check for memory leaks
valgrind --leak-check=full ./loglite logfile.log < commands.txt
```

## Getting Started

1. Read the project specification (`spec.md`)
2. Study the data structures in `types.h`
3. Implement `parser.c` functions (Phase 1)
4. Implement `query.c` functions (Phase 2)
5. Test with your own log files and commands
6. Run with sanitizers to check memory safety
7. Document AI usage in `ai_log.md`

## Submission Checklist

- [ ] All required files present
- [ ] `make clean && make` succeeds with no warnings
- [ ] Sanitizer build passes
- [ ] No memory leaks (valgrind clean)
- [ ] `ai_log.md` completed
- [ ] Partner contract (if working in pairs)

Good luck!

