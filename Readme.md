[![Build Status](https://travis-ci.org/rete/Monkey.svg?branch=master)](https://travis-ci.org/rete/Monkey)

# Monkey
# A unified c++ io interface for markup languages and others
Copyright Remi Ete

## INSTALL:

The build process is managed by [CMake](http://cmake.org)

### Dependencies

In the root directory :

```bash
mkdir build
cd build
cmake [-DOPTIONS=...] ..
make
```

where OPTIONS can be :
* INSTALL_DOC [ON/OFF] to install [doxygen](www.doxygen.org) code documentation
* Format_SUPPORT [ON/OFF], with Format = a Monkey supported format (Xml, Json, Yaml, Binary, MySQL)

Example :

```bash
cmake -DINSTALL_DOC=ON -DXml_SUPPORT=ON ..
```

All options area by default set to OFF

### Bug report

You can send emails to <remi.ete@gmail.com>
or use the [github issues interface](https://github.com/rete/Monkey/issues)
