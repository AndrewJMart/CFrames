# CFrames
CFrames is a simple executable that allows you to view any gif or png in your terminal as ASCII art.
---

## Demo

Here is an example GIF and it's resulting ASCII art that will continuously output to your terminal.

### Original GIF Version
This is the actual GIF:

![Original Demo](https://media.giphy.com/media/lOiJiFNeRuvdfZQbtK/giphy.gif)

### ASCII GIF Version
This is the ASCII version of the animation:

![ASCII Demo](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExeThtMmJrbXFsNGVldjV6bXFucmczYTdsdDJsNWQ1YnBwaDZxdGdlcCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/uMaMAwQjpKn86BKGfW/giphy.gif)

Please note, while the program will resize your initial PNG or GIF, it is important to note that for best viewing you will have to tinker with your zoom settings on your terminal.

## Installation
Here's how to try out CFrames yourself!

1. ***Clone Github Repo***
  Access code locally on your machine by cloning this git repo.
```bash
git clone https://github.com/AndrewJmart/CFrames.git
```

2. ***Use Makefile To Compile Executable***
  With gcc on your system, run the Makefile with the command below to generate the executable 'ascii_viewer'

```bash
  make
```

And there you have it! You now have an executable that will process pngs & gifs into ASCII art!

## Usage

To use the executable ```ascii_viewer```, simply move your terminal to the folder that the executable is held in and type

```bash
./ascii_viewer filename.(gif/png)
```




With filename being the name, including the .png/.gif extension of the file held in the same folder.

