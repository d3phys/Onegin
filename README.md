<p align="center">
     <img src="images//onegin_logo.png" alt="Logo" width="100"/>
</p>

# Onegin
The fastest text analyzer. It was written by a MIPT student as homework task.
* [Installation](#installation)
* [Usage](#usage)
* [Docs](#docs)

## Installation
You should have `git` , `make` and `g++ compiler` installed.
* Clone this repository:
    * `git clone https://github.com/d3phys/Onegin.git`
 * Build the program:
    * `cd Onegin/`
    * `make bin`

## Usage
You can easily analyze texts using console arguments. For example:

`./onegin -i input.txt -o output1.txt ~/Downloads/output2.txt -s bubble -c alpha`

This command reads the `input.txt` file, than sorts the lines using the bubble sort algorithm and outputs them to the files `output1.txt` and `output2.txt`.

You can see the commonly used options using `-help` or `-h` option.

<p align="center">
     <img src="images//onegin_logo.png" alt="Logo" width="500"/>
</p>

## Docs
If you want to use some modules or modify the whole program, you can check the documetation.
>Check `<local_path_to_repo>/docs/compiled`
