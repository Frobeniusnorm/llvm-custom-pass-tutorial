## Showcasing LLVM's new pass manager

Build:
```
cmake -B build
cd build
make
```
Use:
```
clang -emit-llvm test.c -S -o test.ll -O1
opt --load-pass-plugin=build/llvm-plugin/libCustomPass.so test.ll -o test.ll --passes="custom-pass" -S
clang test.ll -o test
```
or only with clang:
```
clang -fpass-plugin=build/llvm-plugin/libCustomPass.so test.c -O1
```
