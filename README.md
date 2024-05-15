[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/JXTgUwc5)
# Project08 Page Tables and Virtual Memory

## About

## Requirements

### Overview

In this project you will get some experience with how the kernel manages the virtual address space of user proceses. By default every process is given its own virtual address space and user processes cannot access the memory (virtual address space) of anothe process. However, sometimes it is useful to allow two or more processes to share a portion of their virtual address space so they can communicte data among themselves. In modern Unix this can be achieved with the `mmap()` system call. We are going implement a much simpler version called `smem()`.

### Deliverables

* Include a copy of xv6 with your modified kernel supporting the virtual memory requirements described below.  
* Your implementation should pass all of the Project08 Autograder tests.  
* Your source code should conform to xv6 formatting conventions.  
* Your Project08 repo should not have any extraneous files or build artifacts.  
* Make sure to test your repo by cloning from GitHub to a different location and run the Autograder. This will catch problems like missing files.  

#### Kernel Free Pages
#### Page Directories
#### Process Shared Memory

## Links

### External Dependencies

## Testing

### Manual

### Autograder
