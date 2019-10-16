#!/bin/bash

#make

if [[ $# == 2 ]]; then
    PROGRAM=$1
    SCIEZKA=$2
else
    echo "Zła ilość parametrów"
fi

for f in $SCIEZKA/*.in; do
    ./$PROGRAM <$f >${f%in}out2 2>${f%in}err2

    diff ${f%in}err2 ${f%in}err >/dev/null
    
    if [[ $? != 0 ]]; then
	echo "Niepoprawne wyjście diagnostyczne dla wejścia ${f%.in}"
    else
	echo "Poprawne wyjście diagnostyczne dla wejścia ${f%.in}"
    fi
    
    diff ${f%in}out2 ${f%in}out >/dev/null

    if [[ $? != 0 ]]; then
	echo "Niepoprawne wyjście dla wejścia ${f%.in}"
    else
	echo "Poprawne wyjście dla wejścia ${f%.in}"
    fi
done

    
