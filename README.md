CricketInfo
===========

Some InfoNest stuff to measure entropies in cricket.
This depends on [InfoNest](https://github.com/eggplantbren/InfoNest),
which I've included as a submodule in this repository. Make sure you use
`--recursive` when you clone this repository:

    $ git clone --recursive https://github.com/eggplantbren/CricketInfo

You'll also need to compile InfoNest before you can compile CricketInfo.

    $ cd CricketInfo
    $ cd InfoNest/cpp
    $ make
    $ cd ../../cpp
    $ make

(c) 2017 Brendon J. Brewer

This is free software released under the GNU General Public License, version 3.
See LICENSE file for details.


## Some basic results

For the constant hazard model, the average depth is 8.607 +- 0.044,
so the conditional (differential) entropy is 2.393 +- 0.044 nats.
The differential entropy of the prior is 4.350 nats.



