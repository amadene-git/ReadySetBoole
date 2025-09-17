#!/bin/bash

docker build -t ready_set_boole .

docker run -it --rm \
    --name ready_set_boole \
    --hostname ready_set_boole \
    -v /home/$USER:/home/$USER \
    -v /home/$USER:/root \
    -w ${PWD} \
    ready_set_boole \
    bash
