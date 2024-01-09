#!/usr/bin/env bash

# install python and gcc
apt-get install -y python3 python3-pip python3-dev gcc

# install dependencies
pip3 install -r /autograder/source/requirements.txt