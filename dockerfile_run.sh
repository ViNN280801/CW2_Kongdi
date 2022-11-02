#!/bin/bash

#Setting colour variables
blue='\033[0;36m'
yellow='\033[0;33m'
reset_colour='\033[0m'

printf "${yellow}Requesting password to start docker service:\n${reset_colour}"

# Staring docker service
sudo systemctl start docker

# Sign in to docker
docker login

# Downloading Debian image
docker pull alpine:latest

# Building project with control work #2
docker build -t cw2_kongdi .

printf "${blue}Do you want to run this container? y/N: ${reset_colour}"
read choice

if [[ "$choice" == "y" ]] || [[ "$choice" == "Y" ]]; then
    # Running container
    docker container run cw2_kongdi:latest
elif [[ "$choice" == "n" ]] || [[ "$choice" == "N" ]]; then
    break
fi
