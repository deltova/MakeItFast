# Twitter 
This project starts from a simple leetcode exercise where you need to create a simple API that "simulate" 
a super simple version of Twitter.
I wanted to push the exercise to the next level:
- Adding benchmarking tool to evaluate the performance of the API
- Have a fuzzing tool that evaluate the c++ version against a reference wrote in python
- Push the performance


## Getting Started

To begin with this project you just could clone it from github.

### Prerequisites

To make it work you need:
- cppyy `pip install cppyy`
- Google BenchMark(archlinux: `yaourt -S benchmark`)

### Installing

To compile the project:

```
mkdir build
cd build
cmake ..
make
```

### Tools
You can run some test generated tests using:
```
make check
```
You can run a benchmark that is just running the different function of the lib from a input file:
```
make bench
```

## Authors

* **Clement Magnard** - [Deltova](https://github.com/deltova)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
