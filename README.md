# CFetch

### The most minimalist and opinionated fetch tool.

I didn't know where to start with my C projects. So, one day, I opened my terminal, saw my **beautiful** Fastfetch, and wondered:

_What if I recreated Fastfetch from scratch, keeping only the information I actually need?_

And that's where **CFetch** came in.

CFetch is my first C project. It's deliberately minimalistic and opinionated, displaying only a handful of system details. It isn't meant to replace Fastfetch or compete with its extensive feature set. It simply does what I want it to do.

Written entirely in **C**, CFetch is lightweight and has minimal dependencies.

### Features

- Memory usage
    
- System uptime
    
- Hostname
    
- Username
    
- Shell
    
- Linux distribution
    
- Kernel version
    
- Installed package count (Arch Linux)
    

### Limitations

CFetch currently supports **Linux only**. Package counting currently relies on the Arch Linux package database.

### Building

Clone the repository:

```
git clone https://github.com/YOUR_USERNAME/CFetch.git
cd CFetch
```

Compile:

```
gcc -Wall -Wextra -Wpedantic -std=c11 -o cfetch cfetch.c
```

Run:

```
./cfetch
```

### License

CFetch is licensed under the **GNU General Public License v3.0 (GPL-3.0)**.