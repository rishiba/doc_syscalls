#!/bin/bash

# Script to make html docs and start in a browser.

make clean
make html
google-chrome _build/html/index.html
