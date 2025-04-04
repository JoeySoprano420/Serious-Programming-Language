#!/bin/bash
# Install required dependencies
while read -r lib version; do
    apt-get install "$lib=$version"
done < <(jq -r '.dependencies[] | @sh' dependencies.json)
