# cgrad
## About
Project heavily inspired by Andrej Karpathy's [micrograd](https://github.com/karpathy/micrograd), with the difference being that micrograd is written in Python as opposed to cgrad, which is written in C.
## Description
A tiny autograd engine implementing backpropagation (reverse-mode autodiff) with typical machine learning structures like neurons, layers and mlps. Engine only oparates on scalar values, so e.g. we chop up each neuron into all of its individual tiny adds and multiplies.
## Usage
There is an usage example in *example* directory, that compiles after *make* command in the terminal. In order to make your own neural network, you will have to make your own *main.c* file (and input/output files if you wish to) and change Makfile accordingly.
## License
MIT
