# Learning SDL (My own projects)

## First time

```bash
cmake -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

```bash
ln -s build/compile_commands.json .
```

## Any new changes

```bash
cmake --build build
```

## To run
```bash
./build/bin/main
```
