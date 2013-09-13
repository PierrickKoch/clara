CLARA
=====

*The Common LAAS RAster library*

Provide Geo data through GDAL, the standard library, from our existing libs.

    +--------+
    |        |
    | libDTM |-----+
    |        |     |    +-------+    +------+
    +--------+     |    |       |    |      |
                   +--->| clara |--->| GDAL |
    +-----------+  |    |       |    |      |
    |           |  |    +-------+    +------+
    | regionMap |--+
    |           |
    +-----------+


* http://gdal.org
* http://www.openrobots.org/wiki
* http://trac.laas.fr/git/clara


INSTALL
-------

    git clone http://trac.laas.fr/git/clara && cd clara
    mkdir build && cd build
    cmake -DCMAKE_INSTALL_PREFIX=$HOME/devel ..
    make -j8 && make install


CONTRIBUTE
----------

Code is available on GitHub at https://github.com/pierriko/clara

Feel free to fork, pull request or submit issues to improve the project!

* https://github.com/pierriko/clara/fork
* https://github.com/pierriko/clara/issues
* https://github.com/pierriko/clara/pulls
* https://help.github.com/articles/fork-a-repo
* https://help.github.com/articles/using-pull-requests


LICENSE
-------

[BSD 3-Clause](http://opensource.org/licenses/BSD-3-Clause)
