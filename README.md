# Simple CPU stress test
The code is written just for fun and practicing fantastic std::async function. The code runs some threads, each taking a lot of square roots, sines and cosines to make your CPU cry!

# Make
Compile the code by yourself. The only restriction is C++11 or above. You can use the following command for compilation:
```bash
g++ main.cpp -o stress_test
```

# Usage
You must pass the following arguments to the program
* number of threads to run
* number of sqrts/sines/cosines

```
usage: stress_test <THREADS> <STEPS>
```
