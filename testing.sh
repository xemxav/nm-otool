#!/usr/bin/env sh

NM="nm"
NM_PERSO="./ft_nm"

test_nm()
{
  echo $1
  eval ${NM_PERSO} $1 > my_result.txt
  eval ${NM} $1 > off_result.txt
  diff my_result.txt off_result.txt
    if [ $? -eq 0 ]
    then
      echo ' ok'
      rm my_result.txt
      rm off_result.txt
    else
      echo $?
    fi

}

test_nm $1