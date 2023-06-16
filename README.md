# AI - First Project

## Quick verify
```bash
cat <(./geramapa 3 3 5 123) <(./geramapa 3 3 5 123 | ./solve 2> /dev/null) | ./verifica; echo $?
```

## Quick verify with debug
```bash
cat <(./geramapa 3 3 5 123) <(./geramapa 3 3 5 123 | ./solve) | ./verifica; echo $?
```